/*
Author: Azfar C.
FileName: main.c
Purpose: Desktop client for the limerick ftp/server program
*/
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <pthread.h>
#include <gtk/gtk.h>


const gchar *ipAddr,*portN;
int port, sock=0;

GtkWidget *mainWindow,*mainStack;
GtkWidget *serverPage,*ipAddrBox,*portNum;
GtkWidget *loginPage,*displayName,*clientServerKey,*clinetSubmitBtn,*lbl_login;


void *input(){
    char inp[200];
    // for(;;){
    // scanf("%s",inp);
    send((long)sock , "This is a message from a socket" , 34,0);
    // }
    pthread_exit(NULL);
}
void *output(){
    printf("Receiving Output\n");
    char buffer[1024];
    for(;;){
        if(read((long)sock,buffer,1024)>0){
            printf("Received - %s\n",buffer);
        }
    }
    pthread_exit(NULL);
}

void msgBox(char*header,char*message){
    
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,message);
  gtk_window_set_title(GTK_WINDOW(dialog),header);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void loginServer(){
    const gchar *dispName =  gtk_entry_get_text(displayName);
    const gchar *serverKey = gtk_entry_get_text(clientServerKey);
    send((long)sock,displayName,strlen(displayName),0); 
    send((long)sock,serverKey,strlen(serverKey),0); 
}

int submitServer(){
    portN = gtk_entry_get_text(portNum);
    port = atoi(portN);
    ipAddr= gtk_entry_get_text(ipAddrBox);
    g_print(ipAddr);
    printf(":%d\n",port);

    /***********Socket Code*********************/
    struct sockaddr_in serv_addr; 
    pthread_t inThread,outThread; 
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        msgBox("Error","Connection Error");
        return -1;
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    if(inet_pton(AF_INET,ipAddr, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n");
        msgBox("Error","Invalid/ Unsupported Address");
        return -1;
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n");
        msgBox("Error","Connection Failure");
        return -1;
    }
    printf("%d\n",socket);
    pthread_create(&inThread, NULL, input,0); 
    pthread_create(&outThread, NULL, output,0); 
    /****************************************/
    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
    
}

void goto_loginPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
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
    portNum = GTK_WIDGET(gtk_builder_get_object(builder, "portNum"));

    loginPage = GTK_WIDGET(gtk_builder_get_object(builder, "loginPage"));
    displayName = GTK_WIDGET(gtk_builder_get_object(builder, "displayName"));
    clientServerKey = GTK_WIDGET(gtk_builder_get_object(builder, "clientServerKey"));
    lbl_login = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_login"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(mainWindow);                
    gtk_main();

    return 0;
}


