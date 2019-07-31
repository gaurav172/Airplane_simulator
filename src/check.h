#include "main.h"

#ifndef CHECK_H
#define CHECK_H


class Check {
public:
    Check() {}
    Check(float x,float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
