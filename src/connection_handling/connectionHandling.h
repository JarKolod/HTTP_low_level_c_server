#define MAX_CLIENTS 20       // max number of clients
#define REQUEST_BUFF_SIZE 512 // max header buffor length
#define HEADER_BUFF_SIZE 512 // max header buffor length
#define BODY_BUFF_SIZE 8192  // max body buffor length

#define INDEX_HTML "..//src//web//src//index.html"


enum methodType
{
	INVALID_METHOD_TYPE = -1,
    GET,
    POST
};

enum requestType
{
	INVALID_REQUEST_TYPE = -1,
	TEXT_HTML,
	IMG_JPG
};

void *handleConnection(void *arg);
int get_request_method(char request[]);
int get_request_type(char request_header[]);
