#include "main.h"

#ifndef DASH_H
#define DASH_H


class Dash {
public:
    Dash() {}
    Dash(float x,float y,float z,float a,float b,float c);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *Fl;
    VAO *At;
    VAO *Hl;
};

#endif // BALL_H
