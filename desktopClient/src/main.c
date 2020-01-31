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
int port, sock=0, redo=0,row=0;
char *files[1000];
int buttonContent[8];

//Initialization of gtk objects
GtkWidget	*button[8];
GtkWidget *mainWindow,*mainStack;
GtkWidget *serverPage,*ipAddrBox,*portNum;
GtkWidget *loginPage,*displayName,*clientServerKey,*clinetSubmitBtn,*lbl_login;
GtkWidget *mainPage,*btnGrid,*btnScroll;

//generates an error popup where called
void msgBox(char*header,char*message){
    
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,message);
  gtk_window_set_title(GTK_WINDOW(dialog),header);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
//prints out which file has been selected
void on_row(GtkButton *b) {
	printf("You selected: %s\n", gtk_button_get_label (b));
	}
//validates that user can access server with inputed key
void loginServer(){
    const gchar *dispName =  gtk_entry_get_text(GTK_ENTRY(displayName));
    const gchar *serverKey = gtk_entry_get_text(GTK_ENTRY(clientServerKey));
    char keyLen[20],rcv[20];
    if(redo == 0){
    snprintf(keyLen, strlen(keyLen), "%d", (int)strlen(serverKey));
    send((long)sock,dispName,200,0);
    }
    send((long)sock,serverKey,200,0);
    recv((long)sock,rcv,20,0);
    puts(rcv);
    if(strcmp(rcv,"1")==0){
        gotoMainPage();
        
        puts("Verified");
    }else{
        redo = 1;
        msgBox("Error","Incorrect Key!");
    }

}
void gotoMainPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),mainPage);
    int i=0;
    struct dirent *de;
  
    DIR *dr = opendir("download/"); 
    if (dr == NULL)
    { 
        printf("Could not open current directory" ); 
    } 

    while ((de = readdir(dr)) != NULL)
            files[i++]=de->d_name;
    closedir(dr);      
    for(int f=0;f<i;f++){
    puts(files[f]);
    }

	row = 0;
	while (row<8) {

	// The following code populates the grid with buttons.

    if (row < 8 ) {
        gtk_grid_insert_row (GTK_GRID(btnGrid), row);
        button[row] = gtk_button_new_with_label (files[row]);
        gtk_button_set_alignment (GTK_BUTTON(button[row]), 0.0, 0.5);
        gtk_grid_attach (GTK_GRID(btnGrid), button[row], 1, row, 1, 1);
        g_signal_connect(button[row], "clicked", G_CALLBACK(on_row), NULL);
        buttonContent[row] = row; // current button content
        }
    row ++;
    }

	gtk_range_set_range (GTK_RANGE(btnScroll), 0, row ); // establish range

}

//telling what the program to do when the scrollbar is used
void btnScrolled(GtkRange *r) {
	int i,j;

	i = (int) gtk_range_get_value (r);

	if (i >= row) i = row - 8; // last page
    //"moving" the file names up and down proportional to the scrollbars movement
	for (j = i; j < i + 8; j++) {
		if (j < row){ 
			gtk_button_set_label (GTK_BUTTON( button[j - i] ), (const gchar* ) files[j]);
			puts(files[j]);
		}else
			gtk_button_set_label (GTK_BUTTON( button[j - i] ), (const gchar* ) " ");
		buttonContent[j-i] = j;
		}
	}

//connection attempt to serveer
int submitServer(){
    portN = gtk_entry_get_text(portNum);
    port = atoi(portN);
    ipAddr= gtk_entry_get_text(ipAddrBox);
    g_print(ipAddr);
    printf(":%d\n",port);

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

    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
    
}

void goto_loginPage(){
    gtk_stack_set_visible_child (GTK_STACK(mainStack),loginPage);
    // char msg[200];
    // strcpy(msg,"Login to: ");
    // strcat(msg,(char *)ipAddr);
    // strcat(msg,'\0');
    // puts(msg);
    // gtk_label_set_text(GTK_LABEL(lbl_login),msg);
}

void on_window_destroy(){
    puts("Program Terminated");
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    //Taking commandline arguments (if provided)
    gtk_init(&argc, &argv);

    //Getting template of gui from glade file
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "share/templates/main.glade", NULL);

    //Identifying objects by id from the gui (linking front-end and back-end)
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));

    serverPage = GTK_WIDGET(gtk_builder_get_object(builder, "serverPage"));    
    ipAddrBox = GTK_WIDGET(gtk_builder_get_object(builder, "ipAddr"));
    portNum = GTK_WIDGET(gtk_builder_get_object(builder, "portNum"));

    loginPage = GTK_WIDGET(gtk_builder_get_object(builder, "loginPage"));
    displayName = GTK_WIDGET(gtk_builder_get_object(builder, "displayName"));
    clientServerKey = GTK_WIDGET(gtk_builder_get_object(builder, "clientServerKey"));
    lbl_login = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_login"));

    mainPage = GTK_WIDGET(gtk_builder_get_object(builder, "mainPage"));
    btnGrid = GTK_WIDGET(gtk_builder_get_object(builder, "btnGrid"));
    btnScroll = GTK_WIDGET(gtk_builder_get_object(builder, "btnScroll"));

    //Loading signals (user actions/function routing) from glade file
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    //Starting the gui
    gtk_widget_show(mainWindow);                
    gtk_main();

    return 0;
}


