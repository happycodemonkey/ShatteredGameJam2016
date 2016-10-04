#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Shrimp.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

enum KEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

typedef struct boundbox {
    int x;
    int y;
    int width;
    int height;
}boundbox;

/**
bool collision(boundbox box1, boundbox box2) {
    if ((box1.x > box2.x + box2.width - 1) || 
            (box1.y > box2.y + box2.height - 1) ||
            (box2.x > box1.x + box1.width - 1) ||
            (box2.y > box1.y + box1.height - 1)) {
        return 0;
    }

    return 1;
} 
**/

bool collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    if ((x1 > x2 + w2 - 1) || 
            (y1 > y2 + h2 - 1) ||
            (x2 > x1 + w1 - 1) ||
            (y2 > y1 + h1 - 1)) {
        return 0;
    }

    return 1;
}

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *image = NULL;
    ALLEGRO_BITMAP *ball = NULL;

    Shrimp shrimp(SCREEN_W, SCREEN_H);

    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_dx = -4.0, bouncer_dy = 4.0;

    bool redraw = true;
    bool key[4] = {false, false, false, false};
    bool doexit = false;

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }

    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard\n");
        return -1;
    }

    if(!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize image addon\n");
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if(!display) {
        fprintf(stderr, "failed to create display\n");
        al_destroy_timer(timer);
        return -1;
    }


    ball = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
    if(!ball) {
        fprintf(stderr, "failed to initialize ball\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }

    al_set_target_bitmap(ball);
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    image = al_load_bitmap(shrimp.getImage());
    if (!image) {
        fprintf(stderr, "failed to load awesome shrimp image\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(ball);
        return -1;
    }


    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event queue\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(image);
        al_destroy_bitmap(ball);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(key[KEY_UP] && shrimp.getY() >= 4.0) {
                shrimp.setY(shrimp.getY() - 4.0);
            }

            if(key[KEY_DOWN] && shrimp.getY() <= SCREEN_H - shrimp.getSize() - 4.0) {
                shrimp.setY(shrimp.getY() + 4.0);
            }

            if(key[KEY_LEFT] && shrimp.getX() >= 4.0) {
                shrimp.setX(shrimp.getX() - 4.0);
            }

            if(key[KEY_RIGHT] && shrimp.getX() <= SCREEN_W - shrimp.getSize() - 4.0) {
                shrimp.setX(shrimp.getX() + 4.0);
            }

            if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {
                bouncer_dx = -bouncer_dx;
            }

            if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
                bouncer_dy = -bouncer_dy;
            }

            bouncer_x += bouncer_dx;
            bouncer_y += bouncer_dy;


            if (collision(shrimp.getX(), shrimp.getY(), shrimp.getSize() / 2, shrimp.getSize() / 2,
                        bouncer_x, bouncer_y, BOUNCER_SIZE, BOUNCER_SIZE)) {
                fprintf(stderr, "You got hit!!");
            }

            redraw = true;
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(image, shrimp.getX(), shrimp.getY(), 0);
            al_draw_bitmap(ball, bouncer_x, bouncer_y, 0);
            al_flip_display();
        }
    }
    
    al_destroy_bitmap(image);
    al_destroy_bitmap(ball);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
