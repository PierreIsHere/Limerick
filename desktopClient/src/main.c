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
void on_window_main_destroy();
int connect();
int sock =0;



GtkWidget *g_lbl_hello;
GtkWidget *g_lbl_count;
void on_btn_hello_clicked();
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/login.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "loginWindow"));
    gtk_builder_connect_signals(builder, NULL);
    
    // get pointers to the two labels
    g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void on_btn_hello_clicked()
{
    static unsigned int count = 0;
    char str_count[30] = {0};
    
    gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Hello, world!");
    count++;
    sprintf(str_count, "%d", count);
    gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
}

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
       
//     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
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

void on_loginWindow_main_destroy()
{
    puts("Program teminating");
    gtk_main_quit();
}

void click()
{
    puts("Button Clicked");
}