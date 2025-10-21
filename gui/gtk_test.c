#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data){
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Test Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    GtkWidget *label = gtk_label_new("GTK está funcionando");
    gtk_container_add(GTK_CONTAINER(window), label);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv){
    GtkApplication *app = gtk_application_new("org.usl.gtk_test", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
