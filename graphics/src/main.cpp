#define BUILD_ALL_TARGETS remove("../build/main.o");remove("../build/glad.o");
#define FGE_FAST_VSYNC
#define FGE_WINDOW_TITLE "PONG"

#include "FGE_window.h"
#include "FGE_shape.h"
#include <iostream>
#include "math.h"
#include "FGE_Color.h"


//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
using namespace FGE; 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    
    //Creating the window context
    FGE::Window wind= FGE::Window();
    
    //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
     /*Creating BLACKPINK tm xDDD*/
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(wind.GetWidth(),wind.GetHeight());

    //Specifying the necessary shapes
   // FGE::SArrow arrow{0,100,20,50,0};
    
    FGE::SCircle ball={0,0,10};
    FGE::SCircle ring1 ={0,0,5};
    FGE::SCircle ring2 ={0,0,110};

    FGE::SRect goal1={-350,0,40,100};
    FGE::SRect goal2={350,0,40,100};
    FGE::SRect player1={-360,0,5,50};
    FGE::SRect player2={360,0,5,50};
    FGE::SRect field1={-195,0,195,290};
    FGE::SRect field2={195,0,195,290};
    FGE_Color ball_color=FGE::white; 

    float BALL_VX=-0.8,BALL_VY=0; 
    bool p1Upressed=false,p1Dpressed=false,p2Upressed=false,p2Dpressed=false; 
    while(wind.IsRunning())
    {    
    bool p1U=false,p1D=false,p2U=false,p2D=false; 


        
        FGE_START_RENDER();
        goal1.DrawBorder(FGE::powderblue).UpdateShape();goal2.DrawBorder(FGE::lightgoldenrodyellow).UpdateShape();
        ring1.Draw(FGE::white);ring2.DrawBorder(FGE::white); field1.DrawBorder(FGE::white);field2.DrawBorder(FGE::white);
        ball.ShiftX(BALL_VX*wind.GetDeltaTime()).ShiftY(BALL_VY*wind.GetDeltaTime()).Draw(ball_color).DrawBorder().UpdateShape();
            
        if(ball.x+ball.r>player1.xm-player1.w2&&ball.x-ball.r<player1.xm+player1.w2 && 
        ball.y+ball.r>player1.ym-player1.h2&&ball.y-ball.r<player1.ym+player1.h2)
        {
            ball_color=FGE::lightblue;
            BALL_VY=(ball.y-player1.ym)/(player1.h2*6);
            BALL_VX=-BALL_VX;
            ball.x+=2;
        }

        if(ball.x+ball.r>player2.xm-player2.w2&&ball.x-ball.r<player2.xm+player2.w2 && 
        ball.y+ball.r>player2.ym-player2.h2&&ball.y-ball.r<player2.ym+player2.h2)
        {
            ball_color=FGE::lightgoldenrodyellow;
            BALL_VY=(ball.y-player2.ym)/(player2.h2*6);
            BALL_VX=-BALL_VX;
            ball.x-=2;
        }

        if(ball.y<-wind.GetHeight()/2)BALL_VY=-BALL_VY;
        if(ball.y>wind.GetHeight()/2)BALL_VY=-BALL_VY;
        if(ball.x<-wind.GetWidth()/2){BALL_VX=-BALL_VX;goal1.h2-=20;}
        if(ball.x>wind.GetWidth()/2){BALL_VX=-BALL_VX;goal2.h2-=20;}

        if(wind.KeyDown('w')&&!p1Upressed){p1U=true; p1Upressed=true;}
        if(wind.KeyDown('s')&&!p1Dpressed){p1D=true; p1Dpressed=true;}
        if(wind.KeyDown(SDLK_UP)&&!p2Upressed){p2U=true; p2Upressed=true;}
        if(wind.KeyDown(SDLK_DOWN)&&!p2Dpressed){p2D=true; p2Dpressed=true;}

        if(wind.KeyUp('w'))p1Upressed=false;
        if(wind.KeyUp('s'))p1Dpressed=false;
        if(wind.KeyUp(SDLK_UP))p2Upressed=false;
        if(wind.KeyUp(SDLK_DOWN))p2Dpressed=false;

        player1.ShiftY((p1U-p1D)*(float)wind.GetDeltaTime()*5);
        player2.ShiftY((p2U-p2D)*(float)wind.GetDeltaTime()*5);

        player1.Draw(FGE::powderblue).DrawBorder().UpdateShape();
        player2.Draw(FGE::lightgoldenrodyellow).DrawBorder().UpdateShape();

        if(goal1.h2<0)
        {
            std::cout<<"YELLOW won!!";
            break; 
        }
        if(goal2.h2<0)
        {
            std::cout<<"BLUE won!!";
            break; 
        }

        wind.Swap();
        wind.PollEvents();
    }

    FGE_PRIM_RENDER_DELETE();
    return 0;
}