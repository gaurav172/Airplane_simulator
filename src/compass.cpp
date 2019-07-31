#include "compass.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Compass::Compass(float x,float y,float z,float theta) {
    this->position = glm::vec3(x, y, z);
    this->rotation = theta;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float r1=0.65,r2=0.5,w=0.1;
    GLfloat Dial [] = {
        0.0f,r2,0.0f,
        0.0f,-r2,0.0f,
        w,0.0f,0.0f,
        0.0f,r2,0.0f,
        0.0f,-r2,0.0f,
        -w,0.0f,0.0f,
    };
    GLfloat CDial [] = {
        255.0f/256.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,
        102.0f/256.0f,0.0f,0.0f,
         255.0f/256.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,
        102.0f/256.0f,0.0f,0.0f
    };
    int n=200;
    float sz=200,Pi=2*M_PI;
    GLfloat A1[2000],A2[2000];
    for(int i=0;i<200;i++)
    {
        A1[9*i]=0.0f;
        A1[9*i+1]=0.0f;
        A1[9*i+2]=0.0f;
        A1[9*i+3]=r1*cos((i*Pi)/sz);
        A1[9*i+4]=r1*sin((i*Pi)/sz);
        A1[9*i+5]=0.0f;
        A1[9*i+6]=r1*cos((i+1)%n*Pi/sz);
        A1[9*i+7]=r1*sin((i+1)%n*Pi/sz);
        A1[9*i+8]=0.0f;
        A2[9*i]=0.0f;
        A2[9*i+1]=0.0f;
        A2[9*i+2]=0.0f;
        A2[9*i+3]=r2*cos((i*Pi)/sz);
        A2[9*i+4]=r2*sin((i*Pi)/sz);
        A2[9*i+5]=0.0f;
        A2[9*i+6]=r2*cos((i+1)%n*Pi/sz);
        A2[9*i+7]=r2*sin((i+1)%n*Pi/sz);
        A2[9*i+8]=0.0f;
    }
    this->Dial = create3DObject(GL_TRIANGLES, 6, Dial,CDial, GL_FILL);
    this->Outer = create3DObject(GL_TRIANGLES, 3*200, A1,COLOR_O, GL_FILL);
    this->Inner = create3DObject(GL_TRIANGLES, 3*200, A2,COLOR_I, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Outer);
    draw3DObject(this->Inner);
    draw3DObject(this->Dial);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Compass::tick() {
    this->position.y-=0.1;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

