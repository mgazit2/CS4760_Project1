#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

static void print_usage();
static void senv(char *a, char *b);
static void update_env(char **args, int argc);
static void  show_all();
static *program_name;

int main(int argc, char *argv[]){
	
	program_name = argv[0];
	int i = 0;
	char *args;

	printf("Total args: %d\n", argc);
	if (argc == 1) {
		printf("%s\n", getenv("env"));
		//show_all();
		printf("No arguments given\n");
		return EXIT_SUCCESS;
	}	

	while (true) {
		int c = getopt(argc, argv, "hi:");
		if (c == -1) break;
		switch (c) {
			case 'h':
				print_usage();
				break;
			case 'i':
				update_env(argv, argc);
				break;
			default:
				printf("ERROR\n");
				break;
		}
	}

	//args = argv[strlen(argv)];

	for (i; i < strlen(argv); i++) {
		if (system(argv[i]) == -1) {
		perror("Error=");
		}
	}	
	//senv("TEST", "ABC");	
	/*if (setenv("TEST", "abc", 1) == -1) {
		perror("Failed to set TEST to abc\n");
		exit(1);
	}*/

	//printf("%s\n", getenv("TEST"));

	/*int m = system("./doenv");
	printf("%d\n", m);
	if (m == -1) {
		perror("ERROR\n");
		exit(1);
	}
	*/
	return EXIT_SUCCESS;	
}

void print_usage() {
	printf("Usage\n");
	printf("doenv [-h]\n");
	printf("doenv [-i] [var1=value] [var2=value] [...] {command 1 [; command2] [; ...]}\n");
}

void senv(char *a, char *b) {
	if (setenv(a, b, 1) == -1) {
		perror("ERROR\n");
		exit(1);
	}
}

void update_env(char **args, int argc) {
	char *arg = optarg;
	putenv(arg);
	if (optind < argc) {
		for (;optind<argc;optind++)
			putenv(args[optind]);
	}
	printf("Modified Environment\n");
	show_all();
}

void show_all() {
	char **p;
	system("clear");
	extern char **environ;
	printf("Environment Variables");
	for (p  = environ; *p != NULL; p++)
		printf("%s\n", *p);
}
