#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h> /* select() fd_set */
#include <netinet/in.h> /* struct sockaddr_in */
#include <arpa/inet.h>  /* inet_ntop() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <pthread.h>

#include "connection_handling/connectionHandling.h"
#include "io_helper/io_helper.h"



#define True 1
#define False 0


int main(int argc, char **argv)
{
    int main_sd; // server's main descriptor id
    struct sockaddr_in client_addr, server_addr; // struct contating address information

    socklen_t client_addr_len, server_addr_len; /* size of struct in bytes */

    if (argc != 2)
    {
        fprintf(stderr, "Invocation: %s <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* creating socket for TCP connection (SOCK_STREAM): */
    main_sd = socket(PF_INET, SOCK_STREAM, 0);
    if (main_sd == -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    
    server_addr.sin_family = AF_INET;/* communication domain (protocol family): */
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);/* adress not specified (wildcard address): */
    server_addr.sin_port = htons(atoi(argv[1]));    /* port: */
    server_addr_len = sizeof(server_addr); /* size of servers adress structure in bytes */

    // binding ip address and port number with socket
    if (bind(main_sd, (struct sockaddr *)&server_addr, server_addr_len) == -1)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    // start listing on the main socket
    if (listen(main_sd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connections ...");

    int new_sd = 0;
    char request_buff[REQUEST_BUFF_SIZE];
    while (True)
    {
        if ((new_sd = accept(main_sd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len)) < 0)
        {
            perror("accept() error");
            exit(EXIT_FAILURE);
        }

        printf("SOCKET --- connecting to new socket : %d\n", new_sd);

        //debug
        #pragma region debug
        printf("new Connection %d\n  ip: %s\n  port : %d\n\n", new_sd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        #pragma endregion debug

        // create new thread to handle connection ( http request )
        pthread_t th;
        if (pthread_create(&th, NULL, &handleConnection, (void*)&new_sd) != 0)
        {
            perror("pthread_create()\n");
            exit(EXIT_FAILURE);
        }

        pthread_detach(th);
    }

    close(main_sd);
    exit(EXIT_SUCCESS);
}
