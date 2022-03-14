#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>     /* close() */
#include <string.h>

//getting file size
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "connectionHandling.h"
#include "../io_helper/io_helper.h"


//handles http requests for html and images
void *handleConnection(void *arg)
{
    int sd = *((int *)arg);
    char request_buff[HEADER_BUFF_SIZE];    

    //recive http request
    if (recv(sd, request_buff, sizeof(request_buff), 0) == -1)
    {
        close(sd);
        exit(EXIT_FAILURE);
    }

    //check method type
    enum methodType method = get_request_method(request_buff);

    #pragma region debug
    printf("METHOD : %d \n", method);
    #pragma endregion

    if (method != -1 )
    {
        char httpResponse[8192] = "";
        enum requestType request_type;

        if(method == GET )
        {
            switch (request_type)
            {
                    case TEXT_HTML:
                {
                    char httpResponse_temp[8192] = "";
                    char httpHeader_template[] =
                        "HTTP/1.1 200 OK\n"
                        "Content-Length: %d\n"
                        "Content-Type: text/html; charset=iso-8859-1\n"
                        "\r\n";
                    char httpBody_temp[8192 - 512] = "";

                    readFile(INDEX_HTML, httpBody_temp);

                    strcat(httpResponse_temp, httpHeader_template);
                    strcat(httpResponse_temp, httpBody_temp);
                    sprintf(httpResponse, httpResponse_temp, (int)strlen(httpBody_temp));
                    break;
                }

                case IMG_JPG:
                {
                    printf("XXXXXXXXXXXXXXXXXXXXXXXX");
                    char httpResponse_temp[8192] = "";
                    char httpHeader_template[] =
                        "HTTP/1.1 200 OK\n"
                        "Content-Length: %d\n"
                        "Content-Type: img/jpg; charset=iso-8859-1\n"
                        "\r\n";
                    char httpBody_temp[8192 - 512] = "";



                    return NULL;
                }

                default:
                {
                    char httpResponse_temp[8192] = "";
                    char httpHeader_template[] =
                        "HTTP/1.1 404 REQUEST FILE TYPE NOT IMPLEMENTED\n"
                        "Content-Type: text/html; charset=iso-8859-1\n"
                        "\r\n";
                    char httpBody_temp[8192 - 512] = "";

                    strcat(httpResponse_temp, httpHeader_template);
                    strcat(httpResponse_temp, httpBody_temp);
                    sprintf(httpResponse, httpResponse_temp, (int)strlen(httpBody_temp));
                    break;
                }
            }
            
        }
        else if(method == POST)
        {

        }   


        #pragma region debug
        printf("----------------------------\nresponse : \n%s\n------------------------------\n",httpResponse);
        #pragma endregion

        send(sd, httpResponse, strlen(httpResponse), 0);
    }

    return 0;
}

int get_request_method(char request_header[])
{   

    if(strstr(request_header,"GET") != NULL)
    {
        return GET;
    }

    if(strstr(request_header,"POST") != NULL)
    {
        return POST;
    }

    return INVALID_METHOD_TYPE;
}

int get_request_type(char request_header[])
{
    if(strstr(request_header,"text/html") != NULL)
    {
        return TEXT_HTML;
    }
    else if(strstr(request_header,"img/") != NULL)
    {
        return IMG_JPG;
    }

    return INVALID_REQUEST_TYPE;
}

void get_request_file_name(char request[],char file_type[], char result[])
{

}
