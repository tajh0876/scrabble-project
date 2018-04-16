#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 60000
#define BUF_SIZE	5


int main() {
    int k,j;
    
    int num1, num2;
    char  letter;
    
    int const NUM_RANGE=8;
    //global declaration structure grid
    char * grid[NUM_RANGE][NUM_RANGE];
    
    
    //creates a brand new blank board. Returns a pointer to the array
    void getNewBoard(){
        for (j = 0; j < NUM_RANGE; j++){
            for (k = 0; k < NUM_RANGE; k++)
            {
                grid[k][j]="   ";
            }//Endfor
        }//Endfor
        return;
    }//EndFunction getNewBoard
    
    
    //This function prints out the board that was passed. Returns void
    void drawBoard(){
        char * const NLINE = "    1    2    3    4    5    6    7    8";
        char * const HLINE = "  +----+----+----+----+----+----+----+----+";
        char * const VLINE = "  |    |    |    |    |    |    |    |    |";

        printf("%s\n",NLINE);
        printf("%s\n",HLINE);
        for (j = 0; j < NUM_RANGE; j++){  
            printf("%s\n",VLINE);
            printf("%d ",j+1);
            for (k = 0; k < NUM_RANGE; k++){  
                if(strcmp(grid[k][j],"   ")==0){
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
    
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char * message = "Enter coordinates and letter to play or 'quit' to leave\n";
    
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        getNewBoard();
        //Displaying empty board
        printf("\n%s\n\n","Printing an empty board....");
        drawBoard();
        
        printf("\n%s\n\n","RePrinting board after plays....");
        
        //sends message to client
        send(new_socket , message , strlen(message) , 0 );
        
        //reads message from client
        valread = read( new_socket , buffer, 1024);
        
        int num1 = atoi(&buffer[0]);
        int num2 = atoi(&buffer[1]);
        letter = buffer[2];
        
        makePlay(num2, num2, &letter);
        
         //redrawing the board with plays shown
        drawBoard();
        printf("%c, %c, %c\n", buffer[0], buffer[1], buffer[2]);
        
       
       
    }
    
    close(new_socket);
}

 