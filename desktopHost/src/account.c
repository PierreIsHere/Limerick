#include "account.h"
int login(int sock){
    char *msg,rcv[100];
    msg ="1)Login\n2)Sign-Up\n3)Forgot Password\n";
    write(sock , msg , strlen(msg));	
    recv(sock , rcv , 2000 , 0)
}