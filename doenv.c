// Matan Gazit
// CS4760
// Project 1
// 02/09/21
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

// Program driver
int main(int argc, char *argv[]){
	setvbuf(stdout, NULL, _IONBF, 0); // for debugging purposes	
	_program_name = argv[0]; // set program name to a dedicated var
	snprintf(_error_str, sizeof _error_str, "%s: Error: ", _program_name); // perror

	int i = 0; // iterator
	bool check = true; // while loop boolean var

	if (argc == 1) {
		show_all();
		//perror(_error_str);
		return EXIT_SUCCESS;
	} // end if no arguments, simulates getenv(3)	
	
	// getopt(3) loop based on Jared's (see README)
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
	} // end getopt(3) loop
	
	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '=') != NULL || strchr(argv[i], '-') != NULL)
			continue;
		system(argv[i]);
	} // loops through argv array and executes system commands found		
	/*
	*/
	return EXIT_SUCCESS;	
}

// prints possible program usage 
void print_usage() {
	printf("Usage\n");
	printf("doenv [-h]\n");
	printf("doenv [-i] [var1=value] [var2=value] [...] {command 1 [; command2] [; ...]}\n");
}

// updated environ w/ name=value pairings from cmd line
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

// simulates getenv(3) (see README for reference)
void show_all() {
	char **p;
	extern char **environ;
	for (p  = environ; *p != NULL; p++)
		printf("%s\n", *p);
	//printf("FINISHED WITH SHOW_ALL\n\n");
}

// allocates a newptr to environ to point too
// this newptr will be made up of name=value pairings from cmd line
void allocate_env(char **args, int argc) {
	int size = 0;
	int i = 0;
	char **p;
	extern char **environ;
	
	// code segments finds value for malloc to work with
	for (p = environ; *p != NULL; p++)
		size++;
	size += argc - optind + 1;

	// malloc code segment
	char **newptr = (char**)malloc(2*size);
	if (newptr == NULL) {
		perror(_error_str);
		exit(1);
	}
	
	// fill newptr w/ name=value pairings from cmd line
	for (i = 2; i < argc; i++) {
		if (strchr(args[i], '=') == NULL)
			continue;
		newptr[i-2] = args[i];
	}	

	environ = newptr;
	show_all();
	free(newptr);
}
