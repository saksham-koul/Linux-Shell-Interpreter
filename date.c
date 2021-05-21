#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#define sz 100

int main(int argc, char **argv)
{
	char *flag = argv[1], *args = argv[2];
	
	if(strlen(args) != 0){
		printf("%s\n", "Error: Date command has no arguments!");
		return 0;
	}
	
	if(strlen(flag) == 0){
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		
		char *s = (char*)malloc(sz * sizeof(char));
		
		strftime(s, sz, "%A, %b %d, %Y, %T %Z", tm);
		printf("%s\n\n", s);
	}
	
	else if(strlen(flag) == 1){
		if(flag[0] == 'g'){
			time_t t = time(NULL);
			struct tm *tm = gmtime(&t);

			char *s = (char*)malloc(sz * sizeof(char));
			
			strftime(s, sz, "%A, %b %d, %Y, %T %Z", tm);
			printf("%s\n\n", s);
		}
		
		else if(flag[0] == 'u'){
			time_t t = time(NULL);
			struct tm *tm = gmtime(&t);

			char *s = (char*)malloc(sz * sizeof(char));
			
			strftime(s, sz, "%A, %b %d, %Y, %T", tm);
			printf("%s UTC\n", s);
		}
		
		else
			printf("Invalid flag!\n\n");
	}
	
	return 0;
}
