#include "check.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Check::Check(float x,float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float d1=2,d2=1,h1=2,h2=2;
    GLfloat arr[] = {
       //Arrow Base
       d1,0.0f,d1,
       -d1,0.0f,d1,
       -d1,0.0f,-d1,
       -d1,0.0f,-d1,
       d1,0.0f,-d1,
       d1,0.0f,d1,
       //Down
       d1,0.0f,d1,
       -d1,0.0f,d1,
       0.0f,-h2,0.0f,
       d1,0.0f,d1,
       d1,0.0f,-d1,
       0.0f,-h2,0.0f,
       d1,0.0f,-d1,
       -d1,0.0f,-d1,
       0.0f,-h2,0.0f,
       -d1,0.0f,-d1,
       -d1,0.0f,d1,
       0.0f,-h2,0.0f,
       //Up
       d2,0.0f,d2,
       d2,0.0f,-d2,
       d2,h1,d2,
       d2,h1,d2,
       d2,h1,-d2,
       d2,0.0f,-d2, 
       d2,0.0f,d2,
       -d2,0.0f,d2,
       -d2,h1,d2,
       -d2,h1,d2,
       d2,h1,d2,
       d2,0.0f,d2,
       -d2,0.0f,d2,
       -d2,0.0f,-d2,
       -d2,h1,-d2,
       -d2,h1,-d2,
       -d2,h1,d2,
       -d2,0.0f,d2,
       -d2,0.0f,-d2,
       d2,0.0f,-d2,
       d2,h1,-d2,
       d2,h1,-d2,
       -d2,h1,-d2,
       -d2,0.0f,-d2,
         d2,h1,d2,
       -d2,h1,d2,
       -d2,h1,-d2,
       -d2,h1,-d2,
       d2,h1,-d2,
       d2,h1,d2
    };
    this->object = create3DObject(GL_TRIANGLES, 48, arr,COLOR_RED, GL_FILL);
}

void Check::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Check::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Check::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

