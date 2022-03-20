#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "requestParsing.h"
#include "HttpConsts.h"


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
    if(strstr(request_header,"Accept: text/html") != NULL)
    {
        return TEXT_HTML;
    }
    else if(strstr(request_header,"Accept: image") != NULL)
    {
        return IMG;
    }

    return INVALID_REQUEST_TYPE;
}

//extracts path of file in http request
int extract_file_path(char* request, char result[])
{
    char request_copy[HTTP_REQUEST_MAX_LEN];
    char* sub_string_pointer = (char*)malloc(128);
    char* sub_string_head = sub_string_pointer;

    strcpy(request_copy,request);

    memset(result,0,strlen(result));
    strcat(result,WEB_SERVER_PATH);


    sub_string_pointer = strtok(request_copy," ");
    sub_string_pointer = strtok(NULL," ");

    strcat(result,sub_string_pointer);
    free(sub_string_head);
}
