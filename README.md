# Shattered Game Jam 2016

## Theme: Shrimp

This is my entry for the 2016 Shattered Game Jam, written in C++ using the Allegro game library.

In order to build it, you must have Allegro core and the Allegro image add-on installed.

```
sudo add-apt-repository ppa:allegro/5.2
sudo apt-get update
sudo apt-get install liballegro5-dev liballegro-image5-dev

```
[Source](https://wiki.allegro.cc/index.php?title=Install_Allegro_from_Ubuntu_PPAs)


To build manually:

```
g++ -g main.cpp Shrimp.cpp -o shatteredGameJam `pkg-config --cflags --libs allegro-5 allegro_image-5`

```

Using the Makefile:

```
make allegro="`pkg-config --cflags --libs allegro-5 allegro_image-5`"

```

