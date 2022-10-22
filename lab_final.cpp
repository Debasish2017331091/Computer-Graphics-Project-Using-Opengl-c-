#include<bits/stdc++.h>
#include<graphics.h>
using namespace std;

int window_w=1000, window_h=800 ;
struct PT   ///Point Stracture
{
    double x,y;
    PT()
    {
    }
    PT(double a,double b)
    {
        x=a;
        y=b;
    }
};

PT convert_pixel(PT p)///Point convert with respect to axis
{
    p.x+=(window_w/2);
    p.y=-p.y;
    p.y+=(window_h/2);
    return p;
}

void draw_pixel(PT p,int color) ///Pixel filling with color
{
    p=convert_pixel(p);
    putpixel( (int)(p.x+0.5), (int)(p.y+0.5), color );
}
/*********************Circle Drawing(MID POINT)**********************************************/
void drawCirclePoint(PT p,int color)
{
    draw_pixel(PT(p.x,p.y),color);
    draw_pixel(PT(p.x,-p.y),color);
    draw_pixel(PT(p.y,-p.x),color);
    draw_pixel(PT(-p.y,-p.x),color);
    draw_pixel(PT(-p.x,-p.y),color);
    draw_pixel(PT(-p.x,p.y),color);
    draw_pixel(PT(-p.y,p.x),color);
    draw_pixel(PT(p.y,p.x),color);
}
void circle_draw(int x,int y,int radius) ///Midpoint circle drawing algorithm
{
    int xi=0,yi=radius;
    int d=1-radius;
    while(xi<=yi)
    {
        //drawCirclePoint(PT(xi,yi),YELLOW);
        PT p=PT(xi,yi);
        int color=YELLOW;
        draw_pixel(PT(p.x+x,p.y+y),color);
        draw_pixel(PT(p.x+x,-p.y+y),color);
        draw_pixel(PT(p.y+x,-p.x+y),color);
        draw_pixel(PT(-p.y+x,-p.x+y),color);
        draw_pixel(PT(-p.x+x,-p.y+y),color);
        draw_pixel(PT(-p.x+x,p.y+y),color);
        draw_pixel(PT(-p.y+x,p.x+y),color);
        draw_pixel(PT(p.y+x,p.x+y),color);
        if(d<0)
        {
            d+=(2*xi+3);
        }
        else
        {
            d+=(2*(xi-yi)+5);
            yi--;
        }
        xi++;
    }
}
/**************************************************************************************/
/*************************Boundary FILLING ********************************************/
void Boundary_Filling(PT p,int color,int boundary_color)
{
    PT p1=convert_pixel(p);
    int current_color=getpixel(p1.x,p1.y);
    if(current_color==boundary_color||current_color==color)
    {
        return;
    }
    draw_pixel(p,color);
    Boundary_Filling(PT(p.x,p.y+1), color, boundary_color);
    Boundary_Filling(PT(p.x,p.y-1), color, boundary_color);
    Boundary_Filling(PT(p.x+1,p.y), color, boundary_color);
    Boundary_Filling(PT(p.x-1,p.y), color, boundary_color);
}
/**************************************************************************************/
/************************* circle Object **********************************************/
class CIRCLE
{

public:
    int x, y, radius,s/**speed**/,d/**density**/;
    bool f=false;
    CIRCLE(int a,int b,int r)
    {
        x=a;
        y=b;
        radius=r;
        circle_draw(a,b,r);
        circle_draw(a,b,r-1);
        circle_draw(a,b,r-2);
        s=5;
        d=2;
    }
    void move_right()
    {
        if(x+s+radius<=500){
            cleardevice();
            x=x+s;
            y=y;
            for(int i=0;i<d;i++){
                circle_draw(x,y,radius-i);
            }
        }
        /*for(int i=0; (x+s+radius)<500; i+=s)
        {
            cleardevice();
            x=x+s;
            y=y;
            circle_draw(x,y,radius);
            circle_draw(x,y,radius-1);
            circle_draw(x,y,radius-2);
        }*/
    }
    void move_left(){
        if( x-s-radius >= -500 ){
            cleardevice();
            x=x-s;
            y=y;
            for(int i=0;i<d;i++){
                circle_draw(x,y,radius-i);
            }
        }
    }

    void move_up()
    {
        if(y+s+radius<=400){
            cleardevice();
            x=x;
            y=y+s;
            for(int i=0;i<d;i++){
                circle_draw(x,y,radius-i);
            }
        }
    }
    void move_down()
    {
        if( y-s-radius >= -400 ){
            cleardevice();
            x=x;
            y=y-s;
            for(int i=0;i<d;i++){
                circle_draw(x,y,radius-i);
            }
        }
    }
    void circle_fill(PT p){
        if( (p.x<(x+radius)) && ((p.x>x-radius)) && (p.y<(y+radius)) && (p.y>(y-radius)) ){
            Boundary_Filling(PT(x,y),WHITE,YELLOW);
        }
    }
};
/**************************************************************************************/
int main()
{
    initwindow(window_w,window_h);

    //draw_axis();
    POINT CursorPosition;
    CIRCLE a=CIRCLE(0,0,80);
    int m,n;
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,m,n);
            //cout << m << " " << n << endl;
            PT p(m-500 ,400-n);
            //cout << p.x << " " << p.y << endl;
            a.circle_fill(p);
            cout << "GAME OVER" << endl;
            //delay(1000);
            return 0;
        }
        if(GetAsyncKeyState(VK_RIGHT)){
            //cout << "Right Button pressed" << endl;
            delay(10);
            a.move_right();
        }else if (GetAsyncKeyState(VK_LEFT)){
            delay(10);
            a.move_left();
            //cout << "Left Button pressed" << endl;
        }else if (GetAsyncKeyState(VK_UP)){
            delay(10);
            a.move_up();
            //cout << "Up Button pressed" << endl;
        }else if (GetAsyncKeyState(VK_DOWN)){
            delay(10);
            a.move_down();
            //cout << "Down Button pressed" << endl;
        }else if(GetAsyncKeyState(VK_ESCAPE)){
            return 0;
        }
    }
    return 0;
}
