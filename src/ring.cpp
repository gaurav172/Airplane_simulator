#include "ring.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Ring::Ring(float x,float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat Blon[10000],CBlon[4000],Blon2[4000];
    int n=200;
    float sz=200;
    float r1=2.3,r2=2;
    float Pi=2*M_PI;
    float ht=2;
    float b=0.5;
    int vc=0;
    for(int i=0;i<400;i++)
    {
        Blon[vc++]=r1*cos((i/sz)*Pi);        
        Blon[vc++]=r1*sin((i/sz)*Pi);
        Blon[vc++]=0;
        Blon[vc++]=r1*cos(((i+1)%n/sz)*Pi);        
        Blon[vc++]=r1*sin(((i+1)%n/sz)*Pi);
        Blon[vc++]=0;
        Blon[vc++]=r2*cos((i/sz)*Pi);        
        Blon[vc++]=r2*sin((i/sz)*Pi);
        Blon[vc++]=0;
        Blon[vc++]=r2*cos((i/sz)*Pi);        
        Blon[vc++]=r2*sin((i/sz)*Pi);
        Blon[vc++]=0;
        Blon[vc++]=r2*cos(((i+1)%n/sz)*Pi);        
        Blon[vc++]=r2*sin(((i+1)%n/sz)*Pi);
        Blon[vc++]=0;
        Blon[vc++]=r1*cos(((i+1)%n/sz)*Pi);        
        Blon[vc++]=r1*sin(((i+1)%n/sz)*Pi);
        Blon[vc++]=0;
    }
    this->Outer = create3DObject(GL_TRIANGLES, vc/3, Blon,COLOR_RED, GL_FILL);  
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Outer);
    // draw3DObject(this->Inner);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    this->position.y+=this->speed;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

