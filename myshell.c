#include <stdio.h> 		//for all I-O ops (including stderr, perror)
#include <unistd.h>		//chdir(), fork(), exec(), pid_t
#include <sys/wait.h>	//waitpid() and other associated macros
#include <stdlib.h> 	//malloc(+ related) free() exit() execvp(check coz exec in unistd.h) EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> 	//strcmp, strtok
#include <sys/types.h> 	//for pid_t and fork()
#include <ctype.h>		//for tolower()
#include <stdbool.h>	//to use bool variable
#include <limits.h>		//for PATH_MAX etc.

#define sz 100

int num_cmds = 0;

char** extract_cmds(char *input)
{
	num_cmds = 0;
	
	if (strcmp(input,"") == 0)
		return NULL;
	
	int ptr = 0;
	
	while(input[ptr] != '\0' && input[ptr] == ' ') 				//ignore leading spaces
		ptr++; 
	
	char **commands = (char**)malloc(sz * sizeof(char*));		//to store all cmds separated by '+'
	
	char *token = strtok(input, "+");
	
	while (token != NULL){
		commands[num_cmds] = token;
		num_cmds++;
		
		token = strtok(NULL, "+");
	}
	
	return commands;
}

void ext_cmds(char *cmd, char *flag, char *args)
{
	//handle all external cmds here by creating child processes
	int process;
	
	if ((process = fork()) == 0){
		
		if (strcmp(cmd, "makedir") == 0){					//mkdir
			execl("mkdir", cmd, flag, args, NULL);
		}
		
		else if (strcmp(cmd, "remove") == 0){				//rm
			execl("rm", cmd, flag, args, NULL);
		}
		
		else if (strcmp(cmd, "kat") == 0){					//cat
			execl("cat", cmd, flag, args, NULL);
		}
		
		else if (strcmp(cmd, "list") == 0){					//ls
			execl("ls", cmd, flag, args, NULL);
		}
		
		else if (strcmp(cmd, "datetime") == 0){				//date
			execl("date", cmd, flag, args, NULL);
		}
		
		else if (strlen(cmd) == 0){
			return;
		}
		
		else {
			printf("Invalid command!\nType 'hellp' to see the list of valid commands\n");
		}
		exit(0);
	}
	
	else if (process < 0){
		//error forking
		perror("Error");
	}
	
	else{
		//parent process
		int x;
		waitpid(process, &x, 0);
	}
}

int execute(char *cmd, char *flag, char *args)				//all builtins here
{	
//-------------exit command-------------//
	if (strcmp(cmd, "quit") == 0){
		
		if (strlen(flag) || strlen(args)){
			printf("Error: Invalid command entered!");
			return 1;
		}
		return 0;
	}

//-------------cd command--------------//

	else if (strcmp(cmd, "chd") == 0){
		
		if (strlen(flag) != 0){
			printf("Error: No flags for this command!\n\n");
			return 1;
		}
		
		if (strlen(args) == 0)							//cd => go to HOME
			chdir(getenv("HOME"));
		
		else{											//cd path_name
			int res = chdir(args);
			
			if (res == -1)
				perror("Error");
		}
	}
	
//------------echo command--------------//		

	else if (strcmp(cmd, "ecko") == 0){
		
		if (args[0] != '"'){
			printf("Error: Enclose string in quotes!\n\n");
			return 1;
		}
		
		if (args[strlen(args) - 1] != '"'){
			printf("Error: Expected end quotes!\n\n");
			return 1;
		}
		
		int len = 0;
		for(int i = 0; args[i] != '\0'; i++){
			len++;
		}
			
		len--;
			
		while(len >= 0 && args[len] == ' '){								//removing trailing spaces
			args[len] = '\0';
			len--;
		}
		
		if(strlen(flag) == 0){												//echo "..."
			for(int i = 0; args[i] != '\0'; i++){
				if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) 
					continue;
				printf("%c", args[i]);
			}
				
			printf("\n");
		}
			
		else if (strlen(flag) == 1){
			if (flag[0] == 'n'){											//echo -n "..."
				for(int i = 0; args[i] != '\0'; i++){
					if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) 
						continue;
					printf("%c", args[i]);
				}
			}
			
			else if (flag[0] == 'e'){										//echo -e "..."
				char *line = (char*)malloc(sz * sizeof(char));
				int ptr = 0;
			
				for(int i = 0; args[i] != '\0'; i++){
					if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) 
						continue;
					if(args[i] == '\\' && args[i + 1] == 'n'){				//"...\n..."
						line[ptr] = '\n';
						i++;
					}
					else if (args[i] == '\\' && args[i + 1] == 't'){		//"...\t..."
						line[ptr] = '\t';
						i++;
					}
					else 
						line[ptr] = args[i];
					ptr++;
				}
				printf("%s\n", line);
			}
			
			else{
				printf("Error: Invalid flag!\n\n");
				return 1;
			}
		}
		
		else{
			printf("Error: Invalid flag!\n\n");
			return 1;
		}
		
	}

//------------help command---------------//
	
	else if (strcmp(cmd, "hellp") == 0){
		FILE *help = fopen("help.txt", "r");
		
		if (help == NULL){
			perror("Error");
			printf("\n");
			return 1;
		}
		
		char *data = (char*)malloc(sz * sizeof(char));
	
		while (fgets(data, sz, help) != NULL){
			printf("%s", data);
		}
		fclose(help);
	}
		
