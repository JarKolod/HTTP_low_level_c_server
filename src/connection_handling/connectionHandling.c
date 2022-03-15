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

#include "HttpConsts.h"
#include "requestParsing.h"
#include "../io_helper/io_helper.h"


//handles http requests for html and images
void *handleConnection(void *arg)
{
    int sd = *((int *)arg);
    int retval;
    char request_buff[HEADER_BUFF_SIZE];    
    while(1)
    {
        memset(request_buff,0,sizeof(request_buff));

        //recive http request
        if ((retval = recv(sd, request_buff, sizeof(request_buff), 0)) == -1)
        {
            close(sd);
            exit(EXIT_FAILURE);
        }


        if(retval == 0)
        {
            close(sd);
            exit(EXIT_SUCCESS);
        }

        //check method type
        enum methodType method = get_request_method(request_buff);

        #pragma region debug
        printf("METHOD : %d \n", method);
        #pragma endregion

        if (method != -1 )
        {
            char httpResponse[8192] = "";
            printf("B------B request_buff: %s\n",request_buff);

            enum requestType request_type = get_request_type(request_buff);
            printf("T------T request_type: %d\n",request_type);

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

                        send(sd, httpResponse, strlen(httpResponse), 0);

                        break;
                    }

                    case IMG:
                    {
                        
                        char httpHeader_template[] =
                            "HTTP/1.1 200 OK\n"
                            "Content-Length: %zd\n"
                            "Content-Type: img/jpg\n"
                            "\r\n";

                        int fd;
                        char filename[] = "../src/web/imgs/sample_0.jpg";
                        char filebuff[32000];
                        FILE_STAT filestat;
                        FILE *fp;


#pragma region exporting_filename_from_request
                        char *request_copy = (char*)malloc(HTTP_REQUEST_MAX_LEN);
                        char *sub_string = (char*)malloc(HTTP_REQUEST_MAX_LEN);

                        strcpy(request_copy,request_buff);

                        sub_string = strtok(request_copy," ");
                        sub_string = strtok(NULL," ");


                        char path[] = WEB_SERVER_PATH;
                        strcat(path,sub_string);

                        printf("\nP------P PATH : %s\n",path);

                        free(request_copy);
#pragma endregion


                        //get file descriptor and file info
                        if ( ((fd = open (filename, O_RDONLY)) < -1) || (fstat(fd, &filestat) < 0) ) {
                            printf ("Error in measuring the size of the file");
                        }
                        // insert file size into httpResponse template
                        sprintf(httpResponse, httpHeader_template, filestat.st_size);

                        
                        readBinnaryFile(fp,&filestat,filename,filebuff);


                        send(sd, httpResponse, strlen(httpResponse), 0);
                        send(sd, filebuff, filestat.st_size, 0);

                        break;
                    }

                    default:
                    {
                        char httpResponse_temp[8192] = "";
                        char httpHeader_template[] =
                            "HTTP/1.1 415\n"
                            "Content-Type: text/html; charset=iso-8859-1\n"
                            "\r\n";
                        char httpBody_temp[8192 - 512] = "";

                        strcat(httpResponse_temp, httpHeader_template);
                        strcat(httpResponse_temp, httpBody_temp);
                        sprintf(httpResponse, httpResponse_temp, (int)strlen(httpBody_temp));

                        send(sd, httpResponse, strlen(httpResponse), 0);

                        break;
                    }
                }
                
            }
            else if(method == POST)
            {

            }   
            else
            {
                perror("method extraction error:\n");
                exit(EXIT_FAILURE);
            }


            #pragma region debug
            printf("----------------------------\nresponse : \n%s\n------------------------------\n",httpResponse);
            #pragma endregion

            
        }
    }

    return NULL;
}


