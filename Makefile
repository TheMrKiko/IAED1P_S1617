CC=gcc
CFLAGS=-Wall 
FILENAME=projecto

run: $(FILENAME)
	./$(FILENAME)

$(FILENAME): $(FILENAME).c

clean: $(FILENAME)
	rm $(FILENAME)
 
