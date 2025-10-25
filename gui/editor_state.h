#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *status_label;
    GtkWidget *console_view;
    GtkWidget *notebook;  /* Para las pestañas de consola */
    GtkWidget *console_tab;  /* Pestaña de consola principal */
    GtkWidget *s_tab;  /* Pestaña de código .s */
    GtkWidget *qemu_tab;  /* Pestaña de salida QEMU */
    gchar *current_path; /* ruta del archivo .usl actual */
    gchar *last_ast_png; /* última imagen AST generada */
    gchar *last_ast_dot; /* último DOT AST generado */
} EditorState;

#endif
