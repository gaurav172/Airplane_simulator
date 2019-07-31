#include "island.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Island::Island(float x,float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat body[4000],body2[4000],jn[4000],cbody[4000],cbody2[4000],cjn[4000];
    int n=200;
    float sz=200;
    float r1=2;
    float r2=4;
    float Pi=2*M_PI;
    float len=2;
    float ht=2;
    for(int i=0;i<200;i++)
    {
        body[9*i]=0.0f;
        body[9*i+1]=ht;
        body[9*i+2]=0.0f,
        body[9*i+3]=r1*cos(i*Pi/sz);
        body[9*i+4]=ht;
        body[9*i+5]=r1*sin(i*Pi/sz);
        body[9*i+6]=r1*cos((i+1)%n*Pi/sz);
        body[9*i+7]=ht;
        body[9*i+8]=r1*sin((i+1)%n*Pi/sz);
        body2[9*i]=0.0f;
        body2[9*i+1]=0.0f;
        body2[9*i+2]=0.0f,
        body2[9*i+3]=r2*cos(i*Pi/sz);
        body2[9*i+4]=0.0f;
        body2[9*i+5]=r2*sin(i*Pi/sz);
        body2[9*i+6]=r2*cos((i+1)%n*Pi/sz);
        body2[9*i+7]=0.0f;
        body2[9*i+8]=r2*sin((i+1)%n*Pi/sz);
        jn[18*i]=r1*cos(i*Pi/sz);
        jn[18*i+1]=ht;
        jn[18*i+2]=r1*sin(i*Pi/sz);
        jn[18*i+3]=r2*cos(i*Pi/sz);
        jn[18*i+4]=0.0f;
        jn[18*i+5]=r2*sin(i*Pi/sz);
        jn[18*i+6]=r2*cos((i+1)%n*Pi/sz);
        jn[18*i+7]=0.0f;
        jn[18*i+8]=r2*sin((i+1)%n*Pi/sz);
        jn[18*i+9]=r2*cos((i+1)%n*Pi/sz);
        jn[18*i+10]=0.0f;
        jn[18*i+11]=r2*sin((i+1)%n*Pi/sz);
        jn[18*i+12]=r1*cos((i+1)%n*Pi/sz);
        jn[18*i+13]=ht;
        jn[18*i+14]=r1*sin((i+1)%n*Pi/sz);
        jn[18*i+15]=r1*cos(i*Pi/sz);
        jn[18*i+16]=ht;
        jn[18*i+17]=r1*sin(i*Pi/sz);
    }
    for(int i=0;i<600;i++)
    {
        if(i%6<5)
        {
            cbody[3*i]=0.411;
            cbody[3*i+1]=0.847;
            cbody[3*i+2]=0.392;
        }
        else
        {
            cbody[3*i]=0.074;
            cbody[3*i+1]=0.678;
            cbody[3*i+2]=0.043;
        }
    }
    for(int i=0;i<600;i++)
    {
        if(i%6<3)
        {
            cbody2[3*i]=0.411;
            cbody2[3*i+1]=0.847;
            cbody2[3*i+2]=0.392;
        }
        else
        {
            cbody2[3*i]=0.074;
            cbody2[3*i+1]=0.678;
            cbody2[3*i+2]=0.043;
        }
    }
    for(int i=0;i<200;i++)
    {
        int curr=18*i;
        for(int j=0;j<6;j++)
        {
            if(j%2 && i%6<5)
            {
                cjn[curr+3*j]=0.411;
                cjn[curr+3*j+1]=0.847;
                cjn[curr+3*j+2]=0.392;
            }
            else
            {
                cjn[curr+3*j]=0.074;
                cjn[curr+3*j+1]=0.678;
                cjn[curr+3*j+2]=0.043;
            }
        }
    }
    this->Body = create3DObject(GL_TRIANGLES, 3*200, body, cbody, GL_FILL);
    this->Body2 = create3DObject(GL_TRIANGLES, 3*200, body2,cbody2, GL_FILL);
    this->mid = create3DObject(GL_TRIANGLES, 6*200, jn,cjn, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Body);
    draw3DObject(this->Body2);
    draw3DObject(this->mid);
}

void Island::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Island::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

