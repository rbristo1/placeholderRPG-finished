all:	main

main: main.o implementation/enemies.o implementation/screenManip.o implementation/battle.o implementation/mapMovements.o miniAudioSounds.o Character.o Enemy.o Player.o Game.o Action.o Weapon.o Item.o
	g++ -msse2 -mavx2 -lm -ldl -w -Wnarrowing -lpthread -lncurses -lmenu main.o implementation/enemies.o implementation/screenManip.o implementation/battle.o implementation/mapMovements.o miniAudioSounds.o Character.o Enemy.o Player.o Game.o Action.o Weapon.o Item.o -o main


main.o: main.cpp
	g++ -c main.cpp
enemies.o:  implementation/enemies.cpp implementation/enemies.h
	g++ -c implementation/enemies.cpp
screenManip.o: implementation/screenManip.cpp implementation/screenManip.h
	g++ -c implementation/screenManip.cpp
battle.o: implementation/battle.cpp implementation/battle.h
	g++ -c implementation/battle.cpp
mapMovements.o: implementation/mapMovements.cpp implementation/mapMovements.h
	g++ -c -w -Wnarrowing implementation/mapMovements.cpp
miniAudioSounds.o: miniAudioSounds.cpp miniAudioSounds.h
	g++ -c miniAudioSounds.cpp
Character.o: implementation/AndrewsFiles/Character.cpp implementation/AndrewsFiles/Character.h
	g++ -c implementation/AndrewsFiles/Character.cpp
Enemy.o: implementation/AndrewsFiles/Enemy.cpp implementation/AndrewsFiles/Enemy.h
	g++ -c implementation/AndrewsFiles/Enemy.cpp
Player.o: implementation/AndrewsFiles/Player.cpp implementation/AndrewsFiles/Player.h
	g++ -c implementation/AndrewsFiles/Player.cpp
Game.o: implementation/AndrewsFiles/Game.cpp implementation/AndrewsFiles/Game.h
	g++ -c implementation/AndrewsFiles/Game.cpp
Action.o: implementation/AndrewsFiles/Action.cpp implementation/AndrewsFiles/Action.h
	g++ -c implementation/AndrewsFiles/Action.cpp
Weapon.o: implementation/AndrewsFiles/Weapon.cpp implementation/AndrewsFiles/Weapon.h
	g++ -c implementation/AndrewsFiles/Weapon.cpp
Item.o: implementation/AndrewsFiles/Item.cpp implementation/AndrewsFiles/Item.h
	g++ -c implementation/AndrewsFiles/Item.cpp

clean:
	rm -f *.o main
