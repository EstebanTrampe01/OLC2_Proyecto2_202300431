#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "editor_state.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>

/* Escapa bytes no-UTF8 y ciertos controles a secuencias \uXXXX para evitar GTK-CRITICAL al insertar en GtkTextBuffer.
   - Mantiene \n, \r y \t sin cambios.
   - Si encuentra una secuencia UTF-8 inválida, escapa el byte problemático como \u00XX (hex mayúsculas) y continúa. */
static gchar* escape_for_gui_console(const char* in){
	if(!in) return g_strdup("");
	const unsigned char* p = (const unsigned char*)in;
	GString* out = g_string_sized_new(strlen(in) + 16);
	while(*p){
		/* ASCII rápido */
		if(*p < 0x80){
			unsigned char c = *p;
			if(c == '\n' || c == '\r' || c == '\t'){
				g_string_append_c(out, (char)c);
			} else if(c < 0x20 || c == 0x7F){
				g_string_append_printf(out, "\\u%04X", (unsigned int)c);
			} else {
				g_string_append_c(out, (char)c);
			}
			p++; continue;
		}
		/* Intentar decodificar UTF-8; si no es válido, escapar byte */
		gunichar ch = g_utf8_get_char_validated((const gchar*)p, -1);
		if(ch == (gunichar)-1){
			/* Mapear byte Latin-1 0x80-0xFF a Unicode U+0080..U+00FF y emitir UTF-8 */
			gunichar u = (gunichar)(*p);
			char buf[6]; int n = g_unichar_to_utf8(u, buf);
			g_string_append_len(out, buf, n);
			p++; continue;
		} else if(ch == (gunichar)-2){
			/* Secuencia truncada al final: escapar bytes restantes */
			while(*p){
				gunichar u = (gunichar)(*p);
				char buf[6]; int n = g_unichar_to_utf8(u, buf);
				g_string_append_len(out, buf, n);
				p++;
			}
			break;
		} else {
			/* Válido: copiar la secuencia original */
			const gchar* next = g_utf8_next_char((const gchar*)p);
			g_string_append_len(out, (const gchar*)p, next - (const gchar*)p);
			p = (const unsigned char*)next;
		}
	}
	return g_string_free(out, FALSE);
}

static void set_status(EditorState *st, const char *msg){
	gtk_label_set_text(GTK_LABEL(st->status_label), msg);
}

static void update_title(EditorState *st){
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	gboolean mod = gtk_text_buffer_get_modified(buf);
	const gchar *name = st->current_path ? st->current_path : "(sin nombre)";
	gchar *title = g_strdup_printf("Editor USL%s - %s", mod?"*":"", name);
	gtk_window_set_title(GTK_WINDOW(st->window), title);
	g_free(title);
}

static gboolean ask_save_if_modified(EditorState *st);

static gboolean save_to(EditorState *st, const char *path){
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	GtkTextIter start, end; gtk_text_buffer_get_start_iter(buf,&start); gtk_text_buffer_get_end_iter(buf,&end);
	char *text = gtk_text_buffer_get_text(buf,&start,&end,FALSE);
	/* asegurar .usl */
	gchar *target = NULL;
	if (g_str_has_suffix(path, ".usl")) target = g_strdup(path);
	else target = g_strconcat(path, ".usl", NULL);
	FILE *f = fopen(target, "w");
	if(!f){ set_status(st, "Error guardando archivo"); g_free(text); g_free(target); return FALSE; }
	fwrite(text,1,strlen(text),f); fclose(f);
	g_free(text);
	g_free(st->current_path); st->current_path = g_strdup(target);
	gtk_text_buffer_set_modified(buf, FALSE);
	update_title(st);
	set_status(st, "Guardado");
	g_free(target);
	return TRUE;
}

static void new_file_cb(GtkWidget *w, gpointer data){
	(void)w; EditorState *st = (EditorState*)data;
	if(!ask_save_if_modified(st)) return;
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	gtk_text_buffer_set_text(buf, "", -1);
	g_clear_pointer(&st->current_path, g_free);
	gtk_text_buffer_set_modified(buf, FALSE);
	update_title(st);
	set_status(st, "Nuevo archivo");
}

static void on_modified_changed(GtkTextBuffer *buffer, gpointer data){
	(void)buffer; EditorState *st=(EditorState*)data; update_title(st);
}

