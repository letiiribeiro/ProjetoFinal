IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = grafo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = grafo.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g -Wall

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) -g -Wall -ftest-coverage -fprofile-arcs

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
