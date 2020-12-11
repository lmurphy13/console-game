CC=gcc

GAME = game.c
ENGINE = engine/engine.c \
			engine/test.c

ENGINE_H = engine/include/engine.h

engine:
	$(CC) -o test $(ENGINE_H) $(ENGINE)

all: 
	$(CC) -o game $(GAME)
	

clean:
	rm -f *.o