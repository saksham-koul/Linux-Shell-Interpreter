#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#define sz 200

int main(int argc, char **argv)
{
	char *flag = argv[1], *args = argv[2];
	
	if (strlen(flag) != 0){
		printf("\nError: No flags for this command!\n");
		return 0;
	}
	
	if (strlen(args) == 0){										//cat
		char *line = (char*)malloc(sz * sizeof(char));
		
		while(1){
			fgets(line, sz, stdin);
			if (strcmp(line, "end\n") == 0)
				break;
			
			printf("%s", line);
		}
	}
	
	else{
		int args_ptr = strlen(args) - 1;
		
		while (args[args_ptr] == ' ' || args[args_ptr] == '\n'){					//removing trailing spaces
			args_ptr--;
		}
		
		args[args_ptr + 1] = '\0';
		
		int file_ptr = 0, n1 = 0;
		
		char **files = (char**)malloc(sz * sizeof(char*));
		
		char *f = strtok(args, ">");
		
		while (f != NULL){
			files[file_ptr] = f;
			file_ptr++;
			n1++;
			
			f = strtok(NULL, ">");
		}
		
		for (int i = 0; i < n1; i++){
			char *ptr = strtok(files[i], " ");
			while (ptr != NULL){
				files[i] = ptr;
				ptr = strtok(NULL, " ");
			}
		}
		
		if ((n1 == 0) || (n1 == 1 && args[strlen(args) - 2] == '>')){			//cat > or cat file >
			printf("Error: Invalid command!\n");
			return 0;
		}
		
		if (n1 == 1){
			
			if (args[0] == '>'){												//cat > file
				FILE *fp = fopen(files[0], "w");
				
				if (fp == NULL){
					printf("\nError: Couldn't create file!\n");
					return 0;
				}
				
				char *line = (char*)malloc(sz * sizeof(char));
				while (1){
					fgets(line, sz, stdin);
					if (strcmp(line, "end\n") == 0)
						break;
					fprintf(fp, "%s", line);
				}
				fclose(fp);	
			}
			
			else{																//cat file 
				FILE *fp = fopen(files[0], "r");
				
				if (fp == NULL){
					printf("\nError: Couldn't open file!\n");
					return 0;
				}
				
				char *line = (char*)malloc(sz * sizeof(char));
				while (fgets(line, sz, fp) != NULL){
					printf("%s", line);
				}
				fclose(fp);
			}
		}
		
		else{																	//2 files - cat file1 > file2
			FILE *f1 = fopen(files[0], "r");
			FILE *f2 = fopen(files[1], "w");
			
			if (f1 == NULL || f2 == NULL){
				printf("\nFile error!\n");
				return 0;
			}
			
			char *line = (char*)malloc(sz * sizeof(char));
			
			while (fgets(line, sz, f1) != NULL){
				fprintf(f2, "%s", line);
			}
			fclose(f1);
			fclose(f2);
		}
		
	}
	
	return 0;
}
