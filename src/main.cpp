#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "bomb.h"
#include "missile.h"
#include "para.h"
#include "island.h"
#include "cannon.h"
#include "bullet.h"
#include "ring.h"
#include "check.h"
#include "fuel.h"
#include "volcano.h"
#include "dash.h"
#include "compass.h"
#include "rect.h"
#include "meter.h"

#define mp make_pair
#define GLM_ENABLE_EXPERIMENTAL
using namespace std;

GLMatrices Matrices,DMatrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
int score=0,sp=0;
vector<Rect> Ten,Unit,Hund;
string digDisplay[10];
Sea sea;
bool broll=0;
float prx=0;
float sz=0,sy=0;
float fric=0.01,gr=-0.0001;
vector<Island> Iland;
vector<Missile> Mfire;
vector<Bomb> BomFire;
vector<Para> Pchute;
vector<Cannon> Enemy[20];
vector<Bullet> Blt;
vector<Ring> Rng;
vector<Fuel> F;
vector<Volcano> Vlc;
vector<pair<int,int> > cp;
float px,pz;
float CurrFuel=50,CurrHealth=100;
int view=0,prv=0,curr=0,mpr=0,fire=0,cpoint=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
double x_pos,y_pos;
float camera_rotation_angle = 0;
int viewdiff=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void getnext()
{
    float x=cp[cpoint].first;
    float z=cp[cpoint].second;
    float cx=ball1.position.x;
    float cz=ball1.position.z;
    float D=sqrt(pow(x-cx,2)+pow(z-cz,2));
    float d=min(D,300.0f);
    px=cx+(x-cx)*d/D;
    pz=cz+(z-cz)*d/D;
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    float cx,cy,cz,lx,ly,lz,ux=0,uy=1,uz=0;

    //Back View
    if(view==0)
    {
        cx=ball1.position.x+5*ball1.co_z.x+ball1.co_y.x*2;
        cy=ball1.position.y+5*ball1.co_z.y+ball1.co_y.y*2;
        cz=ball1.position.z+5*ball1.co_z.z+ball1.co_y.z*2;
        lx=ball1.position.x;
        ly=ball1.position.y;
        lz=ball1.position.z;
        ux=0;
        uy=1;
        uz=0;
    }
   
    //Plane view
    if(view==1)
    {
        cx=ball1.position.x-1*ball1.co_z.x;
        cy=ball1.position.y-1*ball1.co_z.y;
        cz=ball1.position.z-1*ball1.co_z.z;
        lx=ball1.position.x-4*ball1.co_z.x;
        ly=ball1.position.y-4*ball1.co_z.y;
        lz=ball1.position.z-4*ball1.co_z.z;
        ux=ball1.co_y.x;
        uy=ball1.co_y.y;
        uz=ball1.co_y.z;
    }

    //Top view
    if(view==2)
    {
        cx=ball1.position.x;
        cy=ball1.position.y+10;
        cz=ball1.position.z;
        lx=ball1.position.x;
        ly=ball1.position.y;
        lz=ball1.position.z;
        ux=0;
        uy=0;
        uz=-1;
    }
    if(view==3)
    {
        cx=5;
        cy=5;
        cz=5;
        lx=ball1.position.x;
        ly=ball1.position.y;
        lz=ball1.position.z;
    }
    if(view==4)
    {
        x_pos=(x_pos-1000)/1000;
        y_pos=(y_pos-1000)/1000;
        x_pos=min(x_pos,1.0);
        x_pos=max(x_pos,-1.0);
        y_pos=min(y_pos,1.0);
        y_pos=max(y_pos,-1.0);
        float r=screen_zoom*5;
        float a1=x_pos*M_PI/2;
        float a2=y_pos*M_PI/2;
        cx=ball1.position.x-ball1.co_z.x*r*(cos(a1)+cos(a2))+ball1.co_x.x*r*sin(a1)+ball1.co_y.x*r*sin(a2);
        cy=ball1.position.y-ball1.co_z.y*r*(cos(a1)+cos(a2))+ball1.co_x.y*r*sin(a1)+ball1.co_y.y*r*sin(a2);
        cz=ball1.position.z-ball1.co_z.z*r*(cos(a1)+cos(a2))+ball1.co_x.z*r*sin(a1)+ball1.co_y.z*r*sin(a2);
        lx=ball1.position.x;
        ly=ball1.position.y;
        lz=ball1.position.z;
    }
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (cx,cy,cz );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (lx,ly,lz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (ux, uy, uz);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    DMatrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0,0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    glm::mat4 DVP  = DMatrices.projection * DMatrices.view;
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    for(int i=0;i<Iland.size();i++)
        Iland[i].draw(VP);

    for(int i=0;i<BomFire.size();i++)
        BomFire[i].draw(VP);    
     for(int i=0;i<Mfire.size();i++)
        Mfire[i].draw(VP);
    for(int i=0;i<Pchute.size();i++)
        Pchute[i].draw(VP);
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<Enemy[i].size();j++)
            Enemy[i][j].draw(VP);
    }
    for(int i=0;i<Blt.size();i++)
        Blt[i].draw(VP);
      for(int i=0;i<Rng.size();i++)
        Rng[i].draw(VP);
    for(int i=0;i<Vlc.size();i++)
        Vlc[i].draw(VP);
    for(int i=0;i<F.size();i++)
        F[i].draw(VP);
    getnext();
    Check IM = Check(px,2,pz);
    IM.draw(VP);
    float Y = ball1.position.y+4;
    Dash D=Dash(-3.8,-3.8,0,CurrFuel*0.02,Y/20,CurrHealth*0.02);
    D.draw(DVP);
    Compass CP=Compass(-3,3,0,ball1.rotationy);
    CP.draw(DVP);
    int z=score/100;
   int x=score%100/10;
    int y=score%10;
    for(int i=0;i<7;i++)
        if(digDisplay[z][i]=='1')
            Hund[i].draw(DVP);
    for(int i=0;i<7;i++)
        if(digDisplay[x][i]=='1')
            Ten[i].draw(DVP);
    for(int i=0;i<7;i++)
        if(digDisplay[y][i]=='1')
            Unit[i].draw(DVP);
    Meter SPD=Meter(2.5,-2.9,0,100*sz);
    SPD.draw(DVP);
     ball1.draw(VP);
    
}

