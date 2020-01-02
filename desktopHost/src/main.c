/*
Author: Azfar C.
FileName: main.c
Purpose: Desktop host for the limerick ftp/server program
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <gtk/gtk.h>

const char *ipAddr;
GtkWidget *mainWindow,*mainStack;
GtkWidget *mainPage,*portEditToggle,*portEntry,*ipAddrEntry;
GtkWidget *toggleServerBtn,*lblServerToggle;

char* getIpAddr() 
{ 
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
} 

void portEditToggled(){
    gboolean state;
    state = gtk_toggle_button_get_active(portEditToggle);
    if(state){
        gtk_widget_set_sensitive(portEntry,TRUE);
    }else{
        gtk_widget_set_sensitive(portEntry,FALSE);
    }
}

void toggleServer(GtkToggleButton *toggleBtn){
    gboolean state;
    state = gtk_toggle_button_get_active(toggleBtn);
    if(state){
        gtk_label_set_text(GTK_LABEL(lblServerToggle),"Stop Server");
    }else{
        gtk_label_set_text(GTK_LABEL(lblServerToggle),"Start Server");
    }
}

void on_window_destroy(){
    puts("Program Terminated");
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    ipAddr = getIpAddr();
    //Taking commandline arguments (if provided)
    gtk_init(&argc, &argv);
    
    //Getting template of gui from glade file
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/main.glade", NULL);
    
    //Getting styling for gui from css file
    if( gtk_css_provider_load_from_path(cssProvider, "share/styles/style.css", NULL) )
    {
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    
    //Identifying objects by id from the gui (linking front-end and back-end)    
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));

    mainPage = GTK_WIDGET(gtk_builder_get_object(builder, "mainPage"));

    ipAddrEntry = GTK_WIDGET(gtk_builder_get_object(builder, "ipAddrEntry"));
    gtk_entry_set_text(GTK_ENTRY(ipAddrEntry),ipAddr);
    gtk_entry_set_width_chars(GTK_ENTRY(ipAddrEntry),strlen(ipAddr)-2);

    portEntry = GTK_WIDGET(gtk_builder_get_object(builder, "portEntry"));
    portEditToggle = GTK_WIDGET(gtk_builder_get_object(builder, "portEditToggle"));
    
    toggleServerBtn = GTK_WIDGET(gtk_builder_get_object(builder, "toggleServerBtn"));
    lblServerToggle = GTK_WIDGET(gtk_builder_get_object(builder, "lblServerToggle"));

    //Loading signals (user actions) from glade file
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    //Starting the gui
    gtk_widget_show(mainWindow);                
    gtk_main();

    return 0;
}


