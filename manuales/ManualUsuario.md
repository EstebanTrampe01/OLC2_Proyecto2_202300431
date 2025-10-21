<div align="center" style="border:2px solid #444;padding:24px;border-radius:12px;background:linear-gradient(180deg,#222,#111);color:#eee">
  <h1 style="margin:0 0 8px 0">JavaLang Interpreter</h1>
  <h3 style="margin:0 0 16px 0">Manual de Usuario</h3>
  <p style="margin:0">Universidad San Carlos de Guatemala — Facultad de Ingeniería</p>
  <p style="margin:0">Organización de Lenguajes y Compiladores 2</p>
  <p style="margin:12px 0 0 0"><b>Autor:</b> Juan Esteban Chacón Trampe — 202300431</p>
  <p style="margin:0"><b>Título del Proyecto:</b> JavaLang Interpreter</p>
</div>

---

## Introducción

Este manual guía al usuario en la instalación y uso del JavaLang Interpreter con archivos .usl. Explica cómo editar, guardar y ejecutar programas desde la GUI, así como interpretar los reportes de AST, tabla de símbolos y errores. Está orientado a estudiantes del curso OLC2 y asume un entorno Linux con las dependencias indicadas.

## 1. Requisitos e instalación

- Linux con GCC, Flex, Bison, GTK+3 y Graphviz (opcional) instalados.
- Clonar el repositorio y compilar:
  - make
  - make all editor (o tarea preconfigurada en VS Code)

## 2. Archivos USL (.usl)

- Los programas se editan en archivos con extensión .usl.
- Soporta literales (int, float, boolean, char, string, null), control (if/else, while, for, switch) y funciones builtin como String.valueOf.

## 3. Uso del editor GTK

- Ejecutar el editor: make run-editor o ./build/editor
- Atajos:
  - Ctrl+O abrir, Ctrl+S guardar
  - F5 ejecutar, F6 generar AST, F9 errores, F10 símbolos
- Paneles:
  - Editor: edición del código .usl
  - Consola: salida de la ejecución (stdout + stderr combinados)

  ![alt text](image.png)

## 4. Ejecutar y ver resultados

1) Escribe tu código en el panel superior.  
            ![alt text](image-3.png)
2) Guarda el archivo si lo deseas (Ctrl+S).  
![alt text](image-2.png)
3) Presiona F5.  
4) La salida aparece en la consola inferior.
![alt text](image-1.png)

Notas:
- La GUI normaliza la salida a UTF‑8 para evitar errores de codificación.
- La semántica de ejecución es la misma que por CLI.

## 5. Reportes: AST, Tabla de Errores y Símbolos

- AST (F6): genera un .dot en carpeta reportes/ y un PNG si está dot instalado. Se abre un visor en la GUI.
![alt text](image-4.png)
- Errores (F9): muestra una tabla parseada de líneas con prefijo ERR|emitidas por el intérprete.

  - Formato: ERR|descripcion|ambito|linea|columna|tipo

  ![alt text](image-5.png)
- Símbolos (F10): tabla a partir de líneas con prefijo SYM|
  - Formato: SYM|id|clase|tipo|ambito|linea|columna
  ![alt text](image-6.png)


## 7. Solución de problemas

- No existe ./build/calc: compila con `make`.
- Errores de GTK-CRITICAL: la GUI ya normaliza UTF‑8; si persisten, revisa literales char (usar \uXXXX correctos).
- AST sin PNG: instala Graphviz (dot) o revisa permisos de la carpeta reportes.
