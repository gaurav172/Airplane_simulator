#include "ball.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Ball::Ball(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    this->co_x={1,0,0};
    this->co_y={0,1,0};
    this->co_z={0,0,1};
    this->rotation = glm::mat4(1.0);
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat body[4000],body2[4000],jn[4000];
    int n=200;
    float sz=200;
    float r=0.3;
    float Pi=2*M_PI;
    float len=2;
    for(int i=0;i<200;i++)
    {
        body[9*i]=0.0f;
        body[9*i+1]=0.0f;
        body[9*i+2]=0.0f,
        body[9*i+3]=r*cos(i*Pi/sz);
        body[9*i+4]=r*sin(i*Pi/sz);
        body[9*i+5]=0.0f;
        body[9*i+6]=r*cos((i+1)%n*Pi/sz);
        body[9*i+7]=r*sin((i+1)%n*Pi/sz);
        body[9*i+8]=0;
        body2[9*i]=0.0f;
        body2[9*i+1]=0.0f;
        body2[9*i+2]=len,
        body2[9*i+3]=r*cos(i*Pi/sz);
        body2[9*i+4]=r*sin(i*Pi/sz);
        body2[9*i+5]=len;
        body2[9*i+6]=r*cos((i+1)%n*Pi/sz);
        body2[9*i+7]=r*sin((i+1)%n*Pi/sz);
        body2[9*i+8]=len;
        jn[18*i]=r*cos(i*Pi/sz);
        jn[18*i+1]=r*sin(i*Pi/sz);
        jn[18*i+2]=0.0f;
        jn[18*i+3]=r*cos(i*Pi/sz);
        jn[18*i+4]=r*sin(i*Pi/sz);
        jn[18*i+5]=len;
        jn[18*i+6]=r*cos((i+1)%n*Pi/sz);
        jn[18*i+7]=r*sin((i+1)%n*Pi/sz);
        jn[18*i+8]=len;
        jn[18*i+9]=r*cos((i+1)%n*Pi/sz);
        jn[18*i+10]=r*sin((i+1)%n*Pi/sz);
        jn[18*i+11]=len;
        jn[18*i+12]=r*cos((i+1)%n*Pi/sz);
        jn[18*i+13]=r*sin((i+1)%n*Pi/sz);
        jn[18*i+14]=0.0f;
        jn[18*i+15]=r*cos(i*Pi/sz);
        jn[18*i+16]=r*sin(i*Pi/sz);
        jn[18*i+17]=0.0f;
    }
    GLfloat wings[] = {
        //wings
       //LW
       0.0f,0.0f,0.4f,
       0.0f,0.0f,0.8f,
       2.5f,0.0f,0.6f,
       0.0f,0.0f,0.4f,
       0.0f,-0.1f,0.4f,
       2.5f,0.0f,0.6f,
       0.0f,0.0f,0.8f,
       0.0f,-0.1f,0.8f,
       2.5f,0.0f,0.6f,
       0.0f,0.0f,1.6f,
       0.0f,0.0f,1.8f,
       1.2f,0.0f,1.7f,
       0.0f,0.0f,1.6f,
       0.0f,-0.1f,1.6f,
       1.2f,0.0f,1.7f,
       0.0f,0.0f,1.8f,
       0.0f,-0.1f,1.8f,
       1.2f,0.0f,1.7f,

       //RW
       0.0f,0.0f,0.4f,
       0.0f,0.0f,0.8f,
       -2.5f,0.0f,0.6f,
       0.0f,0.0f,0.4f,
       0.0f,-0.1f,0.4f,
       -2.5f,0.0f,0.6f,
       0.0f,0.0f,0.8f,
       0.0f,-0.1f,0.8f,
       -2.5f,0.0f,0.6f,
       0.0f,0.0f,1.6f,
       0.0f,0.0f,1.8f,
       -1.2f,0.0f,1.7f,
       0.0f,0.0f,1.6f,
       0.0f,-0.1f,1.6f,
       -1.2f,0.0f,1.7f,
       0.0f,0.0f,1.8f,
       0.0f,-0.1f,1.8f,
       -1.2f,0.0f,1.7f,
    };

    this->Body = create3DObject(GL_TRIANGLES, 3*200, body, COLOR_RED, GL_FILL);
    this->Body2 = create3DObject(GL_TRIANGLES, 3*200, body2,COLOR_RED, GL_FILL);
    this->mid = create3DObject(GL_TRIANGLES, 6*200, jn,COLOR_GREEN, GL_FILL);
    this->Wing = create3DObject(GL_TRIANGLES, 12*3, wings, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // this->rotationx=this->rotationy=this->rotationz=0;
    this->rotation=rotatey*rotatex*rotatez;
    Matrices.model *= (translate * this->rotation);
    this->co_x  = {this->rotation[0][0],this->rotation[0][1],this->rotation[0][2]};
    this->co_y  = {this->rotation[1][0],this->rotation[1][1],this->rotation[1][2]};
    this->co_z  = {this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]};
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->Wing);
    draw3DObject(this->Body);
    draw3DObject(this->Body2);
    draw3DObject(this->mid);
}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

