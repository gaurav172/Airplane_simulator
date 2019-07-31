#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x,float y,float z);
    glm::vec3 position;
    float rotation;
    float r1;
    float r2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speed;
private:
    VAO *Outer; 
    VAO *Inner;
};

#endif // BALL_H
