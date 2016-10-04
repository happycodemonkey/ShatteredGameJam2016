CC=g++

shrimpmake: main.cpp
	$(CC) -o shatteredGameJam main.cpp Shrimp.cpp $(allegro)

