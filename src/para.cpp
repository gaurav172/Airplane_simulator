#include "para.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Para::Para(float x,float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed=-0.02;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat Lbody[] = {
         -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        // -1.0f, 1.0f, 1.0f,
        // -1.0f,-1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f
    };
    for(int i=0;i<90;i++)
        Lbody[i]*=0.3;
    this->Body = create3DObject(GL_TRIANGLES, 30, Lbody,COLOR_BLACK, GL_FILL);
    GLfloat Blon[4000],CBlon[4000];
    int n=200;
    float sz=200;
    float r1=0.8;
    float Pi=2*M_PI;
    float ht=1;
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
        if(i%9<3)
        {
            CBlon[9*i+3]=0.368f;
            CBlon[9*i+4]=0.105f;
            CBlon[9*i+5]=0.552f;
            CBlon[9*i+6]=0.369f;
            CBlon[9*i+7]=0.105f;
            CBlon[9*i+8]=0.552f;
        }
        if(i%9<6)
        {
            CBlon[9*i+3]=0.949f;
            CBlon[9*i+4]=0.956f;
            CBlon[9*i+5]=0.121f;
            CBlon[9*i+6]=0.949f;
            CBlon[9*i+7]=0.956f;
            CBlon[9*i+8]=0.121f;
        }
        if(i%3==2)
        {
            CBlon[9*i+3]=0.121f;
            CBlon[9*i+4]=0.956f;
            CBlon[9*i+5]=0.607f;
            CBlon[9*i+6]=0.121f;
            CBlon[9*i+7]=0.956f;
            CBlon[9*i+8]=0.607f;
        }
    }
    this->Baloon = create3DObject(GL_TRIANGLES, 3*200, Blon,CBlon, GL_FILL);  
}

void Para::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Body);
    draw3DObject(this->Baloon);
}

void Para::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Para::tick() {
    this->position.y+=this->speed;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

