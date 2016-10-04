#include "Boundbox.h"

Boundbox::Boundbox() {

}

Boundbox::Boundbox(float x, float y, float width, float height) {
    x = x;
    y = y;
    width = width;
    height = height;
}

bool Boundbox::collision(Boundbox box1, Boundbox box2) {
    if ((box1.getX() > box2.getX() + box2.getWidth() - 1) ||
            (box1.getY() > box2.getY() + box2.getHeight() - 1) ||
           (box2.getX() > box1.getX() + box1.getWidth() -1 ) ||
          (box2.getY() > box1.getY() + box1.getHeight() - 1)) {
        return 0;
    }

    return 1;
}

void Boundbox::setX(float x) {
    x = x;
}

void Boundbox::setY(float y) {
    y = y;
}

void Boundbox::setWidth(float width) {
    width = width;
}

void Boundbox::setHeight(float height) {
    height = height;
}
