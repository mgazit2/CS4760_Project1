#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

static void print_usage();
static *program_name;

int main(int argc, char *argv[]){
	
	program_name = argv[0];	

	while (true) {
		int c = getopt(argc, argv, "hi:");
		if (c == -1) break;
		switch (c) {
			case 'h':
				print_usage();
				break;
			case 'i':
				printf("%s\n", argv[optind]);
				break;
			default:
				printf("No arg given, printing out current environment\n");
				getenv("env");
				break;
		}
	}	

	return EXIT_SUCCESS;	
}

void print_usage() {
	printf("Usage\n");
	printf("doenv [-h]\n");
	printf("doenv [-i] [var1=value] [var2=value] [...] {command 1 [; command2] [; ...]}\n");
}
