#include "run.h"
#include <glib/gstdio.h>
#include <unistd.h>

static void append_column(GtkListStore* store, GtkTreeView* view, const char* title, int col){ (void)store;
    GtkCellRenderer* rend = gtk_cell_renderer_text_new();
    GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes(title, rend, "text", col, NULL);
    gtk_tree_view_append_column(view, column);
}

gchar* gui_run_calc_with_buffer(GtkTextView* view){
    GtkTextBuffer *buf = gtk_text_view_get_buffer(view);
    GtkTextIter start, end; gtk_text_buffer_get_start_iter(buf,&start); gtk_text_buffer_get_end_iter(buf,&end);
    char *text = gtk_text_buffer_get_text(buf,&start,&end,FALSE);

    if(!g_file_test("./build/calc", G_FILE_TEST_IS_EXECUTABLE)){
        gchar *msg = g_strdup("No existe ./build/calc (compila con make)");
        g_free(text); return msg;
    }

    gchar *tmpname = NULL; int fd = g_file_open_tmp("usl-XXXXXX.usl", &tmpname, NULL);
    if(fd == -1){ g_free(text); return g_strdup("No se pudo crear archivo temporal"); }
    FILE *f = fdopen(fd, "w"); if(!f){ close(fd); g_free(tmpname); g_free(text); return g_strdup("No se pudo abrir tmp"); }
    fwrite(text,1,strlen(text),f); fclose(f); g_free(text);

    gchar *cmd = g_strdup_printf("./build/calc %s", tmpname);
    gchar *out=NULL, *err=NULL; gint status=0; GError *gerr=NULL;
    g_spawn_command_line_sync(cmd, &out, &err, &status, &gerr);

    GString* combined = g_string_new("");
    if(out) g_string_append(combined, out);
    if(err) g_string_append(combined, err);

    if(out){ g_free(out);} if(err){ g_free(err);} 
    if(gerr) g_error_free(gerr);
    g_remove(tmpname); g_free(tmpname); g_free(cmd);
    return g_string_free(combined, FALSE);
}

static gchar* save_editor_buffer_to_tmp(GtkTextView* view){
    GtkTextBuffer *buf = gtk_text_view_get_buffer(view);
    GtkTextIter start, end; gtk_text_buffer_get_start_iter(buf,&start); gtk_text_buffer_get_end_iter(buf,&end);
    char *text = gtk_text_buffer_get_text(buf,&start,&end,FALSE);
    gchar *src_tmp = NULL; int fd1 = g_file_open_tmp("usl-XXXXXX.usl", &src_tmp, NULL);
    if(fd1 == -1){ g_free(text); return NULL; }
    FILE *f1 = fdopen(fd1, "w"); if(!f1){ close(fd1); g_free(src_tmp); g_free(text); return NULL; }
    fwrite(text,1,strlen(text),f1); fclose(f1); g_free(text);
    return src_tmp;
}

static void ast_viewer_reload(GtkButton* btn, gpointer data){
    (void)btn; if(!data) return; EditorState* st = (EditorState*)data;
    if(!st->last_ast_png || !g_file_test(st->last_ast_png, G_FILE_TEST_EXISTS)) return;
    GtkWidget* img = g_object_get_data(G_OBJECT(st->window), "ast-image");
    if(!img) return;
    /* Zoom factor almacenado en la ventana; por defecto 1.0 */
    gdouble* pzoom = (gdouble*)g_object_get_data(G_OBJECT(st->window), "ast-zoom");
    gdouble zoom = (pzoom? *pzoom : 1.0);
    int w=0, h=0; gdk_pixbuf_get_file_info(st->last_ast_png, &w, &h);
    if(w<=0 || h<=0){
        GError* err=NULL; GdkPixbuf* px = gdk_pixbuf_new_from_file(st->last_ast_png, &err);
        if(!px){ if(err){ g_error_free(err);} return; }
        gtk_image_set_from_pixbuf(GTK_IMAGE(img), px);
        g_object_unref(px); return;
    }
    int max_dim = 4000; /* límite para evitar imágenes gigantes en GTK */
    int target_w = (int)(w * zoom);
    if(target_w > max_dim) target_w = max_dim;
    if(target_w < 100) target_w = 100;
    GError* err=NULL; GdkPixbuf* px = gdk_pixbuf_new_from_file_at_scale(st->last_ast_png, target_w, -1, TRUE, &err);
    if(!px){ if(err){ g_error_free(err);} return; }
    gtk_image_set_from_pixbuf(GTK_IMAGE(img), px);
    g_object_unref(px);
}

