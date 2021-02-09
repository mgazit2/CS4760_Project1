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