void FireBullet(int x)
{
    for(int i=0;i<Enemy[x].size();i++)
    {
        if(rand()%3)
            continue;
        float a=Enemy[x][i].position.x,b=Enemy[x][i].position.y,c=Enemy[x][i].position.z;
        float x=ball1.position.x,y=ball1.position.y,z=ball1.position.z;
        float D=sqrt(pow(a-x,2)+pow(b-y,2)+pow(c-z,2));
        float sx=(x-a)/D,sy=(y-b)/D,sz=(z-c)/D;
        Blt.push_back(Bullet(a,b,c,sx,sy,sz));
    }
}

void tick_input(GLFWwindow *window) {
    int left = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int cclr = glfwGetKey(window, GLFW_KEY_R);
    int clr = glfwGetKey(window, GLFW_KEY_E);
    int up = glfwGetKey(window,GLFW_KEY_SPACE);
    int down = glfwGetKey(window,GLFW_KEY_DOWN);
    int fwd  = glfwGetKey(window,GLFW_KEY_W);
    int bck  = glfwGetKey(window,GLFW_KEY_S);
    int bmb  = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
    int msi  = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    int ptcp  = glfwGetKey(window, GLFW_KEY_Z);
    int ptcn  = glfwGetKey(window, GLFW_KEY_X);
    int brr   = glfwGetKey(window, GLFW_KEY_J);
    int cv    = glfwGetKey(window, GLFW_KEY_V);
    glfwGetCursorPos(window,&x_pos,&y_pos);
    viewdiff--;
    if(cv && viewdiff<=0)
    {
        viewdiff=30;
        view++;
        view%=5;
    }
    if(brr)
    {
        broll=1;
        prx=ball1.rotationx;
    }
    if(ptcp)
    {
        ball1.rotationx+=1;
    }
    if(ptcn)
    {
        ball1.rotationx-=1;
    }
   
    if(left)
    {
        ball1.rotationz-=2;
        // ball1.rotationz=max(ball1.rotationz,-45.0f);
    }
    if(right)
    {
        ball1.rotationz+=2;
        // ball1.rotationz=min(ball1.rotationz,45.0f);
    }
    if(up)
        sy+=0.001f;
    if(down)
        sy-=0.001f;
    sy=min(sy,0.02f);
    sy=max(sy,-0.02f);
    sy=sy+gr;
    // sy=0;
    // if(up)
    //     sy=0.1;
    // if(down)
    //     sy=-0.1;
    ball1.position.y+=sy;
    if(fwd)
      sz-=0.1f;
    if(bck)
        sz+=0.1f;
    sz=max(sz,-0.9f);
    sz=min(sz,0.9f);
    ball1.position.x+=sz*ball1.co_z.x;
    ball1.position.y+=sz*ball1.co_z.y;
    ball1.position.z+=sz*ball1.co_z.z;
    if(cclr)
        ball1.rotationy+=1;
    if(clr)
        ball1.rotationy-=1;
    if(bmb)
    {
        if(curr>prv+20)
        {
            BomFire.push_back(Bomb(ball1.position.x,ball1.position.y,ball1.position.z));
            prv=curr;
        }
    }
    if(msi)
    {
        if(curr>mpr+20)
        {
            Mfire.push_back(Missile(ball1.position.x,ball1.position.y,ball1.position.z,ball1.co_z.x,ball1.co_z.y,ball1.co_z.z));
            mpr=curr;
        }
    }
    if(curr>fire+100)
    {
       FireBullet(cpoint);
       fire=curr;
    }
}