static void ast_zoom_in(GtkButton* btn, gpointer data){
    (void)btn; if(!data) return; EditorState* st=(EditorState*)data;
    gdouble* pzoom = (gdouble*)g_object_get_data(G_OBJECT(st->window), "ast-zoom");
    if(!pzoom){ pzoom = g_new0(gdouble,1); *pzoom = 1.0; g_object_set_data_full(G_OBJECT(st->window), "ast-zoom", pzoom, g_free); }
    *pzoom *= 1.25;
    ast_viewer_reload(NULL, st);
}

static void ast_zoom_out(GtkButton* btn, gpointer data){
    (void)btn; if(!data) return; EditorState* st=(EditorState*)data;
    gdouble* pzoom = (gdouble*)g_object_get_data(G_OBJECT(st->window), "ast-zoom");
    if(!pzoom){ pzoom = g_new0(gdouble,1); *pzoom = 1.0; g_object_set_data_full(G_OBJECT(st->window), "ast-zoom", pzoom, g_free); }
    *pzoom /= 1.25; if(*pzoom < 0.1) *pzoom = 0.1;
    ast_viewer_reload(NULL, st);
}

static void open_ast_viewer(EditorState* st){
    if(!st || !st->last_ast_png || !g_file_test(st->last_ast_png, G_FILE_TEST_EXISTS)) return;
    GtkWidget* dialog = gtk_dialog_new_with_buttons("AST", GTK_WINDOW(st->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "Cerrar", GTK_RESPONSE_CLOSE, NULL);
    GtkWidget* content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_box_pack_start(GTK_BOX(content), vbox, TRUE, TRUE, 0);
    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    GtkWidget* reload = gtk_button_new_with_label("Recargar");
    GtkWidget* zoom_in = gtk_button_new_with_label("Zoom +");
    GtkWidget* zoom_out = gtk_button_new_with_label("Zoom -");
    gtk_box_pack_start(GTK_BOX(hbox), reload, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), zoom_in, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), zoom_out, FALSE, FALSE, 0);
    GtkWidget* scroll = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);
    GtkWidget* img = gtk_image_new();
    g_object_set_data(G_OBJECT(st->window), "ast-image", img);
    gtk_container_add(GTK_CONTAINER(scroll), img);
    g_signal_connect(reload, "clicked", G_CALLBACK(ast_viewer_reload), st);
    g_signal_connect(zoom_in, "clicked", G_CALLBACK(ast_zoom_in), st);
    g_signal_connect(zoom_out, "clicked", G_CALLBACK(ast_zoom_out), st);
    ast_viewer_reload(GTK_BUTTON(reload), st);
    gtk_widget_set_size_request(dialog, 800, 600);
    gtk_widget_show_all(dialog);
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
}

