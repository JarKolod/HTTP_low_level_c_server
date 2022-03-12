#include <stdio.h>
#include <stdlib.h>

#include "io_helper.h"

void readFile(char path[], char result[])
{
	FILE *fp;
	char con[20];

	fp = fopen(path, "r");
	if (!fp)
	{
		perror("\n Unable to create or open file");
		exit(EXIT_FAILURE);
	}

	while (fgets(con, 20, fp) != NULL)
	{
		strcat(result, con);
	}

	fclose(fp);
}

void writeToFile(char path[], char text[])
{
	FILE *fileAddress;
	fileAddress = fopen(path, "w");

	if (fileAddress != NULL)
	{
		fputs(text, fileAddress);
		fclose(fileAddress);
	}
	else
	{
		perror("\n Unable to create or open file");
		exit(EXIT_FAILURE);
	}
}
