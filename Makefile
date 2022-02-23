But : dragon

OFILES= mouvement.o \
		collision.o \
		gameover.o \
		main.o

CC = gcc




gameover.o : gameover.c gameover.h

mouvement.o : mouvement.c mouvement.h

collision.o :collision.c collision.h

main.o : main.c 


dragon : $(OFILES)
	$(CC) -o dragon $(OFILES) $(CFLAGS) -lgraph

.PHONY : clean

clean : 
	rm -f $(OFILES)

run : dragon
	./dragon