#ifndef SHRIMP_H
#define SHRIMP_H

class Shrimp {
/**
 *
 * Todo: figure out how to set the image
 * better programmatically
 *
 * */
    private:
        float shrimp_x;
        float shrimp_y;
        float shrimp_dx;
        float shrimp_dy;
        int size;
        const char* image = NULL;

    public:
        Shrimp(int SCREEN_W, int SCREEN_H);
        float getX();
        float getY();
        float getSize();
        void setX(float x);
        void setY(float y);
        const char* getImage();
};

#endif
