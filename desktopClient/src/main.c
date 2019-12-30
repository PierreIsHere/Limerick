#include <gtk/gtk.h>


void login();
void submitServer();
void on_window_destroy();
const gchar *ipAddr;

typedef struct limerickGUI{
    GtkWidget *mainWindow,*mainStack;
    GtkWidget *serverPage,*ipAddrBox,*submitServer;
    GtkWidget *loginPage,*userName, *userPass;
}   limerickGUI;

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    limerickGUI mainProg;
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/logintest.glade", NULL);

    mainProg.mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    mainProg.mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));

    mainProg.serverPage = GTK_WIDGET(gtk_builder_get_object(builder, "serverPage"));    
    mainProg.ipAddrBox = GTK_WIDGET(gtk_builder_get_object(builder, "ipAddr"));
    mainProg.submitServer = GTK_WIDGET(gtk_builder_get_object(builder, "submitServer"));

    mainProg.loginPage = GTK_WIDGET(gtk_builder_get_object(builder, "loginPage"));

    g_signal_connect(mainProg.submitServer, "clicked", G_CALLBACK(submitServer), &mainProg);
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(mainProg.mainWindow);                
    gtk_main();

    return 0;
}
void submitServer(GtkWidget *widget, limerickGUI *mainProg){
    ipAddr= gtk_entry_get_text(mainProg->ipAddrBox);
    g_print(ipAddr);
    gtk_stack_set_visible_child (GTK_STACK(mainProg->mainStack), mainProg->loginPage);
}

// void login(){
//     const gchar *uName,*uPass;
//     uName = gtk_entry_get_text(mainProg.userName);
//     uPass = gtk_entry_get_text(mainProg.userPass);
// }

void on_window_destroy(){
    puts("Program Terminated");
    gtk_main_quit();
}

