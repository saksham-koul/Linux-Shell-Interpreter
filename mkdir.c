#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#define sz 100

extern int errno;

int main(int argc, char *argv[])
{
	errno = 0;
	char *flag = argv[1], *args = argv[2];
	
	if(strlen(args) == 0){
		printf("%s", "Error: File name not given!");
		return 0;
	}
	
	char **files = (char**)malloc(sz * sizeof(char*));
	int f = 0;
	
	char *temp = strtok(args, " ");
	while (temp != NULL){
		files[f] = temp;
		f++;
		temp = strtok(NULL," "); 
	}
	
	if(strlen(flag) == 0){
		for (int i = 0; i < f; i++){
			char *args = files[i];
			int check = mkdir(args, 0);
		
			if(check == -1){
				perror("Error");
			}
			else
				chmod(args, 0777);
		}
	}
	
	else if(strlen(flag) == 1){
		if(flag[0] == 'v'){
			for (int i = 0; i < f; i++){
				char *args = files[i];											//mkdir -v dir_name
				int check = mkdir(args, 0);
			
				if(check == -1){
					perror("Error");
				}
			
				else{
					chmod(args, 0777);
					printf("Created directory \"%s\"\n", args);
				}
			}
		}
		
		else if(flag[0] == 'm'){											//mkdir -m dir_name
			if (f > 2){
					printf("Error: Only one file for this flag!");
					return 0;
			}
					
			char *args = (char*)malloc(sz * sizeof(char));
			args = files[0];

			int ptr = 0, ptr_mode;
			
			char *mode = (char*)malloc(100 * sizeof(char));
			
			for(int i = 0; args[i] != '\0' && args[i] != ' '; i++){
				mode[i] = args[i];
				
				if(isdigit(mode[i]) == 0){								//not a numeric char
					printf("Invalid mode value!");
					return 0;
				}
				ptr++;
				mode[i + 1] = '\0';
			}
			
			int len = (int) strlen(mode);
			mode_t sum = 0;
			
			for(int i = 0; i < len; i++){
				int p = 1;
				for(int j = 0; j < len - i - 1; j++){
					p *= 8;
				}
				sum += p*(mode[i] - '0');
			}
			
			char *filename = (char*)malloc(100 * sizeof(char));
			filename = files[1];
			
			while(args[ptr] != '\0' && args[ptr] == ' ') 
				ptr++;
			
			int ptr2 = 0;
			
			for(int i = ptr; args[i] != '\0'; i++){
				filename[ptr2] = args[i];
				ptr2++;
			}
			
			sum = strtol(mode, NULL, 8);
			
			int check = mkdir(filename, 0);
			
			if(check == -1){
				perror("Error");
			}
			else
				chmod(filename, sum);
		}
		
		else
			printf("%s", "Error: Invalid flag!");
	}
	
	else
		printf("%s", "Error: Invalid flag!");
	
	return 0;
}
