#include "cannon.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Cannon::Cannon(float x,float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed=-0.02;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat Blon[4000],CBlon[4000];
    int n=200;
    float sz=200;
    float r1=2;
    float Pi=2*M_PI;
    float ht=2;
    float b=0.5;
    for(int i=0;i<200;i++)
    {
        Blon[9*i]=0.0f;
        Blon[9*i+1]=b+ht;
        Blon[9*i+2]=0.0f;
        Blon[9*i+3]=r1*cos(i*Pi/sz);
        Blon[9*i+4]=b;
        Blon[9*i+5]=r1*sin(i*Pi/sz);
        Blon[9*i+6]=r1*cos((i+1)%n*Pi/sz);
        Blon[9*i+7]=b;
        Blon[9*i+8]=r1*sin((i+1)%n*Pi/sz);
    }
    for(int i=0;i<200;i++)
    {
        CBlon[9*i]=1.0f;
        CBlon[9*i+1]=1.0f;
        CBlon[9*i+2]=1.0f;
        CBlon[9*i+3]=153.0f/256.0f;
        CBlon[9*i+4]=-.0f;
        CBlon[9*i+5]=153.0f/256.0f;
        CBlon[9*i+6]=153.0f/256.0f;
        CBlon[9*i+7]=0.0f;
        CBlon[9*i+8]=153.0f/256.0f;
        // if(i%9<3)
        // {
        //     CBlon[9*i+3]=153.0f/256.0f;
        //     CBlon[9*i+4]=0.0f;
        //     CBlon[9*i+5]=153/256.0f;
        //     CBlon[9*i+6]=1.0f;
        //     CBlon[9*i+7]=1.0f;
        //     CBlon[9*i+8]=1.0f;
        // }
  
    }
    this->Baloon = create3DObject(GL_TRIANGLES, 3*200, Blon,CBlon, GL_FILL);  
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Baloon);
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
    this->position.y+=this->speed;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