static void load_path(EditorState *st, const char *path){
	FILE *f = fopen(path, "r");
	if(!f){ set_status(st, "No se pudo abrir"); return; }
	fseek(f,0,SEEK_END); long len=ftell(f); fseek(f,0,SEEK_SET);
	char *content = g_malloc(len+1);
	size_t rd=fread(content,1,len,f); content[rd]='\0'; fclose(f);
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	gtk_text_buffer_set_text(buf, content, -1);
	g_free(content);
	g_free(st->current_path); st->current_path = g_strdup(path);
	gtk_text_buffer_set_modified(buf, FALSE);
	update_title(st);
	set_status(st, path);
}

static void open_file_cb(GtkWidget *w, gpointer data){
	(void)w; EditorState *st=(EditorState*)data;
	if(!ask_save_if_modified(st)) return;
	GtkWidget *dlg = gtk_file_chooser_dialog_new("Abrir .usl", GTK_WINDOW(st->window), GTK_FILE_CHOOSER_ACTION_OPEN,
		"Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT, NULL);
	GtkFileFilter *filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter, "*.usl");
	gtk_file_filter_set_name(filter, "Archivos USL");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dlg), filter);
	if(gtk_dialog_run(GTK_DIALOG(dlg)) == GTK_RESPONSE_ACCEPT){
		char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dlg));
		load_path(st, filename);
		g_free(filename);
	}
	gtk_widget_destroy(dlg);
}

static void save_file_cb(GtkWidget *w, gpointer data){
	(void)w; EditorState *st=(EditorState*)data;
	if(st->current_path){ save_to(st, st->current_path); return; }
	GtkWidget *dlg = gtk_file_chooser_dialog_new("Guardar .usl", GTK_WINDOW(st->window), GTK_FILE_CHOOSER_ACTION_SAVE,
		"Cancelar", GTK_RESPONSE_CANCEL, "Guardar", GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dlg), TRUE);
	GtkFileFilter *filter = gtk_file_filter_new(); gtk_file_filter_add_pattern(filter, "*.usl"); gtk_file_filter_set_name(filter, "Archivos USL");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dlg), filter);
	if(gtk_dialog_run(GTK_DIALOG(dlg)) == GTK_RESPONSE_ACCEPT){
		char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dlg));
		save_to(st, filename);
		g_free(filename);
	}
	gtk_widget_destroy(dlg);
}

static gboolean ask_save_if_modified(EditorState *st){
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	if(!gtk_text_buffer_get_modified(buf)) return TRUE;
	GtkWidget *md = gtk_message_dialog_new(GTK_WINDOW(st->window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE,
		"Guardar cambios?");
	gtk_dialog_add_buttons(GTK_DIALOG(md), "Cancelar", GTK_RESPONSE_CANCEL, "Descartar", GTK_RESPONSE_REJECT, "Guardar", GTK_RESPONSE_ACCEPT, NULL);
	gint r = gtk_dialog_run(GTK_DIALOG(md));
	gtk_widget_destroy(md);
	if(r == GTK_RESPONSE_ACCEPT){ save_file_cb(NULL, st); return !gtk_text_buffer_get_modified(buf); }
	if(r == GTK_RESPONSE_REJECT){ return TRUE; }
	return FALSE;
}

/* placeholder_cb eliminado (no usado) */

/* Ejecutar: toma el contenido del editor, lo guarda en tmp y ejecuta ./build/calc mostrando salida en consola */
/* Filtra líneas que comienzan con 'SYM|' (tabla de símbolos) para que no 
   aparezcan en la consola principal del editor, manteniendo la data intacta
   para los diálogos (Errores / Símbolos) que invocan gui_run_calc_with_buffer
   de forma independiente. */
static gchar* filter_console_output(const gchar* original){
	if(!original) return g_strdup("(sin salida)");
	gchar** lines = g_strsplit(original, "\n", -1);
	GString* filtered = g_string_sized_new(strlen(original));
	for(int i=0; lines[i]; i++){
		if(g_str_has_prefix(lines[i], "SYM|")){
			continue; /* omitir línea de símbolo */
		}
		g_string_append(filtered, lines[i]);
		if(lines[i+1]) g_string_append_c(filtered, '\n');
	}
	g_strfreev(lines);
	return g_string_free(filtered, FALSE);
}

static void run_program_cb(GtkWidget *w, gpointer data){
	(void)w; EditorState *st=(EditorState*)data;
	gchar* combined = gui_run_calc_with_buffer(GTK_TEXT_VIEW(st->text_view));
	gchar* filtered = filter_console_output(combined);
	GtkTextBuffer *cbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->console_view));
	gchar* shown = escape_for_gui_console(filtered);
	gtk_text_buffer_set_text(cbuf, shown, -1);
	g_free(shown);
	g_free(filtered);
	/* auto scroll al final */
	GtkTextIter endIter; gtk_text_buffer_get_end_iter(cbuf, &endIter);
	GtkWidget *scroll = gtk_widget_get_parent(st->console_view); /* scrolled window */
	if(GTK_IS_SCROLLED_WINDOW(scroll)){
		GtkAdjustment *vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll));
		gtk_adjustment_set_value(vadj, gtk_adjustment_get_upper(vadj));
	}
	set_status(st, "Ejecución finalizada");
	if(combined) g_free(combined);
}

