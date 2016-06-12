IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -g -Wall -ftest-coverage -fprofile-arcs -lncurses

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = grafo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = grafo.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
