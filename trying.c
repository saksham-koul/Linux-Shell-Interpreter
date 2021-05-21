#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define sz 100
int num_cmds = 0;

int main()
{
	//pid_t x = fork();
	
	//if (x == 0)
		//printf("Child process\n");
	//else if (x < 0)
		//printf("Forking error\n");
	//else{
		//printf("Parent process, pid = %d\n", x);
	//}
	
	//cout << 1 << '\r' << 2 << '\n';
	//printf("1\t\r 2");
	
	//char chars[] = {'-', '\\', '|', '/'};
    //unsigned int i;

    //for (i = 0; ; ++i) {
		//printf("%c\r", chars[i % sizeof(chars)]);
        //fflush(stdout);
        //usleep(1000000);
	//}
	
	char *input = (char*)malloc(sz * sizeof(char));
	fgets(input, sz, stdin);
	
	char **commands = (char**)malloc(sz * sizeof(char*));
	char *cmd, *flag, *args;
	//cmd = (char*)malloc(sz * sizeof(char));
	//flag = (char*)malloc(sz * sizeof(char));
	//args = (char*)malloc(sz * sizeof(char));
	
	char *cmds = strtok(input, "+");
	while (cmds != NULL){
		commands[num_cmds] = cmds;
		num_cmds++;
		
		cmds = strtok(NULL, "+");
	}
	
	//for (int i = 0; i < num_cmds; i++){
		//char *token = commands[i];
		//printf("%s\n", token);
	//}
	
	for (int i = 0; i < num_cmds; i++){
		cmd = (char*)malloc(sz * sizeof(char));
		flag = (char*)malloc(sz * sizeof(char));
		args = (char*)malloc(sz * sizeof(char));
		
		int token_ptr = 0, cmd_ptr = 0, flag_ptr = 0, args_ptr = 0;
			
		//char* token = (char*)malloc(sz * sizeof(char));
		char *token = commands[i];
			
		while(token[token_ptr] == ' '){						//ignoring leading spaces in the token
			token_ptr++;
		}
			
		while (token[token_ptr] != '-' && token[token_ptr] != '\0' && token[token_ptr] != ' '){
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
			
		while (token[token_ptr] != '\0' && token[token_ptr] == ' ')		//ignoring spaces b/w cmd and flag
			token_ptr++;
				
		if (token[token_ptr] == '-'){							//flag found
			token_ptr++;
				
			while (token[token_ptr] != '\0' && token[token_ptr] != ' ' && token[token_ptr] != '\t'){
				flag[flag_ptr] = token[token_ptr];
				flag_ptr++;
				token_ptr++;
			}
		}
			
		while(token[token_ptr] != '\0' && (token[token_ptr] == ' ' || token[token_ptr] == '\t')) //ignoring spaces b/w flag and args
			token_ptr++;
			
		while(token[token_ptr] != '\0'){				//retrieving args
			//if (token[token_ptr] == '\t')
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
			
		//for (int i = 0; cmd[i] != '\0'; i++)
				//cmd[i] = tolower(cmd[i]);
			
		for (int i = 0; flag[i] != '\0'; i++)
			flag[i] = tolower(flag[i]);
			
		//for (int i = 0; args[i] != '\0'; i++)
			//args[i] = tolower(args[i]);
		//execute(cmd, flag, args);
		printf("cmd = %s\nflag = %s\nargs = %s\n", cmd, flag, args);
			
	}
	
	////char *path = (char*)malloc(sz * sizeof(char));
	//char *path = getenv("HOME");
	
	//printf("\n%s\n", path);
	
	//bool ok = true;
	//int quotes = 0;
		
	//for (int i = 0; args[i] != '\0'; i++){
		//if (args[i] == '"')
			//quotes++;
	//}
	//if (quotes % 2 != 0)
		//ok = false;
		
	//if (!ok){
		//printf("\nError: Couldn't find matching end quote!\n");
	//}
	//else{
		//for (int i = 0; args[i] != '\0'; i++){
			//if (args[i] != '"')
				//printf("%c", args[i]);
		//}
	//}
	
	//char *dir = (char*)malloc(PATH_MAX * sizeof(char));
		
	//if (getcwd(dir, PATH_MAX) == NULL){
		//printf("\nError\n");
		//return 0;
	//}
	//printf("%s\n", dir);
	
	//if (strlen(flag) != 0){
		//printf("\nError: No flags for this command!\n");
		//return 0;
	//}
	
	//if (strlen(args) == 0){
		//char *line = (char*)malloc(sz * sizeof(char));
		
		//while(1){
			//fgets(line, sz, stdin);
			//if (strcmp(line, "end\n") == 0)
				//break;
			//printf("%s", line);
		//}
	//}
		
	return 0;
}
