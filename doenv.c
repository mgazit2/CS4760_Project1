// Matan Gazit
// CS4760
// Project 1
//
// Purpose:
// 	mimic env(1) behavior
// 
// Usage
// 	./doenv [-h]
//      ./doenv [-i] [var1=value] [var2=value] [...] {command 1 [; command2] [; ...]}\n");

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

static void print_usage();
static void update_env(char **args, int argc);
static void  show_all();
static void allocate_env(char **args, int argc);

static char* _program_name;
static char* _error_str[100];

int main(int argc, char *argv[]){
	setvbuf(stdout, NULL, _IONBF, 0);		
	_program_name = argv[0];
	snprintf(_error_str, sizeof _error_str, "%s: Error: ", _program_name);

	int i = 0;
	bool check = true;

	if (argc == 1) {
		show_all();
		//perror(_error_str);
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
				perror(_error_str);
				exit(1);
				break;
		}
	}
	
	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '=') != NULL || strchr(argv[i], '-') != NULL)
			continue;
		system(argv[i]);
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
	char **p;
	if (optind < argc) {
		for (p = args; *p != NULL; p++){
			if (strchr(*p, '=') == NULL)
				continue;
			putenv(*p);
		}
	}
	//printf("Modified Environment\n");
	show_all();
}

void show_all() {
	char **p;
	extern char **environ;
	for (p  = environ; *p != NULL; p++)
		printf("%s\n", *p);
	//printf("FINISHED WITH SHOW_ALL\n\n");
}

void allocate_env(char **args, int argc) {
	int size = 0;
	int i = 0;
	char **p;
	extern char **environ;
	for (p = environ; *p != NULL; p++)
		size++;
	size += argc - optind + 1;
	char **newptr = (char**)malloc(2*size);
	if (newptr == NULL) {
		perror(_error_str);
		exit(1);
	}
	for (i = 2; i < argc; i++) {
		if (strchr(args[i], '=') == NULL)
			continue;
		newptr[i-2] = args[i];
	}	
	/* */
	environ = newptr;
	show_all();
	free(newptr);
}