static void show_errors_cb(GtkWidget* w, gpointer data){ (void)w; EditorState* st=(EditorState*)data; gchar* combined = gui_run_calc_with_buffer(GTK_TEXT_VIEW(st->text_view)); gui_show_errors_dialog(st, combined); if(combined) g_free(combined); }
static void show_symbols_cb(GtkWidget* w, gpointer data){ (void)w; EditorState* st=(EditorState*)data; gchar* combined = gui_run_calc_with_buffer(GTK_TEXT_VIEW(st->text_view)); gui_show_symbols_dialog(st, combined); if(combined) g_free(combined); }

/* Cargar CSS embebido o externo opcional (gui/style.css) */
static void load_css(void){
	GtkCssProvider *prov = gtk_css_provider_new();
	const gchar *fallback =
		"window { background: #1e1e1e; color: #ddd; }"
		"textview, textview text { font-family: 'Fira Code', monospace; font-size: 12px; }"
		"#editor-view { background: #252526; color: #e0e0e0; }"
		"#console-view { background: #111; color: #c8c8c8; }"
		"headerbar { background: linear-gradient(#323233,#252526); border-bottom: 1px solid #444; }"
		"button { border-radius: 4px; padding: 4px 10px; }"
		"button.suggested-action { background: #0e639c; color: white; }"
		"button.suggested-action:hover { background: #1177bb; }"
		"label#status-label { padding: 4px 8px; background: #323233; color: #bbb; }";
	GError *err=NULL;
	if(g_file_test("gui/style.css", G_FILE_TEST_EXISTS)){
		gtk_css_provider_load_from_path(prov, "gui/style.css", &err);
		if(err){ g_error_free(err); gtk_css_provider_load_from_data(prov, fallback, -1, NULL); }
	} else {
		gtk_css_provider_load_from_data(prov, fallback, -1, NULL);
	}
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(prov), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	g_object_unref(prov);
}

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
	(void)widget; EditorState *st = (EditorState*)user_data;
	guint state = event->state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK|GDK_MOD1_MASK);
	if((state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_s || event->keyval == GDK_KEY_S)){
		save_file_cb(NULL, st); return TRUE;
	}
	if((state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_o || event->keyval == GDK_KEY_O)){
		open_file_cb(NULL, st); return TRUE;
	}
	if(event->keyval == GDK_KEY_F5){ run_program_cb(NULL, st); return TRUE; }
	if(event->keyval == GDK_KEY_F6){ gui_generate_ast_report(NULL, st); return TRUE; }
	if(event->keyval == GDK_KEY_F9){ show_errors_cb(NULL, st); return TRUE; }
	if(event->keyval == GDK_KEY_F10){ show_symbols_cb(NULL, st); return TRUE; }
	return FALSE;
}

