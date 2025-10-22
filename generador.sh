#!/usr/bin/env bash
# generador.sh - Generador y ejecutor ARM64 para archivos .usl
# Uso: ./generador.sh <archivo.usl>
#
# Flujo:
# 1) Si existe ./build/calc, lo usa: ./build/calc --codegen-out=out.s <archivo>
# 2) Si no existe, genera un out.s de respaldo que imprime la primera cadena encontrada
# 3) Ensambla/enlaza con toolchain aarch64 y ejecuta con qemu-aarch64

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEBUG=0
if [[ "${1:-}" == "--debug" ]]; then DEBUG=1; shift; fi
USL_FILE="${1:-test.usl}"
OUT_S="out.s"
OUT_BIN="out_arm64"
COMPILER_BIN="${ROOT_DIR}/build/calc"

usage() {
  cat <<EOF
Usage: $0 <archivo.usl>
Genera ensamblador ARM64 (out.s) desde <archivo.usl>, ensambla y ejecuta con qemu-aarch64.
Si el compilador del proyecto está en ./build/calc se usará; de lo contrario se genera
un ensamblador de respaldo que imprime la primera cadena encontrada en el .usl.

Ejemplo:
  $0 test.usl

EOF
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
  usage
  exit 0
fi

if [ ! -f "$USL_FILE" ]; then
  echo "[error] archivo no encontrado: $USL_FILE" >&2
  usage
  exit 2
fi

echo "[info] entrada: $USL_FILE"

if [ -x "$COMPILER_BIN" ]; then
  echo "[info] usando compilador del proyecto: $COMPILER_BIN"
  if [ "$DEBUG" -eq 1 ]; then
    echo "[debug] invocando: $COMPILER_BIN --codegen-out=$OUT_S $USL_FILE"
    export CODEGEN_DEBUG=1
  fi
  # Intentar rebuild con make si Makefile existe
  if [ -f "${ROOT_DIR}/Makefile" ]; then
    echo "[info] Makefile detectado, ejecutando make (puede tardar)"
    (cd "${ROOT_DIR}" && make) || echo "[warn] make devolvió error, continuando con binario existente"
  fi
  "$COMPILER_BIN" --codegen-out="$OUT_S" "$USL_FILE" || { echo "[error] el compilador devolvió error"; exit 1; }
else
  echo "[warn] compilador no encontrado en $COMPILER_BIN — generando fallback"
  # Extraer la primera cadena entre comillas
  MSG=$(grep -oP '"\K[^"]+(?=")' "$USL_FILE" | head -n1 || true)
  if [ -z "$MSG" ]; then MSG="hola mundo"; fi
  echo "[info] mensaje detectado: '$MSG'"

  # Asegurar newline
  if [[ "$MSG" != *$'\n' ]]; then MSG_LINE="${MSG}\n"; else MSG_LINE="$MSG"; fi
  MSG_LEN=${#MSG_LINE}

  cat > "$OUT_S" <<EOF
    .section .data
    .align 3
msg:
    .asciz "${MSG_LINE}"

    .section .text
    .global _start
_start:
    // write(1, msg, ${MSG_LEN})
    mov x0, #1
    adrp x1, msg
    add x1, x1, :lo12:msg
    mov x2, #${MSG_LEN}
    mov x8, #64
    svc #0

    // exit(0)
    mov x0, #0
    mov x8, #93
    svc #0
EOF
  echo "[info] generado $OUT_S (fallback)"
  if [ "$DEBUG" -eq 1 ]; then echo "[debug] contenido de $OUT_S:"; sed -n '1,200p' "$OUT_S"; fi
fi

# Ensamblar y linkear
CC_CROSS=$(command -v aarch64-linux-gnu-gcc || true)
AS_CROSS=$(command -v aarch64-linux-gnu-as || true)
LD_CROSS=$(command -v aarch64-linux-gnu-ld || true)

if [ -n "$CC_CROSS" ]; then
  echo "[info] enlazando con cross-compiler: $CC_CROSS"
  "$CC_CROSS" -nostartfiles -static "$OUT_S" -o "$OUT_BIN" || { echo "[error] falló la compilación con $CC_CROSS"; exit 1; }
elif [ -n "$AS_CROSS" ] && [ -n "$LD_CROSS" ]; then
  echo "[info] ensamblando con as + ld"
  TMP_O="/tmp/out_arm64.o"
  "$AS_CROSS" -o "$TMP_O" "$OUT_S"
  "$LD_CROSS" -o "$OUT_BIN" "$TMP_O"
  rm -f "$TMP_O"
else
  echo "[error] no se encontró toolchain aarch64 (aarch64-linux-gnu-gcc o as/ld). Instala cross-toolchain." >&2
  exit 2
fi

# Ejecutar con QEMU
QEMU=$(command -v qemu-aarch64 || true)
if [ -z "$QEMU" ]; then
  echo "[error] qemu-aarch64 no encontrado en PATH. Instala qemu-user." >&2
  echo "[info] el binario generado está en: $OUT_BIN"
  exit 0
fi

echo "[info] ejecutando con qemu-aarch64: $OUT_BIN"
if [ "$DEBUG" -eq 1 ]; then
  echo "[debug] tamaño out.s: $(stat -c%s "$OUT_S") bytes";
  echo "[debug] primeras 120 líneas de out.s:"; sed -n '1,120p' "$OUT_S";
fi

"$QEMU" -cpu cortex-a57 -L /usr/aarch64-linux-gnu "$OUT_BIN"
