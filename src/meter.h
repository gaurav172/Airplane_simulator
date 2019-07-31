#include "main.h"

#ifndef METER_H
#define METER_H


class Meter {
public:
    Meter() {}
    Meter(float x,float y,float z,float sx);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *Dial;
    VAO *Outer;
    VAO *Inner;
};

#endif // BALL_H
