#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *status_label;
    GtkWidget *console_view;
    gchar *current_path; /* ruta del archivo .usl actual */
    gchar *last_ast_png; /* última imagen AST generada */
    gchar *last_ast_dot; /* último DOT AST generado */
} EditorState;

#endif
