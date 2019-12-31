/*
Author: Azfar C.
FileName: main.c
Purpose: Desktop client for the limerick ftp/server program
*/
#include <gtk/gtk.h>


const gchar *ipAddr;

GtkWidget *mainWindow,*mainStack;
GtkWidget *serverPage,*ipAddrBox;
GtkWidget *loginPage,*userName,*userPass;
GtkWidget *signupPage;
GtkWidget *passRecovPage;


void submitServer(){
    ipAddr= gtk_entry_get_text(ipAddrBox);
    g_print(ipAddr);
    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
}
void login(){
    const gchar *uName,*uPass;
    uName = gtk_entry_get_text(userName);
    uPass = gtk_entry_get_text(userPass);
}
void goto_loginPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
}
void goto_signupPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),signupPage);
}
void goto_recovPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),passRecovPage);    
}

void on_window_destroy(){
    puts("Program Terminated");
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/main.glade", NULL);

    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));

    serverPage = GTK_WIDGET(gtk_builder_get_object(builder, "serverPage"));    
    ipAddrBox = GTK_WIDGET(gtk_builder_get_object(builder, "ipAddr"));

    loginPage = GTK_WIDGET(gtk_builder_get_object(builder, "loginPage"));

    signupPage = GTK_WIDGET(gtk_builder_get_object(builder, "signupPage"));

    passRecovPage = GTK_WIDGET(gtk_builder_get_object(builder, "passRecovPage"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(mainWindow);                
    gtk_main();

    return 0;
}


