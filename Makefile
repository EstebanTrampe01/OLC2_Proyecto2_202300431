SRC     := src
BUILD   := build

CC      := gcc
BISON   := bison
FLEX    := flex
CFLAGS  := -I$(SRC) -Wall -Wextra
# Oara llevar registro de memoria y tener buen debug usaremos asan flags
ASAN_FLAGS := -fsanitize=address -fno-omit-frame-pointer -g -O0
RM      := rm -rf $(BUILD)
MKDIR   := mkdir -p $(BUILD)

# GTK (optional) flags for editor GUI (ignored if target not built)
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0 2>/dev/null)
GTK_LIBS   := $(shell pkg-config --libs gtk+-3.0 2>/dev/null)

.DEFAULT_GOAL := all

# Buscar todos los .c en src (excepto parser.y y lexer.l) excluyendo util eliminado
# Excluir los archivos originales expr_*.c e instr_*.c en src/codegen/generadorARM porque
# hemos reorganizado esos módulos en subcarpetas 'expresiones/' y 'instrucciones/'.
# Esto evita definiciones duplicadas al compilar ambas copias.
SRC_FILES := $(shell find $(SRC) -name '*.c' \
	! -name 'array_element_utils.c' \
	! -path '$(SRC)/codegen/generadorARM/expr_*.c' \
	! -path '$(SRC)/codegen/generadorARM/instr_*.c' \
	! -name 'compat_impl.c' \
	! -name '*_test.c')

# Archivos generados por Bison y Flex
BISON_C := $(BUILD)/parser.tab.c
BISON_H := $(BUILD)/parser.tab.h
LEX_C   := $(BUILD)/lex.yy.c

# Objetos finales
OBJ_SRC := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRC_FILES))
OBJ_GEN := $(BUILD)/parser.tab.o $(BUILD)/lex.yy.o
OBJ_ALL := $(OBJ_SRC) $(OBJ_GEN)

# GUI sources: solo el editor para el binario editor
GUI_SRC := gui/editor.c gui/run.c
GUI_OBJ := $(patsubst gui/%.c,$(BUILD)/gui/%.o,$(GUI_SRC))

EDITOR_BIN := $(BUILD)/editor

all: $(BUILD)/calc

# Optional target to build the GTK editor if GTK is available
editor: $(EDITOR_BIN)

$(EDITOR_BIN): $(GUI_OBJ)
	@if [ -z "$(GUI_SRC)" ]; then echo "No GUI sources found."; exit 1; fi
	@if [ -z "$(GTK_LIBS)" ]; then echo "GTK+3 no encontrado (pkg-config gtk+-3.0). Instala las dependencias para compilar el editor."; exit 1; fi
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ $^ $(GTK_LIBS) -lm

$(BUILD):
	$(MKDIR)

# Generar parser
$(BISON_C) $(BISON_H) $(BUILD)/parser.output: $(SRC)/entriesTools/parser.y | $(BUILD)
	$(BISON) -d -v --locations -o $(BISON_C) $<

# Generar lexer
$(LEX_C): $(SRC)/entriesTools/lexer.l $(BISON_H) | $(BUILD)
	$(FLEX) -o $@ $<

# Compilar .c de src a .o
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/gui/%.o: gui/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	@if [ -z "$(GTK_CFLAGS)" ]; then echo "GTK+3 no encontrado (pkg-config gtk+-3.0). No se puede compilar el editor."; exit 1; fi
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c $< -o $@

# Compilar .c generados por Bison/Flex a .o
$(BUILD)/parser.tab.o: $(BISON_C) $(BISON_H)
	$(CC) $(CFLAGS) -c $(BISON_C) -o $@

$(BUILD)/lex.yy.o: $(LEX_C)
	$(CC) $(CFLAGS) -c $(LEX_C) -o $@

# Enlazar todo
$(BUILD)/calc: $(OBJ_ALL)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	$(RM)

# Build con AddressSanitizer para depurar corrupción de memoria.
# Paso 1: "make asan" generará un binario instrumentado build/calc_asan.
# Estrategia: limpiamos para recompilar todos los objetos con las flags ASAN.
asan: clean
	@echo "[ASAN] Recompilando con AddressSanitizer..."
	$(MAKE) CFLAGS="$(CFLAGS) $(ASAN_FLAGS)" LDFLAGS="$(LDFLAGS) $(ASAN_FLAGS)" $(BUILD)/calc
	@cp $(BUILD)/calc $(BUILD)/calc_asan
	@echo "[ASAN] Binario listo: build/calc_asan"

