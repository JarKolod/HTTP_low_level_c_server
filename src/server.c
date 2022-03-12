#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> /* socket(), listen() */
#include <string.h>

#include "connection_handling/connectionHandling.h"
#include "io_helper/io_helper.h"

#define MAX_CLIENTS 20       // maskymalna obslugiwana liczba klientow
#define HEADER_BUFF_SIZE 512 // maskymalna dlugosc buffora Header
#define BODY_BUFF_SIZE 8192  // maskymalna dlugosc buffora Body

int main(int argc, char **argv)
{
    int main_sd; // Deskryptor gniazda glownego.

    if (argc != 2)
    {
        fprintf(stderr, "Invocation: %s <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Utworzenie gniazda dla protokolu TCP: */
    main_sd = socket(PF_INET, SOCK_STREAM, 0);
    if (main_sd == -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    test();

    return 0;
}
