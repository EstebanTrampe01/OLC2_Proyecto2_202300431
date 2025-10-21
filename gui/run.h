#ifndef GUI_RUN_H
#define GUI_RUN_H

#include <gtk/gtk.h>
#include "editor_state.h"

/* Ejecuta ./build/calc con el contenido del GtkTextView y retorna salida combinada (stdout+stderr). Devuelve string g_malloc, caller libera con g_free. */
gchar* gui_run_calc_with_buffer(GtkTextView* view);

/* Muestra en una ventana modal la tabla de errores, parseando líneas especiales si existen; caso contrario muestra stderr capturado. */
void gui_show_errors_dialog(EditorState* st, const gchar* combined_output);

/* Muestra la tabla de símbolos a partir de líneas especiales emitidas por el intérprete. */
void gui_show_symbols_dialog(EditorState* st, const gchar* combined_output);

/* Genera y guarda el AST como PNG bajo 'reportes/' y abre un visor con la imagen si existe. */
void gui_generate_ast_report(GtkButton* btn, gpointer user_data);

#endif
