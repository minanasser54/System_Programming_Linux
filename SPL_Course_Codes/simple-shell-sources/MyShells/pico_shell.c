#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define IN_SIZE 16384
#define DIR_SIZE 8192

int main(int argc, char **argv)
{
	int exit_code = 0;
	if (argc > 1)
	{
		printf("Usage: Pico Shell doesn't have arguments, please run it again without arguments\n");
		exit(-1);
	}

	char input[IN_SIZE];
	while (1)
	{
		input[0] = 0;
		printf("PicoSha >> ");
		fflush(stdout);
		if (fgets(input, IN_SIZE, stdin) == NULL)
		{
			//printf("EOF or Failed to read the input\n");
			break;
		}
		input[strlen(input) - 1] = 0;
		if (strlen(input) == 0)
			continue;
		int new_argc = strlen(input);
		char **new_argv = (char **)malloc(sizeof(char *) * new_argc + 1);
		char *temp = strtok(input, " ");
		int i = 1, k = 0;
		while (temp != NULL)
		{
			new_argv[k] = (char *)malloc(strlen(temp) + 1);
			strcpy(new_argv[k], temp);
			k++;
			temp = strtok(NULL, " ");
		}
		new_argv[k] = NULL;
		new_argc = k;
		if (!strcmp(new_argv[0], "echo"))
		{
			for (; i < new_argc; i++)
			{
				printf("%s", new_argv[i]);
				if (i < new_argc - 1)
					printf(" ");
			}
			printf("\n");
		}
		else if (!strcmp(new_argv[0], "pwd"))
		{
			if (new_argc > 1)
				printf("Usage: 'pwd' command doesn't have arguments. Arguments are ignored.\n");
			char cwd[DIR_SIZE];
			if (getcwd(cwd, DIR_SIZE) == NULL)
			{
				printf("Error: Failed to get the pathname (pathname is too long)\n");
				exit_code = 1;
			}
			else
			{
				printf("%s\n", cwd);
				exit_code = 0;
			}
		}
		else if (!strcmp(new_argv[0], "cd"))
		{
			if (new_argc != 2)
				printf("Usage: cd [new_directory_path]\n");
			else if (chdir(new_argv[1]) < 0)
			{
				printf("cd: %s: No such file or directory\n", new_argv[1]);
				exit_code = 1;
			}
			else
				exit_code = 0;
		}
		else if (!strcmp(new_argv[0], "exit"))
		{
			if (new_argc > 1)
				printf("Usage: 'exit' command doesn't have arguments. Arguments are ignored.\n");
			printf("Good Bye\n");
			for (i = 0; i < new_argc; i++)
				free(new_argv[i]);
			free(new_argv);
			break;
		}
		else
		{
			pid_t child_pid = fork();
			if (child_pid > 0)	//This is parent
			{
				int status;
				wait(&status);
				if (WIFEXITED(status))
					exit_code = WEXITSTATUS(status);
				else
					exit_code = 1;
			}
			else if (child_pid == 0)	//This is child
			{
				execvp(new_argv[0], new_argv);
				printf("%s: command not found\n", new_argv[0]);
				exit(-2);
			}
			else
				printf("UNIX CMD: Failed to fork\n");
		}
		for (i = 0; i < new_argc; i++)
			free(new_argv[i]);
		free(new_argv);
	}
	return exit_code;
}
