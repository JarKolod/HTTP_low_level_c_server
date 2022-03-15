#define WEB_SERVER_PATH "../src/web/"
#define HTTP_REQUEST_MAX_LEN 1024

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
	IMG
};
