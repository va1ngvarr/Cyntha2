LIBS = -lSDL2 -lSDL2_mixer
CC = clang

all: cyntha2

cyntha2: main.c
	$(CC) -o cyntha2 *.c $(LIBS)

clean:
	rm cyntha2