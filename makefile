all:	main

main: main.o implementation/enemies.o implementation/screenManip.o implementation/battle.o implementation/mapMovements.o miniAudioSounds.o Character.o Enemy.o Player.o Action.o Weapon.o Item.o
	g++ -msse2 -mavx2 -lm -ldl -lpthread -pthread main.o implementation/enemies.o implementation/screenManip.o implementation/battle.o implementation/mapMovements.o miniAudioSounds.o Character.o Enemy.o Player.o Action.o Weapon.o Item.o -o main


main.o: main.cpp
	g++ -c -pthread main.cpp
enemies.o:  implementation/enemies.cpp implementation/enemies.h
	g++ -c -pthread implementation/enemies.cpp
screenManip.o: implementation/screenManip.cpp implementation/screenManip.h
	g++ -c -pthread implementation/screenManip.cpp
battle.o: implementation/battle.cpp implementation/battle.h
	g++ -c -pthread implementation/battle.cpp
mapMovements.o: implementation/mapMovements.cpp implementation/mapMovements.h
	g++ -c -pthread implementation/mapMovements.cpp
miniAudioSounds.o: miniAudioSounds.cpp miniAudioSounds.h
	g++ -c -pthread miniAudioSounds.cpp
Character.o: implementation/AndrewsFiles/Character.cpp implementation/AndrewsFiles/Character.h
	g++ -c -pthread implementation/AndrewsFiles/Character.cpp
Enemy.o: implementation/AndrewsFiles/Enemy.cpp implementation/AndrewsFiles/Enemy.h
	g++ -c -pthread implementation/AndrewsFiles/Enemy.cpp
Player.o: implementation/AndrewsFiles/Player.cpp implementation/AndrewsFiles/Player.h
	g++ -c -pthread implementation/AndrewsFiles/Player.cpp
Action.o: implementation/AndrewsFiles/Action.cpp implementation/AndrewsFiles/Action.h
	g++ -c -pthread implementation/AndrewsFiles/Action.cpp
Weapon.o: implementation/AndrewsFiles/Weapon.cpp implementation/AndrewsFiles/Weapon.h
	g++ -c -pthread implementation/AndrewsFiles/Weapon.cpp
Item.o: implementation/AndrewsFiles/Item.cpp implementation/AndrewsFiles/Item.h
	g++ -c -pthread implementation/AndrewsFiles/Item.cpp

clean:
	rm -f *.o main
