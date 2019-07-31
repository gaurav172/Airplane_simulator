#include "dash.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

Dash::Dash(float x,float y,float z,float a,float b,float c) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    GLfloat HorB[400],verB[400],Bdr[400];
    float d=0.01,D=0.4,H=2;
    int vc=0;
    a=min(a,2.0f-d);
    b=min(b,2.0f-d);
    c=min(c,2.0f-d);
    GLfloat Fuel[] = {
        d,d,0.0f,
        D-d,d,0.0f,
        D-d,a,0.0f,
        D-d,a,0.0f,
        d,d,0.0f,
        d,a,0.0f
    };
      GLfloat Alt[] = {
        d,d,0.0f,
        D-d,d,0.0f,
        D-d,b,0.0f,
        D-d,b,0.0f,
        d,d,0.0f,
        d,b,0.0f
    };
      GLfloat Health[] = {
        d,d,0.0f,
        D-d,d,0.0f,
        D-d,c,0.0f,
        D-d,c,0.0f,
        d,d,0.0f,
        d,c,0.0f
    };
    for(int i=0;i<6;i++)
    {
        Alt[3*i]=Fuel[3*i]+0.6;
        Health[3*i]=Fuel[3*i]+1.2;
    }
    GLfloat A[ ] = {
        0.0f,0.0f,0.0f,
        D,0.0f,0.0f,
        D,d,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,d,0.0f,
        D,d,0.0f
    };
    GLfloat B[] = {
        0.0f,0.0f,0.0f,
        d,0.0f,0.0f,
        d,H,0.0f,
        d,H,0.0f,
        0.0f,H,0.0f,
        0.0f,0.0f,0.0f
    };
    for(int i=0;i<6*3;i++)
    {
        HorB[i]=A[i];
        verB[i]=B[i];
    }
    for(int i=0;i<6;i++)
    {
        HorB[18+3*i]=HorB[3*i];
        HorB[18+3*i+1]=HorB[3*i+1]+H-d;
        HorB[18+3*i+2]=HorB[3*i+2];
    }
    for(int i=0;i<6;i++)
    {
        verB[18+3*i]=verB[3*i]+D-d;
        verB[18+3*i+1]=verB[3*i+1];
        verB[18+3*i+2]=verB[3*i+2];
    }
    for(int i=0;i<36;i++)
    {
        Bdr[i]=HorB[i];
        Bdr[i+36]=verB[i];
    }
    for(int i=0;i<72;i++)
    {
        if(i%3==0)
        {
            Bdr[72+i]=Bdr[i]+0.6;
            Bdr[144+i]=Bdr[i]+1.2;
        }
        else
        {
            Bdr[72+i]=Bdr[i];
            Bdr[144+i]=Bdr[i];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 72, Bdr, COLOR_Bd, GL_FILL);
    this->Fl = create3DObject(GL_TRIANGLES, 6, Fuel, COLOR_Fl, GL_FILL);
    this->At = create3DObject(GL_TRIANGLES, 6, Alt, COLOR_Alt, GL_FILL);
    this->Hl = create3DObject(GL_TRIANGLES, 6, Health, COLOR_Ht, GL_FILL);
}

void Dash::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->Fl);
    draw3DObject(this->At);
    draw3DObject(this->Hl);

}

void Dash::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dash::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