static GtkWidget* build_header_bar(EditorState *st G_GNUC_UNUSED,
								   GtkWidget **btn_new,
								   GtkWidget **btn_open,
								   GtkWidget **btn_save,
								   GtkWidget **btn_run,
								   GtkWidget **btn_err,
								   GtkWidget **btn_sym,
								   GtkWidget **btn_ast){
	GtkWidget *hb = gtk_header_bar_new();
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(hb), TRUE);
	gtk_header_bar_set_title(GTK_HEADER_BAR(hb), "Editor USL");

	*btn_new = gtk_button_new_from_icon_name("document-new", GTK_ICON_SIZE_BUTTON);
	*btn_open = gtk_button_new_from_icon_name("document-open", GTK_ICON_SIZE_BUTTON);
	*btn_save = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_BUTTON);
	*btn_run  = gtk_button_new_with_label("▶ Ejecutar");
	*btn_err  = gtk_button_new_with_label("Errores");
	*btn_sym  = gtk_button_new_with_label("Símbolos");
	*btn_ast  = gtk_button_new_with_label("AST");

	gtk_widget_set_tooltip_text(*btn_new, "Nuevo (Ctrl+N)");
	gtk_widget_set_tooltip_text(*btn_open, "Abrir (Ctrl+O)");
	gtk_widget_set_tooltip_text(*btn_save, "Guardar (Ctrl+S)");
	gtk_widget_set_tooltip_text(*btn_run, "Ejecutar (F5)");
	gtk_widget_set_tooltip_text(*btn_err,  "Tabla de Errores (F9)");
	gtk_widget_set_tooltip_text(*btn_sym,  "Tabla de Símbolos (F10)");
	gtk_widget_set_tooltip_text(*btn_ast,  "Generar AST (F6)");

	gtk_style_context_add_class(gtk_widget_get_style_context(*btn_run), "suggested-action");

	GtkWidget *box_left = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
	gtk_container_add(GTK_CONTAINER(box_left), *btn_new);
	gtk_container_add(GTK_CONTAINER(box_left), *btn_open);
	gtk_container_add(GTK_CONTAINER(box_left), *btn_save);
	gtk_container_add(GTK_CONTAINER(box_left), *btn_run);

	GtkWidget *box_right = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
	gtk_container_add(GTK_CONTAINER(box_right), *btn_err);
	gtk_container_add(GTK_CONTAINER(box_right), *btn_sym);
	gtk_container_add(GTK_CONTAINER(box_right), *btn_ast);

	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), box_left);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(hb), box_right);
	return hb;
}

static void activate(GtkApplication* app, gpointer user_data){
	(void)user_data;
	EditorState *st = g_new0(EditorState, 1);
	st->window = gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(st->window), 950, 620);

	/* Header bar moderno */
	GtkWidget *btn_new=NULL,*btn_open=NULL,*btn_save=NULL,*btn_run=NULL,*btn_err=NULL,*btn_sym=NULL,*btn_ast=NULL;
	GtkWidget *hb = build_header_bar(st, &btn_new,&btn_open,&btn_save,&btn_run,&btn_err,&btn_sym,&btn_ast);
	gtk_window_set_titlebar(GTK_WINDOW(st->window), hb);

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(st->window), vbox);

	/* Panel dividido: editor arriba, consola abajo */
	GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(vbox), paned, TRUE, TRUE, 0);

	st->text_view = gtk_text_view_new();
	gtk_widget_set_name(st->text_view, "editor-view");
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(st->text_view), TRUE);
	GtkWidget *scroll_editor = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scroll_editor), st->text_view);
	gtk_paned_pack1(GTK_PANED(paned), scroll_editor, TRUE, FALSE);

	st->console_view = gtk_text_view_new();
	gtk_widget_set_name(st->console_view, "console-view");
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(st->console_view), TRUE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(st->console_view), FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(st->console_view), FALSE);
	GtkWidget *scroll_console = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scroll_console), st->console_view);
	gtk_paned_pack2(GTK_PANED(paned), scroll_console, TRUE, FALSE);
	gtk_paned_set_position(GTK_PANED(paned), 420);

	/* Barra de estado */
	st->status_label = gtk_label_new("Listo");
	gtk_widget_set_name(st->status_label, "status-label");
	gtk_box_pack_start(GTK_BOX(vbox), st->status_label, FALSE, FALSE, 0);

	/* Signals */
	g_signal_connect(btn_new,  "clicked", G_CALLBACK(new_file_cb), st);
	g_signal_connect(btn_open, "clicked", G_CALLBACK(open_file_cb), st);
	g_signal_connect(btn_save, "clicked", G_CALLBACK(save_file_cb), st);
	g_signal_connect(btn_run,  "clicked", G_CALLBACK(run_program_cb), st);
	g_signal_connect(btn_err,  "clicked", G_CALLBACK(show_errors_cb), st);
	g_signal_connect(btn_sym,  "clicked", G_CALLBACK(show_symbols_cb), st);
	g_signal_connect(btn_ast,  "clicked", G_CALLBACK(gui_generate_ast_report), st);
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(st->text_view));
	g_signal_connect(buf, "modified-changed", G_CALLBACK(on_modified_changed), st);
	g_signal_connect(st->window, "key-press-event", G_CALLBACK(on_key_press), st);

	load_css();

	g_object_set_data_full(G_OBJECT(st->window), "editor-state", st, (GDestroyNotify)g_free);
	update_title(st);
	gtk_widget_show_all(st->window);
}

int main(int argc, char **argv){
	GtkApplication *app = gtk_application_new("com.usl.editor", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}

