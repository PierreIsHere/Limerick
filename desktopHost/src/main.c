/*
Author: Azfar C.
FileName: main.c
Purpose: Desktop host for the limerick ftp/server program
*/
#include"libs.h"

int clientLimit, port;
const char *ipAddr;
GtkWidget *mainWindow,*mainStack;
GtkWidget *mainPage,*portEditToggle,*portEntry,*ipAddrEntry;
GtkWidget *toggleServerBtn,*lblServerToggle;

void * clientThread(void *arg)
{
    int clientSocket = *((int *)arg);
    /*
    *should be receiving inputs from the client
    *for data calls from database 
    */
    close(clientSocket);
    pthread_exit(NULL);
}

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
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    if(state){
        gtk_label_set_text(GTK_LABEL(lblServerToggle),"Stop Server");
        printf("asdssssssssss");
        //Creating the host socket 
        serverSocket = socket(PF_INET, SOCK_STREAM, 0);
        
        // Configuring family, port and address
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(ipAddr);
        
        //Convention of padding the socket structure
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
        
        //Combining socket with supplied information
        bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

        //Setting the socket to listen with a clientLimit amount of connections qeued 
        if(listen(serverSocket,clientLimit)==0){
            printf("Listening\n");
        }else{
            /*
            *Implement a popup indicating the user that there is a connection error
            */
            printf("Error\n");
        }
        /*
        *Need to implement a client handler to take care of incoming clients 
        *while user continues to use application
        */

        //Instantiating an array of thread identifiers
        pthread_t threadID[clientLimit];
        int i = 0;
        for(;;){

            //Accept call creates a new socket for the incoming connection
            addr_size = sizeof serverStorage;
            clientSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

            //for each client request creates a thread and assign the client request to it to process
            //so the main thread can entertain next request
            if( pthread_create(&threadID[i], NULL, clientThread, &clientSocket) != 0 )
                printf("Failed to create thread\n");
            if( i >= clientLimit)
            {
                i = 0;
                while(i < clientLimit)
                {
                pthread_join(threadID[i++],NULL);
                }
                i = 0;
            }
        }
    }else{
        gtk_label_set_text(GTK_LABEL(lblServerToggle),"Start Server");
        //disconnect
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

    //Loading signals (user actions/function routing) from glade file
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    //Starting the gui
    gtk_widget_show(mainWindow);                
    gtk_main();
    return 0;
}


