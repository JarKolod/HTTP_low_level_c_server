typedef struct stat FILE_STAT;

void readFile(char path[], char result[]);
void writeToFile(char path[], char text[]);
void readBinnaryFile(FILE* fp, FILE_STAT* filestat , char filename[], char filebuff[]);
