#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <pthread.h>
#include <gtk/gtk.h>
#define PORT 8888 

void *input();
void *output();
int connect();
int sock =0;
const gchar *ipAddr;

GtkWidget *ipAddrBox;
GtkWidget *ipPop;
GtkBuilder *builder;
GtkWidget *window;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/login.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "loginWindow"));
    ipPop = GTK_WIDGET(gtk_builder_get_object (builder, "ipPop"));
    ipAddrBox = GTK_WIDGET(gtk_builder_get_object(builder, "ipAddr"));

    gtk_builder_connect_signals(builder, NULL);    
    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void submitServer(){
    ipAddr= gtk_entry_get_text(ipAddrBox);
    g_print(ipAddr);
    // if(connect()){
    //     //go to next page 
    // }else{
    //     //Dialog Box
    // }
    gtk_dialog_run(GTK_DIALOG(ipPop));
    
}

void on_loginWindow_destroy()
{
    puts("Program Terminated");
    gtk_main_quit();
}

void destroyIpPop(){
    gtk_widget_hide(GTK_WIDGET(ipPop));
    ipPop = GTK_WIDGET(gtk_builder_get_object (builder, "ipPop"));
    puts("Closed Popup");
}
// Socket Code Below
// int connect(){ 
//     struct sockaddr_in serv_addr; 
//     pthread_t inThread,outThread; 
    
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
//     { 
//         printf("\n Socket creation error \n"); 
//         return -1; 
//     } 
   
//     serv_addr.sin_family = AF_INET; 
//     serv_addr.sin_port = htons(PORT); 
       
//     if(inet_pton(AF_INET,ipAddr, &serv_addr.sin_addr)<=0)  
//     { 
//         printf("\nInvalid address/ Address not supported \n"); 
//         return -1; 
//     } 
   
//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
//     { 
//         printf("\nConnection Failed \n"); 
//         return -1; 
//     }
//     pthread_create(&inThread, NULL, input,0); 
//     pthread_join(inThread, NULL);
//     pthread_create(&outThread, NULL, output,0); 
//     pthread_join(outThread, NULL); 
//     return 1; 
// }

// void *input(){
//     char inp[200];
//     for(;;){
//     scanf("%s",inp);
//     printf("%d\n",send((long)sock , inp , strlen(inp),0));
//     }
    
// }
// void *output(){
//     char buffer[1024];
//     for(;;){
//         if(read((long)sock,buffer,1024)>0){
//             printf("%s",buffer);
//         }
//     }
// }