//------------history command-------------//
	
	else if (strcmp(cmd, "hisstory") == 0){			//2 flags - history -clear & history -write
		if (strlen(flag) == 0){
			if (strlen(args) != 0){
				printf("Error: Invalid command!\n");
				return 1;
			}
			
			FILE *history = fopen("history.txt", "r");
		
			if(history == NULL){
				perror("Error");
				return 1;
			}
			
			char *line = (char*)malloc(sz * sizeof(char));
			while(fgets(line, sz, history) != NULL){
				printf("%s", line);
			}
			
			fclose(history);
		}
		
		else{
			if (strcmp(flag, "clear") == 0){					//history -clear
				if (strlen(args) != 0){
					printf("Error: No arguments expected for this command!\n");
					return 1;
				}
				
				FILE *history = fopen("history.txt", "w");
				
				if(history == NULL){
					perror("Error");
					printf("\n");
					return 1;
				}
				
				fprintf(history, "%c", ' ');
				fclose(history);
			}
			
			else if (strcmp(flag, "write") == 0){				//history -write
				FILE *history = fopen("history.txt", "a+");
				
				fprintf(history, "%s\n", args);
				fclose(history);
			}
			
			else
				printf("Error: Invalid command!\n");
		}
	}

//-------------pwd command---------------//

	else if (strcmp(cmd, "cwd") == 0){
		if (strlen(flag) != 0 || strlen(args) != 0){
			printf("Error: Invalid command!\n");
			return 1;
		}
		
		char *dir = (char*)malloc(PATH_MAX * sizeof(char));
		
		if (getcwd(dir, PATH_MAX) == NULL){
			perror("Error");
			printf("\n");
			return 1;
		}
		printf("%s\n", dir);
	}
	
	else
		ext_cmds(cmd, flag, args);
	
	return 1;
}

void shell()							//contains implementation of all builtins
{	
	int status;
	
	do {
		char *curr_dir = (char*)malloc(PATH_MAX * sizeof(char));
		getcwd(curr_dir, PATH_MAX);
		
		printf("\033[0;33m");
		printf("%s", curr_dir);
		printf("\033[0m");
		printf("$ ");
		
		char *input = (char*)malloc(sz * sizeof(char));
		fgets(input, sz, stdin);
		
		char *cmd, *flag, *args;
		
		char **commands = (char**)malloc(sz * sizeof(char*));
		commands = extract_cmds(input);
		
		
		char *dir = (char*)malloc(PATH_MAX * sizeof(char));
		getcwd(dir, PATH_MAX);
		
		FILE *history = fopen("history.txt", "a+");
		
		if(history == NULL) {
			printf("%s\n", "Error: Couldn't load history.\n");
		}
		
		else {
			fprintf(history, "%s", input);
			fclose(history);
		}
		
		for (int i = 0; i < num_cmds; i++){
			cmd = (char*)malloc(sz * sizeof(char));
			flag = (char*)malloc(sz * sizeof(char));
			args = (char*)malloc(sz * sizeof(char));
		
			int token_ptr = 0, cmd_ptr = 0, flag_ptr = 0, args_ptr = 0;
			
			char* token = commands[i];
			
			while(token[token_ptr] != '\0' && token[token_ptr] == ' '){		//ignoring leading spaces in the token
				token_ptr++;
			}
			
			
			while (token[token_ptr] != '\0' && token[token_ptr] != ' '){
				cmd[cmd_ptr] = token[token_ptr];
				cmd_ptr++;
				token_ptr++;
			}
			
			cmd[cmd_ptr] = '\0';
			
			if (cmd_ptr > 0){
				if (cmd[cmd_ptr - 1] == '\n')
					cmd[cmd_ptr - 1] = '\0';
			}
			
			for (int i = 0; cmd[i] != '\0'; i++)
				cmd[i] = tolower(cmd[i]);
			
			while (token[token_ptr] != '\0' && token[token_ptr] == ' ')		//ignoring spaces bw cmd and flag
				token_ptr++;
				
			if (token[token_ptr] == '-'){									//flag found
				token_ptr++;
				
				while (token[token_ptr] != '\0' && token[token_ptr] != ' '){
					flag[flag_ptr] = token[token_ptr];
					flag_ptr++;
					token_ptr++;
				}
			}
			
			while(token[token_ptr] != '\0' && token[token_ptr] == ' ') //ignoring spaces b/w flag and args
				token_ptr++;
				
			while(token[token_ptr] != '\0'){					//retrieving args
				args[args_ptr] = token[token_ptr];
				token_ptr++;
				args_ptr++;
			}
			
			if(args_ptr > 0){
				if(args[args_ptr - 1] == '\n'){
					args[args_ptr - 1] = '\0';
				}
			}
	
			if(flag_ptr > 0){
				if(flag[flag_ptr - 1] == '\n'){
					flag[flag_ptr - 1] = '\0';
				}
			}
			
			for (int i = 0; flag[i] != '\0'; i++)
				flag[i] = tolower(flag[i]);
			
			
			status = execute(cmd, flag, args);
			
			if (status == 0)
				break;
		} 
		
	} while (status);
}

int main(int argc, char *argv[])
{
	printf("\n-------------------------------------\n");
	printf("Welcome to my Linux Shell Interpreter\n");
	printf("-------------------------------------\n\n");
	
	printf("-> Type commands and arguments, and hit enter.\n");
	printf("-> Type 'hellp' command to see the list of all commands that can be executed here.\n\n");

	
	shell();
	
	
	return 0;
}
