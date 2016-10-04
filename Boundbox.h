#ifndef BOUNDBOX
#define BOUNDBOX

class Boundbox {
    private:
        float x;
        float y;
        float width;
        float height;

    public:
        Boundbox();
        Boundbox(float x, float y, float width, float height);
        bool collision(Boundbox box1, Boundbox box2);
        float getX() { return x; }
        float getY() { return y; }
        float getWidth() { return width; }
        float getHeight() { return height; }
        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
};

#endif
