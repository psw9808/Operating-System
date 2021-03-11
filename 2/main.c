#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instructions.h"
#define size 10

int main()
{
	char str[size] ;

	printf("-------------------SHELL-------------------\n");
	printf("ls, ls -al, pwd, exit\n");

	while (true)
	{
		printf("-> ");
		gets(str);

		if (!strcmp("ls -al",str))
			ls2();

		if (!strcmp("ls",str))
			ls();

        if (!strcmp("pwd", str))
			pwd();

		if (!strcmp("exit", str))
			break;
	}

	return 0;
}
