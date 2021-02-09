# CS4760_Project1
# Matan Gazit
#
MAKE:
	To make this project, type 'make' into the command line when in the project directory
	To clean the directory after compilation, type 'make clean' into the command line when in the project directory

RUN:
	To run this file, type './doenv -h' into the command line when in the project directory to pull up the usage options

PURPOSE:
	The purpose of this project is to replicate a select number of functions of the env(1) user command

	doenv - run a program in a modified environment

COMMENTS:

	strtok(3) and strchr(3) are both powerful & useful functions that significantly improved quality of output
	
	I'm not entirely sure if my way for going about showing the environment is correct, as getenv was not used.
		- Rather, a more roundabout way was used where the environ extern was called and printed out line by
		line.

REFERENCES:

	Used the code found in the below GitHub repository to begin structuring my own project
		Used the writer's for loop found in the showAll() function to iterate through a ** throughout my project
	https://github.com/SivaKrrish/Operating-System/blob/master/doenv.c						

	Used the code found in the below GitHub repository to construct a working getopt loop, as I was not familiar with
	the getopt() data structure before this
	https://github.com/jaredible/CS4760-Project-1/blob/master/mydu.c

	strtok(3) man page
	https://man7.org/linux/man-pages/man3/strtok.3.html

	gnu section discussing strtok(3)
	https://www.gnu.org/software/libc/manual/html_node/Finding-Tokens-in-a-String.html

	strchr(3) man page
	https://man7.org/linux/man-pages/man3/strchr.3.html
		
	env(1) man page
	https://man7.org/linux/man-pages/man1/env.1.html
