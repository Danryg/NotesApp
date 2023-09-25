
#include <stdio.h>

#include <gtk/gtk.h>


typedef struct {
    int id;
    gchar *text;
} Pane;

typedef struct {
    int index;
    
} CallBackData;


const Pane panes[4] = {
    {1, "Test text 1"},
    {2, "Test text 2"},
    {3, "Test text 3"},
    {4, "Test text 4"}
};

Pane active_pane = panes[0];
GtkWidget *text_view;

static void save_pane(){
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    gchar *text;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE); // FALSE means text will not include hidden characters (like tags)
    
    // ... Do something with the text ...
    active_pane.text = text;
    
    g_free(text);
}


void setActivePane(Pane pane){
    GtkTextBuffer *buffer;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, pane.text, -1);
}


// Switch pane
// First, save tha prior pane
// Sould switch to a different pane when a option is clicked inside a drawer
static void switchPane(Pane *pane){
    
    //Save the current pane
    
    
    // Load the new pane
    
}


static void on_button_clicked(GtkButton *button, gpointer user_data) {
    // Handle the button click here.
    //setActivePane(panes[index]);
    CallBackData *data = (CallBackData *) user_data;
    printf("%d \n", &data->index);
}



static void on_activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    
    GtkWidget *scrolled_window;
    GtkWidget *box;
    GtkWidget *drawer_box;
    
    // Create a new window
    window = gtk_application_window_new(app);
    
    //Drawer -----------------------------------------------------------------------------------------
    //This is a widget
    drawer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    gtk_widget_set_size_request(GTK_WIDGET(drawer_box), 300, -1);
    
    
    //Buttons in Drawer ------------------------------------
    GtkWidget *button1;
    button1 = gtk_button_new_with_label("Button 1");
    gtk_box_pack_start(GTK_BOX(drawer_box), button1, FALSE, FALSE, 0);
    GtkWidget *button2;
    button2 = gtk_button_new_with_label("Button 2");
    gtk_box_pack_start(GTK_BOX(drawer_box), button2, FALSE, FALSE, 0);
    GtkWidget *button3;
    button3 = gtk_button_new_with_label("Button 3");
    gtk_box_pack_start(GTK_BOX(drawer_box), button3, FALSE, FALSE, 0);
    GtkWidget *button4;
    button4 = gtk_button_new_with_label("Button 4");
    gtk_box_pack_start(GTK_BOX(drawer_box), button4, FALSE, FALSE, 0);
    
    CallBackData data1 = {0};
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), &data1);
    CallBackData data2 = {1};
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), &data2);
    CallBackData data3 = {2};
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button_clicked), &data3);
    CallBackData data4 = {3};
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button_clicked), &data4);
    
    // TextView --------------------------------------------------------------------------------------
    // Create a new text view
    text_view = gtk_text_view_new();
    
    // Create a scrolled window
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    
    // Main Container -------------------------------------------------------------------------------
    //Create new box
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    gtk_box_pack_start(GTK_BOX(box), drawer_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);
    
    
    
    //-----------------------------------------------------------------------------------------------
    // Set window properties
    gtk_window_set_title(GTK_WINDOW(window), "My GTK Window with Multi-row Textfield");
    gtk_window_set_default_size(GTK_WINDOW(window), 1250, 1000);
    
    // Add the scrolled window (which contains the text view) to the main window
    gtk_container_add(GTK_CONTAINER(window), box);
    
    // Show all widgets within the window
    gtk_widget_show_all(window);
}


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("com.example.gtkwindow", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
