#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float z, color_t color);
    glm::vec3 position;
    glm::vec3 co_x,co_y,co_z;
    glm:: mat4 rotation;
    float rotationx;
    float rotationy;
    float rotationz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *Body;
    VAO *Body2;
    VAO *mid;
    VAO *Wing;
    VAO *Tail;
};

#endif // BALL_H
