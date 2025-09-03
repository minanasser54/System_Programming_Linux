#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_SIZE 16384
int main(int argc, char** argv)
{
	if(argc > 1)
	{
		printf("Femto Shell doesn't have arguments, please run it again without arguments\n");
		exit(-1);
	}

	char command[5] = "", input[IN_SIZE];
	printf("FemtoSha > ");
	while(fgets(input, IN_SIZE, stdin))
	{
		if(strlen(input) == 1 && input[0] == '\n')
		{
			printf("Please enter something, anything, please.\n");
			command[0] = '\0'; input[0] = '\0';
	                printf("FemtoSha > ");
			continue;
		}
		int i;
		for(i = 0; i < 4 && input[i] != '\0'; i++)
			command[i] = input[i];
		command[i] = '\0';
		//printf("%s\n", command);
		if(strcmp(command, "echo") == 0)
		{
			i++;
			char *output = &input[i];
			printf("%s", output);	
		}
		else if(strcmp(command, "exit") == 0)
		{
			printf("See u later (>ᴗ<)づ\n");
			break;
		}
		else
			printf("Invalid command\n");
		command[0] = '\0'; input[0] = '\0';
                printf("FemtoSha > ");

	}
	
	return 0;

}
