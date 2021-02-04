CC = gcc
CFLAGS = -Wall -g

EXE = doenv2
OBJ = doenv2.o
OUT = $(EXE)

.SUFFIXES: .c .o
.PHONY: all clean

all : $(OUT)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	/bin/rm -f *.o
