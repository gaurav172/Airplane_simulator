#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x,float y,float z,float sx,float sy,float sz);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float sx;
    float sy;
    float sz;
private:
    VAO *object;
};

#endif // BALL_H
