#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <unistd.h>
#include <arpa/inet.h>


#define BUF_SIZE	1024
#define SERVER_IP	"127.0.0.1"
#define	SERVER_PORT	60000



struct play{
	char x,y;
	char *c;
};



int main(int argc, char *argv[]){
    int			sock_send;
    struct sockaddr_in	addr_send;
    char			text[8], buf[BUF_SIZE];
    int			send_len, bytes_sent;
    
    int num1, num2;
    char * letter;
    
    char result[8];
    
    int z;

    char x,y,ltr;
        /* create socket for sending data */

    struct play p;



    sock_send=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_send < 0){
        printf("socket() failed\n");
        exit(0);
    }



            /* fill the address structure for sending data */
    memset(&addr_send, 0, sizeof(addr_send));  /* zero out structure */
    addr_send.sin_family = AF_INET;  /* address family */
    addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_send.sin_port = htons((unsigned short)SERVER_PORT);




    while(1){
        printf("enter the coordinates and letter to play or 'q' to quit:\n");
        for (z = 0; z < 3; ++z)
        {
            scanf("%s",&text[z]);
            break;
        }

        if (strcmp(text,"q") == 0)
            break;
        strcpy(buf,text);
        send_len=strlen(text);
        bytes_sent=sendto(sock_send, buf, send_len, 0,(struct sockaddr *) &addr_send, sizeof(addr_send));
        }

    close(sock_send);
}