# --- Cross-compile / run helpers for ARM64 (.s -> aarch64 executable + qemu)
# Usage: make arm-assemble CODE=out.s OUT=out_aarch64
# Then: make run-arm FILE=out_aarch64
ARM_CC ?= aarch64-linux-gnu-gcc
QEMU ?= qemu-aarch64

.PHONY: arm-assemble run-arm
arm-assemble:
	@if [ -z "$(CODE)" ]; then echo "Usage: make arm-assemble CODE=file.s OUT=prog"; exit 1; fi
	@if ! command -v $(ARM_CC) >/dev/null 2>&1; then echo "Aviso: cross-compiler '$(ARM_CC)' no encontrado. Instala 'gcc-aarch64-linux-gnu' o ajusta ARM_CC."; exit 1; fi
	@if [ -z "$(OUT)" ]; then OUT=out_arm; fi
	$(ARM_CC) -static -nostdlib -o $(OUT) $(CODE)
	@echo "ARM64 executable produced: $(OUT)"

run-arm:
	@if [ -z "$(FILE)" ]; then echo "Usage: make run-arm FILE=prog"; exit 1; fi
	@if ! command -v $(QEMU) >/dev/null 2>&1; then echo "Aviso: qemu-aarch64 no encontrado. Instala qemu-user para ejecutar binarios aarch64 en x86_64."; exit 1; fi
	$(QEMU) ./$(FILE)

# Simple GTK test app
gtk-test: $(BUILD)/gtk_test

$(BUILD)/gtk_test: gui/gtk_test.c | $(BUILD)
	@if [ -z "$(GTK_LIBS)" ]; then echo "GTK+3 no encontrado (pkg-config gtk+-3.0). Instala libgtk-3-dev."; exit 1; fi
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ $< $(GTK_LIBS)

.PHONY: all clean editor gtk-test run-editor run-gtk-test run-gtk-test-host run-editor-host run-gtk-test-cleanenv run-editor-cleanenv asan

# Run helpers that clear LD_LIBRARY_PATH to evitar conflicto con snap core20
run-editor: editor
	@echo "Ejecutando editor con entorno limpio (sin LD_LIBRARY_PATH)..."
	env -u LD_LIBRARY_PATH ./build/editor

run-gtk-test: gtk-test
	@echo "Ejecutando gtk_test con entorno limpio (sin LD_LIBRARY_PATH)..."
	env -u LD_LIBRARY_PATH ./build/gtk_test

# Ejecutar forzando el enlazador dinámico del sistema (evita libs de snap core20)
run-gtk-test-host: gtk-test
	@echo "Ejecutando gtk_test con enlazador del sistema..."
	@if [ -x /lib64/ld-linux-x86-64.so.2 ]; then LDLOADER=/lib64/ld-linux-x86-64.so.2; else LDLOADER=/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2; fi; \
	$$LDLOADER --library-path /usr/lib/x86_64-linux-gnu:/lib/x86_64-linux-gnu ./build/gtk_test

run-editor-host: editor
	@echo "Ejecutando editor con enlazador del sistema..."
	@if [ -x /lib64/ld-linux-x86-64.so.2 ]; then LDLOADER=/lib64/ld-linux-x86-64.so.2; else LDLOADER=/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2; fi; \
	$$LDLOADER --library-path /usr/lib/x86_64-linux-gnu:/lib/x86_64-linux-gnu ./build/editor

# Ejecutar con entorno casi vacío preservando DISPLAY/Wayland
run-gtk-test-cleanenv: gtk-test
	@echo "Ejecutando gtk_test con entorno mínimo..."
	env -i DISPLAY=$$DISPLAY WAYLAND_DISPLAY=$$WAYLAND_DISPLAY XAUTHORITY=$$XAUTHORITY PATH=/usr/bin:/bin ./build/gtk_test

run-editor-cleanenv: editor
	@echo "Ejecutando editor con entorno mínimo..."
	env -i DISPLAY=$$DISPLAY WAYLAND_DISPLAY=$$WAYLAND_DISPLAY XAUTHORITY=$$XAUTHORITY PATH=/usr/bin:/bin ./build/editor
