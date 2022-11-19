LIBS = -lSDL2 -lSDL2_mixer
CC = clang

all: cyntha2

cyntha2: ./src/main.c
	$(CC) -o cyntha2 ./src/*.c $(LIBS) -mwindows

clean:
	rm cyntha2