CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

all: starwars.out
	./starwars.out map.txt

starwars.out: main.o Bullet.o Things.o Dynamic_enemy.o Ship.o Ceasefire.o Game.o Power_up.o Struct.hpp
	$(CC) main.o Bullet.o Things.o Dynamic_enemy.o Ship.o Ceasefire.o Game.o Power_up.o rsdl.cpp $(FLAGS) -o starwars.out

main.o: main.cpp Things.h Game.h Bullet.h
	$(CC) $(COMPILE_FLAGS) main.cpp

Game.o: Game.h Dynamic_enemy.h Ship.h Ceasefire.h Power_up.h Game.cpp
	$(CC) $(COMPILE_FLAGS) Game.cpp

Ceasefire.o: Ceasefire.h Ceasefire.cpp
	$(CC) $(COMPILE_FLAGS) Ceasefire.cpp

Ship.o: Ship.h Things.h Power_up.h Ship.cpp
	$(CC) $(COMPILE_FLAGS) Ship.cpp

Dynamic_enemy.o: Dynamic_enemy.h Things.h Dynamic_enemy.cpp
	$(CC) $(COMPILE_FLAGS) Dynamic_enemy.cpp

Things.o: Things.h Things.cpp
	$(CC) $(COMPILE_FLAGS) Things.cpp

Bullet.o: Bullet.h Bullet.cpp
	$(CC) $(COMPILE_FLAGS) Bullet.cpp

Power_up.o: Power_up.h Struct.hpp Power_up.cpp
	$(CC) $(COMPILE_FLAGS) Power_up.cpp

Things.h: Bullet.h

Bullet.h: Struct.hpp

.PHONY: clean

clean:
	rm *.o