#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

static void print_usage();
static void update_env(char **args, int argc);
static void  show_all();
static void allocate_env(char **args, int argc);

static char* program_name;

int main(int argc, char *argv[]){
	setvbuf(stdout, NULL, _IONBF, 0);	

	program_name = argv[0];
	int i = 0;
	char *args;
	bool check = true;

	if (argc == 1) {
		//printf("%s\n", getenv("env"));
		show_all();
		printf("No arguments given\n");
		return EXIT_SUCCESS;
	}	
	
	while (check) {
		int d = getopt(argc, argv, "hi:");
		if (d == -1) {
			update_env(argv, argc);
			break;
		}
		switch (d) {
			case 'h':
				print_usage();
				return EXIT_SUCCESS;
				break;
			case 'i':
				allocate_env(argv, argc);
				check = false;
				break;
			default:
				printf("ERROR\n");
				break;
		}
	}
	
	for (i = 1; i < argc; i++) {
		if (system(argv[i]) == -1) {
			continue;
		}
	}		
	/*
	*/
	return EXIT_SUCCESS;	
}

void print_usage() {
	printf("Usage\n");
	printf("doenv [-h]\n");
	printf("doenv [-i] [var1=value] [var2=value] [...] {command 1 [; command2] [; ...]}\n");
}

void update_env(char **args, int argc) {
	printf("In update_env\n");
	char **p;
	if (optind < argc) {
		for (p = args; *p != NULL; p++){
			if (strchr(*p, '=') == NULL)
				continue;
			putenv(*p);
		}
	}
	printf("Modified Environment\n");
	show_all();
}

void show_all() {
	char **p;
	//system("clear");
	extern char **environ;
	//printf("Environment Variables\n");
	for (p  = environ; *p != NULL; p++)
		printf("%s\n", *p);
	printf("FINISHED WITH SHOW_ALL\n\n");
}

void allocate_env(char **args, int argc) {
	char **a;
	int bal = 0;
	int i = 0;
	char **p;
	extern char **environ;
	for (p = environ; *p != NULL; p++)
		bal++;
	bal += argc - optind + 1;
	char **newptr = (char**)malloc(2*bal);
	//printf("%d is\n and %d is \n", optind, argc); DEBUG STATEMENT
	for (i = 2; i < argc; i++) {
		if (strchr(args[i], '=') == NULL)
			continue;
		newptr[i-2] = args[i];
		//printf("Current index of newptr is set to: %s\n", newptr[i-2]);
	}	
	/*for (a = newptr; *a != NULL; a++) {
		printf("IN A LOOP\n");
		printf("%s\n", *a);
	} MEANT TO DEBUG ALLOCATE_ENV() */
	environ = newptr;
	printf("FINISHED WITH ALLOCATE_ENV()\n");
	show_all();
}
