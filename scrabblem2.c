#include <stdio.h>
#include <sys/types.h>	/* system type defintions */
#include <sys/socket.h>	/* network system functions */
#include <netinet/in.h>	/* protocol & struct definitions */
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE	5
#define LISTEN_PORT	60000

int main(){


struct play
{
	int x,y;
	char *c;
};


int k,j;
int const NUM_RANGE=8;
//global declaration structure grid
char * grid[NUM_RANGE][NUM_RANGE];

    void getNewBoard(){
        //creates a brand new blank board. Returns a pointer to the array
        for (j = 0; j < NUM_RANGE; j++){
            for (k = 0; k < NUM_RANGE; k++)
            {
                grid[k][j]="   ";
            }//Endfor
        }//Endfor
        return;
    }//EndFunction getNewBoard

void drawBoard(){
    //This function prints out the board that was passed. Returns void
    char * const NLINE = "    1    2    3    4    5    6    7    8";
    char * const HLINE = "  +----+----+----+----+----+----+----+----+";
    char * const VLINE = "  |    |    |    |    |    |    |    |    |";

    printf("%s\n",NLINE);
    printf("%s\n",HLINE);
    for (j = 0; j < NUM_RANGE; j++)
    {
        printf("%s\n",VLINE);
        printf("%d ",j+1);
        for (k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                printf("| %s",grid[k][j]);
            }else{
                printf("| %s  ",grid[k][j]);
            }
        }
        printf("%s","|");
        printf("\n");
        printf("%s\n",VLINE);
        printf("%s\n",HLINE);
    }
    return;
}//EndFunction drawBoard


void makePlay(int x, int y, char* c){
   //Arrays are zero indexed but our grid starts at index 1
   grid[x-1][y-1]=c;
   return;
}

//server function
int server()
{
    int			sock_recv;
    struct sockaddr_in	my_addr;
    int			i;
    fd_set	readfds,active_fd_set,read_fd_set;
    struct timeval		timeout={0,0};
    int			incoming_len;
    struct sockaddr_in	remote_addr;
    int			recv_msg_size;
    char		buf[BUF_SIZE];
    int			select_ret;
		char *choice;
		int opt;
		struct play p;
		char lplay[1],*ltr;
		int xcoord=1,ycoord=1;

            /* create socket for receiving */
    sock_recv=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_recv < 0){
        printf("socket() failed\n");
        exit(0);
    }
        /* make local address structure */
    memset(&my_addr, 0, sizeof (my_addr));	/* zero out structure */
    my_addr.sin_family = AF_INET;	/* address family */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /* current machine IP */
    my_addr.sin_port = htons((unsigned short)LISTEN_PORT);
        /* bind socket to the local address */
    i=bind(sock_recv, (struct sockaddr *) &my_addr, sizeof (my_addr));
    if (i < 0){
        printf("bind() failed\n");
        exit(0);
    }
       FD_ZERO(&readfds);		/* zero out socket set */
       FD_SET(sock_recv,&readfds);	/* add socket to listen to */
        /* listen ... */
    while (1){
        read_fd_set = active_fd_set;
        select_ret=select(sock_recv+1,&readfds,NULL,NULL,NULL);
        /*select_ret=select(sock_recv+1,&readfds,NULL,NULL,&timeout);*/
        if (select_ret > 0){		/* anything arrive on any socket? */
        /*puts("I received something");*/
        incoming_len=sizeof(remote_addr);	/* who sent to us? */
        recv_msg_size=recvfrom(sock_recv,buf,BUF_SIZE,0,(struct sockaddr *)&remote_addr,&incoming_len);
       /*puts("After receiving...");*/
        if (recv_msg_size > 0){	/* what was sent? */
            buf[recv_msg_size]='\0';
          /*puts("After receiving2...");*/
            printf("From %s received: %s\n",inet_ntoa(remote_addr.sin_addr),buf);
            /*printf("From  received:%s \n",buf);*/
             /*puts("After receiving3...");*/
						 for(int g=0;g<3;g++)
						 {
							 if (g==0)
							 {
								 choice[0]=buf[g];
								 choice[1]='\0';//delimiter
								 xcoord=atoi(&choice[0]);

							 }
							 else if (g==1)
							 {
								 choice[1]=buf[g];
								 ycoord=atoi(&choice[1]);


							 }
							 else if(g==2)
							 {
								 buf[3]='\0'; //delimiter
								 choice[2]=buf[g];
								 lplay[0]=choice[2];
								 lplay[1]='\0';
							//	 *ltr=lplay[0];
								 makePlay(xcoord,ycoord,"l");
							 }

						 }
						 //getNewBoard();
						 drawBoard();
					 }
        if (strcmp(buf,"quit") == 0)
            break;

    }

	}
} // close server function

//getPlayerMove Function
// void getPlayerMove()
// {
// 	char *choice;
// 	int opt;
// 	struct play p;
// 	char buf[BUF_SIZE];
//
// 	printf("Play [1] or Quit [2] \n");
// 	// server();
// 	// scanf("%d",&opt);
//
// 	// if (opt==1)
// 	// {
// 	//   printf("proceeding with Play\n");
// 	// 	// implement function to further play
// 	// 	for(int g=0;g<3;g++)
// 	// 	{
// 	// 		if(g==0)
// 	// 		{
// 	// 			printf("one");
// 	// 			choice[0]=buf[g];
// 	// 			choice[1]='\0';
// 	// 			p.x=atoi(&choice[0]);
// 	// 			printf("%c\n",p.x);
// 	// 		}
// 	//
// 	// 		else if(g==1)
// 	// 		{
// 	// 			printf("2");
// 	// 			choice[1]=buf[g];
// 	// 			p.y=atoi(&choice[1]);
// 	// 			printf("%c\n",p.y);
// 	// 		}
// 	//
// 	// 		else if(g==2)
// 	// 		{
// 	// 			printf("3");
// 	// 			p.c=&buf[g];
// 	// 			printf("%c",*p.c);
// 	// 			buf[3]='\0';
// 	// 		}
// 	// 		printf("done making play\n");
// 	// 		//makePlay(p.x,p.y,p.c);// two integers  'xy' that specifies play
// 	// 		getNewBoard();
// 	// 		drawBoard();
// 	// 		break;
//   //   }//close for loop
//   // }//close if
//   // else if (opt==2)
//   // {
//   //   printf("exiting the game, goodbye\n");
//   //   exit(0);
//   // }
//
//   return;
// 				// this involves getting the coordinates of the play using a function sir implemented
// }
//calculateScore Function
//isOnBoard Function
int isOnBoard(int x,int y)
{
	int t=1,f=0;
	if(x > 0 && x < NUM_RANGE && y > 0 && y < NUM_RANGE)
	{
		return t;
	}
	else
	{
		return f;
	}

}
//StartBoard Function


// GAMEPLAY STARTS HERE IN MAIN
//while(1)
//{
	getNewBoard();
	//Displaying empty board
	printf("\n%s\n\n","Printing an empty board....");
	drawBoard();
	//making two plays
	makePlay(3,7,"a");
	makePlay(4,5,"b");
	//getPlayerMove();
	printf("\n%s\n\n","RePrinting board after plays....");
	//redrawing the board with plays shown
	drawBoard();

	server();
	//getPlayerMove();
//}

    return 0;
}
