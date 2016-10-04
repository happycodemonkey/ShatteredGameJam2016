#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "Shrimp.h"

Shrimp::Shrimp(int SCREEN_W, int SCREEN_H) {
    shrimp_x = SCREEN_W / 2.0 - size / 2.0;
    shrimp_y = SCREEN_H / 2.0 - size / 2.0;
    shrimp_dx = -4.0, shrimp_dy = 4.0;

    image = "shrimpTransparent.png";
    size = 200;
}

float Shrimp::getX() {
    return shrimp_x;
}

void Shrimp::setX(float x) {
    shrimp_x = x;
}

float Shrimp::getY() {
    return shrimp_y;
}

void Shrimp::setY(float y) {
    shrimp_y = y;
}

float Shrimp::getSize() {
    return size;
}

const char* Shrimp::getImage() {
    return image;
}