void tick_elements() {
    ball1.tick();
    for(int i=0;i<BomFire.size();i++)
        BomFire[i].tick();
    for(int i=0;i<Mfire.size();i++)
        Mfire[i].tick();
    for(int i=0;i<Pchute.size();i++)
        Pchute[i].tick();
    for(int i=0;i<Blt.size();i++)
        Blt[i].tick();
    if(sz>0)
        sz=sz-fric;
    else
        sz=sz+fric;
    // camera_rotation_angle += 1;
}
void CalScore()
{
    vector<pair<float,float> > seg;
    seg.push_back(mp(0,0));
    seg.push_back(mp(0.3,0));
    seg.push_back(mp(0,0.01));
    seg.push_back(mp(0.3,0.01));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));    
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
    seg.push_back(mp(0.3,0));
    seg.push_back(mp(0.31,0));
    seg.push_back(mp(0.3,0.21));
    seg.push_back(mp(0.31,0.21));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
    seg.push_back(mp(0.3,0.2));
    seg.push_back(mp(0.31,0.2));
    seg.push_back(mp(0.3,0.41));
    seg.push_back(mp(0.31,0.41));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.4));
    seg.push_back(mp(0.3,0.4));
    seg.push_back(mp(0,0.41));
    seg.push_back(mp(0.3,0.41));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.2));
    seg.push_back(mp(0.01,0.2));
    seg.push_back(mp(0,0.4));
    seg.push_back(mp(0.01,0.4));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0));
    seg.push_back(mp(0.01,0));
    seg.push_back(mp(0,0.21));
    seg.push_back(mp(0.01,0.21));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.2));
    seg.push_back(mp(0.3,0.2));
    seg.push_back(mp(0,0.21));
    seg.push_back(mp(0.3,0.21));
    Hund.push_back(Rect(seg,0+2.1,3.2,COLOR_BLACK,0.0f));
    Ten.push_back(Rect(seg,0+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,0+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other glleft, right, bottom, top, 0.1f, 500.0f function and shaders */
    // Create the models

    ball1       = Ball(0, 0, -10, COLOR_RED);
    sea         = Sea(0.0f,0.0f);
    // Create and compile our GLSL program from the shaders
    //Initialising Islands
    digDisplay[0]="1111110";
    digDisplay[1]="0110000";
    digDisplay[2]="1011011";
    digDisplay[3]="1111001";
    digDisplay[4]="0110101";
    digDisplay[5]="1101101";
    digDisplay[6]="1101111";
    digDisplay[7]="0111001";
    digDisplay[8]="1111111";
    digDisplay[9]="1111101";
    for(int i=0;i<100;i++)
    {
        Iland.push_back(Island(-250+rand()%500,-4,-4-rand()%500));
    }
    for(int i=0;i<10;i++)
    {
        int x=-250+rand()%500;
        cp.push_back(make_pair(x+9,-i*60));
        for(int j=0;j<6;j++)
        {
            Enemy[i].push_back(Cannon(x+j*3,-4,-i*60));
        }
    }
    for(int i=0;i<20;i++)
    {
        Rng.push_back(Ring(-250+rand()%500,10,-5-rand()%500));
    }
    for(int i=0;i<20;i++)
    {
        F.push_back(Fuel(-250+rand()%500,8,-5-rand()%500));
    }
    for(int i=0;i<5;i++)
    {
        Vlc.push_back(Volcano(-250+rand()%500,-4,-5-rand()%500));
    }
    for(int i=0;i<50;i++)
        Pchute.push_back(Para(-250+rand()%500,6+rand()%50,-5-rand()%500));
    
    // Pchute.push_back(Para(0,6,-12));
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_SKY.r / 256.0, COLOR_SKY.g / 256.0, COLOR_SKY.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

bounding_box_t get_bounding_box_bomb(Bomb B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.z=B.position.z;
    a.dx=0.6;
    a.dy=0.6;
    a.dz=0.6;
    return a;
}

bounding_box_t get_bounding_box_bullet(Bullet B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.z=B.position.z;
    a.dx=0.6;
    a.dy=0.6;
    a.dz=0.6;
    return a;
}

bounding_box_t get_bounding_box_missile(Missile B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.z=B.position.z;
    a.dx=0.6;
    a.dy=0.6;
    a.dz=0.6;
    return a;
}

bounding_box_t get_bounding_box_fuel(Fuel B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.z=B.position.z;
    a.dx=1;
    a.dy=1;
    a.dz=1;
    return a;
}

bounding_box_t get_bounding_box_par(Para P)
{
    bounding_box_t a;
    a.x=P.position.x;
    a.y=P.position.y;
    a.z=P.position.z;
    a.dy=1.2;
    a.dx=2;
    a.dz=2;
    return a;
}

bounding_box_t get_bounding_box_plane(Ball B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.z=B.position.z;
    a.dx=2;
    a.dy=2;
    a.dz=1;
    return a;
}

bounding_box_t get_bounding_box_cannon(Cannon C)
{
    bounding_box_t a;
    a.x=C.position.x;
    a.y=C.position.y;
    a.z=C.position.z;
    a.dx=6;
    a.dz=6;
    a.dy=4;
    return a;
}

void clearDeadwood()
{  
    int n=Pchute.size();
    int i=0;
    while(i<n)
    {
        if(Pchute[i].position.y<=-10)
        {
            Pchute.erase(Pchute.begin()+i);
            n--;
            continue;
        }
        int j=0;
        int m=BomFire.size();
        bounding_box_t a=get_bounding_box_par(Pchute[i]);
        while(j<m)
        {
            if(BomFire[j].position.y<=-10)
            {
                BomFire.erase(BomFire.begin()+j);
                m--;
                continue;
            }
            bounding_box_t b=get_bounding_box_bomb(BomFire[j]);
            if(detect_collision(a,b))
            {
                Pchute.erase(Pchute.begin()+i);
                n--;
                BomFire.erase(BomFire.begin()+j);
                m--;
                score+=20;
                break;
            }
            j++;
        }
        i++;
    }
    for(int i=0;i<Pchute.size();i++)
    {
        bounding_box_t a=get_bounding_box_par(Pchute[i]);
        for(int j=0;j<Mfire.size();j++)
        {
            bounding_box_t b=get_bounding_box_missile(Mfire[j]);
            if(detect_collision(a,b))
            {
                score+=20;
                Pchute.erase(Pchute.begin()+i);
                Mfire.erase(Mfire.begin()+j);
                i--;
                break;
            }
        }
    }
    while(Enemy[cpoint].size()==0)
    {
        score+=100;
        cpoint++;
    }
    for(int i=0;i<Enemy[cpoint].size();i++)
    {
        bounding_box_t a=get_bounding_box_cannon(Enemy[cpoint][i]);
        for(int j=0;j<BomFire.size();j++)
        {
            bounding_box_t b=get_bounding_box_bomb(BomFire[j]);
            if(detect_collision(a,b))
            {
                Enemy[cpoint].erase(Enemy[cpoint].begin()+i);
                i--;
                BomFire.erase(BomFire.begin()+j);
                break;
            }
        }
    }
     for(int i=0;i<Enemy[cpoint].size();i++)
    {
        bounding_box_t a=get_bounding_box_cannon(Enemy[cpoint][i]);
        for(int j=0;j<Mfire.size();j++)
        {
            bounding_box_t b=get_bounding_box_missile(Mfire[j]);
            if(detect_collision(a,b))
            {
                Enemy[cpoint].erase(Enemy[cpoint].begin()+i);
                i--;
                Mfire.erase(Mfire.begin()+j);
                break;
            }
        }
    }
    
}

void ColPlane()
{
    if(ball1.position.y<=-3.9)
    {
        quit(window);
    }
    bounding_box_t a = get_bounding_box_plane(ball1);
    for(int i=0;i<F.size();i++)
    {
        bounding_box_t b = get_bounding_box_fuel(F[i]);
        if(detect_collision(a,b))
        {
            CurrFuel+=2;
            F.erase(F.begin()+i);
            i--;
        }
    }
    for(int i=0;i<Blt.size();i++)
    {
        bounding_box_t b = get_bounding_box_bullet(Blt[i]);
        if(detect_collision(a,b))
        {
            CurrHealth-=2;
            Blt.erase(Blt.begin()+i);
            i--;
        }
    }
    for(int i=0;i<Rng.size();i++)
    {
        float x1=Rng[i].position.x;
        float y1=Rng[i].position.y;
        float z1=Rng[i].position.z;   
        float x2=ball1.position.x;
        float y2=ball1.position.y;
        float z2=ball1.position.z;
        float D = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        if(D<=2.3 && abs(z1-z2)<=0.2)
        {
            
            Rng.erase(Rng.begin()+i);
            i--;
            score+=50;
        }
    }
    for(int i=0;i<Vlc.size();i++)
    {
        float x1=Vlc[i].position.x;
        float y1=Vlc[i].position.y;
        float z1=Vlc[i].position.z;   
        float x2=ball1.position.x;
        float y2=ball1.position.y;
        float z2=ball1.position.z;
        float D = sqrt(pow(x1-x2,2)+pow(z1-z2,2));
        if(D<=7 && abs(y1-y2)<=10)
        {
            quit(window);
        }
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;
    float rx=0;
    window = initGLFW(width, height);

    initGL (window, width, height);
            CalScore();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            curr++;
            if(broll)
            {
                ball1.rotationx+=2;
                if(ball1.rotationx>=prx+350)
                    broll=0;
            }
            if(curr>sp+60)
            {
                sp=curr;
                score++;
            }
            // OpenGL Draw commands
            draw();
            clearDeadwood();
            ColPlane();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.dx + b.dx)) &&
           (abs(a.y - b.y) * 2 < (a.dy + b.dy)) && 
            (abs(a.z - b.z) * 2 < (a.dz + b.dz));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f,0.1f,500.0f);
    DMatrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
