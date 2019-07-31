#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x,float y,float z,float dx,float dy,float dz);
    glm::vec3 position;
    float rotation;
    float dx;
    float dy;
    float dz;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
