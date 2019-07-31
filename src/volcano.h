#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x,float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speed;
private:
    VAO *Body;
    VAO *Baloon; 
};

#endif // BALL_H