void gui_generate_ast_report(GtkButton* btn, gpointer user_data){
    (void)btn; if(!user_data) return; EditorState* st = (EditorState*)user_data;
    if(!g_file_test("./build/calc", G_FILE_TEST_IS_EXECUTABLE)){
        GtkWidget* md = gtk_message_dialog_new(GTK_WINDOW(st->window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
            "No existe ./build/calc. Compila primero (make all).");
        gtk_dialog_run(GTK_DIALOG(md)); gtk_widget_destroy(md); return;
    }
    // buffer a tmp
    gchar* src_tmp = save_editor_buffer_to_tmp(GTK_TEXT_VIEW(st->text_view));
    if(!src_tmp){
        GtkWidget* md = gtk_message_dialog_new(GTK_WINDOW(st->window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
            "No se pudo preparar el archivo temporal.");
        gtk_dialog_run(GTK_DIALOG(md)); gtk_widget_destroy(md); return;
    }
    // asegurar carpeta reportes
    if(!g_file_test("reportes", G_FILE_TEST_IS_DIR)) g_mkdir_with_parents("reportes", 0755);
    // nombres con timestamp
    GDateTime* now = g_date_time_new_now_local();
    gchar* stamp = g_date_time_format(now, "%Y%m%d-%H%M%S");
    g_date_time_unref(now);
    gchar* dot_path = g_strdup_printf("reportes/ast-%s.dot", stamp);
    gchar* png_path = g_strdup_printf("reportes/ast-%s.png", stamp);

    // generar DOT
    gchar *cmd1 = g_strdup_printf("./build/calc --ast-out=%s %s", dot_path, src_tmp);
    gchar *out1=NULL, *err1=NULL; gint status1=0; GError *gerr1=NULL;
    g_spawn_command_line_sync(cmd1, &out1, &err1, &status1, &gerr1);
    if(out1){ g_free(out1); }
    if(err1){ g_free(err1); }
    if(gerr1){ g_error_free(gerr1); }
    g_free(cmd1);
    g_remove(src_tmp); g_free(src_tmp);

    if(!g_file_test(dot_path, G_FILE_TEST_EXISTS)){
        GtkWidget* md = gtk_message_dialog_new(GTK_WINDOW(st->window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
            "No se pudo generar el DOT del AST.");
        gtk_dialog_run(GTK_DIALOG(md)); gtk_widget_destroy(md);
        g_free(dot_path); g_free(png_path); g_free(stamp);
        return;
    }
    // render PNG (si hay dot instalado)
    if(access("/usr/bin/dot", X_OK) == 0 || access("/bin/dot", X_OK) == 0){
        /* Generar PNG compacto para mejorar carga en GTK */
        gchar *cmd2 = g_strdup_printf("dot -Tpng -Grankdir=LR -Gnodesep=0.25 -Granksep=0.3 -Nfontsize=9 -Efontsize=9 -Gfontsize=10 %s -o %s", dot_path, png_path);
    gchar *out2=NULL, *err2=NULL; gint status2=0; GError *gerr2=NULL;
    g_spawn_command_line_sync(cmd2, &out2, &err2, &status2, &gerr2);
    if(out2){ g_free(out2); }
    if(err2){ g_free(err2); }
    if(gerr2){ g_error_free(gerr2); }
        g_free(cmd2);
    }
    // Guardar paths en estado
    if(st){
        g_free(st->last_ast_dot); st->last_ast_dot = g_strdup(dot_path);
        if(g_file_test(png_path, G_FILE_TEST_EXISTS)){
            g_free(st->last_ast_png); st->last_ast_png = g_strdup(png_path);
        }
    }
    if(st){
        if(st->last_ast_png){
            open_ast_viewer(st);
        } else {
            gchar* msg = g_strdup_printf("AST generado (sin PNG) en %s", dot_path);
            GtkWidget* ok = gtk_message_dialog_new(GTK_WINDOW(st->window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
                "%s", msg);
            gtk_dialog_run(GTK_DIALOG(ok)); gtk_widget_destroy(ok);
            g_free(msg);
        }
    }
    g_free(dot_path); g_free(png_path); g_free(stamp);
}

/* Reutiliza lógica de escape de editor.c sin exponer símbolo; pequeña copia local */
static gchar* escape_for_gui(const char* in){
    if(!in) return g_strdup("");
    const unsigned char* p = (const unsigned char*)in; GString* out = g_string_sized_new(strlen(in)+8);
    while(*p){
        if(*p < 0x80){
            unsigned char c=*p; if(c=='\n' || c=='\r' || c=='\t'){ g_string_append_c(out,(char)c); }
            else if(c < 0x20 || c==0x7F){ g_string_append_printf(out, "\\u%04X", (unsigned int)c); }
            else { g_string_append_c(out,(char)c);} p++; continue;
        }
        gunichar ch = g_utf8_get_char_validated((const gchar*)p, -1);
        if(ch == (gunichar)-1){ gunichar u=(gunichar)(*p); char buf[6]; int n=g_unichar_to_utf8(u,buf); g_string_append_len(out,buf,n); p++; continue; }
        else if(ch == (gunichar)-2){ while(*p){ gunichar u=(gunichar)(*p); char buf[6]; int n=g_unichar_to_utf8(u,buf); g_string_append_len(out,buf,n); p++; } break; }
        else { const gchar* next = g_utf8_next_char((const gchar*)p); g_string_append_len(out, (const gchar*)p, next-(const gchar*)p); p=(const unsigned char*)next; }
    }
    return g_string_free(out, FALSE);
}

void gui_show_errors_dialog(EditorState* st, const gchar* text){
    GtkWidget* dialog = gtk_dialog_new_with_buttons("Tabla de Errores",
        GTK_WINDOW(st->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "Cerrar", GTK_RESPONSE_CLOSE, NULL);
    GtkWidget* content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkListStore* store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
    GtkWidget* tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree), GTK_TREE_VIEW_GRID_LINES_BOTH);
    g_object_unref(store);
    append_column(store, GTK_TREE_VIEW(tree), "#", 0);
    append_column(store, GTK_TREE_VIEW(tree), "Descripción", 1);
    append_column(store, GTK_TREE_VIEW(tree), "Ámbito", 2);
    append_column(store, GTK_TREE_VIEW(tree), "Tipo", 3);
    append_column(store, GTK_TREE_VIEW(tree), "Línea", 4);
    append_column(store, GTK_TREE_VIEW(tree), "Columna", 5);

    // Parse lines starting with ERR|
    int count=0;
    if(text){
        gchar** lines = g_strsplit(text, "\n", -1);
        for(int i=0; lines[i]; i++){
            if(g_str_has_prefix(lines[i], "ERR|")){
                // Format: ERR|desc|ambito|line|col|Tipo  (nuevo)
                gchar** parts = g_strsplit(lines[i]+4, "|", 6);
                GtkTreeIter it; gtk_list_store_append(store, &it);
                int line = parts[3]? atoi(parts[3]) : 0;
                int col  = parts[4]? atoi(parts[4]) : 0;
                gchar* d0 = escape_for_gui(parts[0]?parts[0]:"");
                gchar* d1 = escape_for_gui(parts[1]?parts[1]:"Global");
                gchar* d5 = escape_for_gui(parts[5]?parts[5]:"");
                gtk_list_store_set(store, &it,
                    0, ++count,
                    1, d0,
                    2, d1,
                    3, d5,
                    4, line,
                    5, col,
                    -1);
                g_free(d0); g_free(d1); g_free(d5);
                g_strfreev(parts);
            }
        }
        g_strfreev(lines);
    }

    if(count==0){
        GtkWidget* scr = gtk_scrolled_window_new(NULL,NULL);
        gtk_container_add(GTK_CONTAINER(scr), tree);
        gtk_box_pack_start(GTK_BOX(content), scr, TRUE, TRUE, 0);
        GtkWidget* empty = gtk_label_new("Sin errores");
        gtk_box_pack_start(GTK_BOX(content), empty, FALSE, FALSE, 4);
    } else {
        GtkWidget* scr = gtk_scrolled_window_new(NULL,NULL);
        gtk_container_add(GTK_CONTAINER(scr), tree);
        gtk_box_pack_start(GTK_BOX(content), scr, TRUE, TRUE, 0);
    }

    gtk_widget_set_size_request(dialog, 700, 400);
    gtk_widget_show_all(dialog);
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
}

void gui_show_symbols_dialog(EditorState* st, const gchar* text){
    GtkWidget* dialog = gtk_dialog_new_with_buttons("Tabla de Símbolos",
        GTK_WINDOW(st->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "Cerrar", GTK_RESPONSE_CLOSE, NULL);
    GtkWidget* content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkListStore* store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
    GtkWidget* tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree), GTK_TREE_VIEW_GRID_LINES_BOTH);
    g_object_unref(store);
    append_column(store, GTK_TREE_VIEW(tree), "ID", 0);
    append_column(store, GTK_TREE_VIEW(tree), "Tipo símbolo", 1);
    append_column(store, GTK_TREE_VIEW(tree), "Tipo dato", 2);
    append_column(store, GTK_TREE_VIEW(tree), "Ámbito", 3);
    append_column(store, GTK_TREE_VIEW(tree), "Línea", 4);
    append_column(store, GTK_TREE_VIEW(tree), "Columna", 5);

    int added=0;
    if(text){
        gchar** lines = g_strsplit(text, "\n", -1);
        for(int i=0; lines[i]; i++){
            if(g_str_has_prefix(lines[i], "SYM|")){
                // Format: SYM|id|clase|tipo|ambito|line|col
                gchar** p = g_strsplit(lines[i]+4, "|", 7);
                GtkTreeIter it; gtk_list_store_append(store, &it);
                gchar* s0 = escape_for_gui(p[0]?p[0]:"");
                gchar* s1 = escape_for_gui(p[1]?p[1]:"");
                gchar* s2 = escape_for_gui(p[2]?p[2]:"");
                gchar* s3 = escape_for_gui(p[3]?p[3]:"");
                gtk_list_store_set(store, &it,
                    0, s0,
                    1, s1,
                    2, s2,
                    3, s3,
                    4, p[4]?atoi(p[4]):0,
                    5, p[5]?atoi(p[5]):0,
                    -1);
                g_free(s0); g_free(s1); g_free(s2); g_free(s3);
                g_strfreev(p); added++;
            }
        }
        g_strfreev(lines);
    }

    GtkWidget* scr = gtk_scrolled_window_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(scr), tree);
    gtk_box_pack_start(GTK_BOX(content), scr, TRUE, TRUE, 0);
    if(added==0){
        GtkWidget* info = gtk_label_new("No se encontró información de símbolos en la salida.");
        gtk_box_pack_start(GTK_BOX(content), info, FALSE, FALSE, 6);
    }
    gtk_widget_set_size_request(dialog, 750, 420);
    gtk_widget_show_all(dialog);
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
}
