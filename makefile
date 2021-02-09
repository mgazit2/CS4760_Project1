CC = gcc
CFLAGS = -Wall -g

EXE = doenv
OBJ = doenv.o
OUT = $(EXE)

.SUFFIXES: .c .o
.PHONY: all clean

all : $(OUT)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	/bin/rm -f *.o $(EXE)
