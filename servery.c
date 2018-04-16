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


    struct play{
    	int x,y;
    	char *c;
    	};

//variables
    int k,j;
    int const NUM_RANGE=8;
    int g;
    
    int num1, num2;
    char* letter;
    
    //global declaration structure grid
    char* grid[NUM_RANGE][NUM_RANGE];




//This function creates a brand new blank board. Returns a pointer to the array
    void getNewBoard(){
        for (j = 0; j < NUM_RANGE; j++){
            for (k = 0; k < NUM_RANGE; k++)
            {
                grid[k][j]="   ";
            }
        }
        return;
    }




//This function prints out the board that was passed. Returns void
    void drawBoard(){
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
    }





//This function takes a coordinate and displays the player's letter on the board
    void makePlay(int x, int y, char* c){
       //Arrays are zero indexed but our grid starts at index 1
       grid[x-1][y-1]=c;
       return;
    }
    
    
    
    
    //getPlayerMove Function
    int getPlayerMove()
    {
    	char *choice,opt[1];
    	int x,y,a,r,s; // coordinates
    	struct play p;
    	char buf[BUF_SIZE];
        
           
        	printf("Play [p] or Quit [q]\n");
        	scanf("%s",opt);
            
            
            if (strcmp(opt,"q")==0){
                printf("exiting the game, goodbye\n");
                return 0;
                exit(0);
            }    
        	
        	else if (strcmp(opt,"p")==0){
        	  printf("proceeding with Play\n");
        		
        		// implement function to further play
        		for( g=0;g<3;g++){
        			if(g==0){
        				choice[0]=buf[g];
        				//strcpy(holdx,p.x);
        				//xcoord[1]='\0':
        				choice[1]='\0';
        				p.x=atoi(&choice[0]);
        				//p.x=atoi(&buf[g]); format before change above
        				//xcoord=p.x;
        				printf("%c\n",p.x);
        			}
        			else if(g==1){
        				choice[1]=buf[g];
        				//strcpy(holdx,p.y);
        				//ycoord[1]='\0';
        				p.y=atoi(&choice[1]);
        				printf("%c\n",p.y);
        			}
        			else if(g==2){
        				p.c=&buf[g];
        				printf("%c",*p.c);
        				buf[3]='\0';
        			//p.c=atol(&buf[2]);
        			}
        			makePlay(p.x,p.y,p.c);// two integers  'xy' that specifies play
        			drawBoard();
        			return 0;
        			exit(0);
        		}
            }
            
        }
    




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
    //server function
    void server()
    {
        int			sock_recv;
        struct sockaddr_in	my_addr;
        int			i;
        fd_set	readfds,active_fd_set,read_fd_set;
        struct timeval		timeout={0,0};
        int			incoming_len;
        struct sockaddr_in	remote_addr;
        int			recv_msg_size;
        char			buf[BUF_SIZE];
        int			select_ret;
    
    
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
                    getPlayerMove();
                 }
                }
    
            if (strcmp(buf,"quit") == 0)
                break;
    
        }
    
        close(sock_recv);
    }
    




    
    // GAMEPLAY STARTS HERE IN MAIN
   
    //Displaying empty board
    getNewBoard();
        
    printf("\n%s\n\n","Printing an empty board....");
    drawBoard();
    
         
    /* scanf("%d, %d, %c", &num1, &num2, letter);
    makePlay(num1, num2, letter);
      
    //making two plays
    makePlay(3,7,"a");
    makePlay(4,5,"b");*/
         
        
    getPlayerMove()
    /*printf("\n%s\n\n","RePrinting board after plays....");
    //redrawing the board with plays shown
    drawBoard();*/
        
        
    server();
    //  getPlayerMove();
    }
    return 0;
}
