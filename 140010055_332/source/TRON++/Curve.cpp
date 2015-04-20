#include <allegro.h>
#include <iostream>

#define W 1000 //width of screen
#define H 675 //height of screen

using namespace std;
const int  r=2.5,col1=makecol(0,0,204),col2=makecol(204,0,0);

//x1,x2,y1,y2 denotes coordinates
int x2 = 10;
int y2 = 10;
int x1 = W-10;
int y1 = H-10;

//p1 and p2 denotes direction
int p1=0,p2=1;

//w1 and w2 denotes win count
int w1=0,w2=0;

// to control player 2
void p2dir(int P)
{
     switch (P)
     {
         case 0:
         {
            if(y2>0)
                --y2;
            else
                y2=H;
            break;
         }
         case 1:
         {
            if(y2<H)
                ++y2;
            else
                y2=0;
            break;
         }
         case 2:
         {
            if(x2<W)
                ++x2;
            else
                x2=0;
            break;
         }
         case 3:
         {
            if(x2>0)
                --x2;
            else
                x2=W;
            break;
         }
     }
}

// to control player 1
void p1dir(int P)
{
    switch (P)
     {
         case 0:
         {
            if(y1>0)
                --y1;
            else
                y1=H;
            break;
         }
         case 1:
         {
            if(y1<H)
                ++y1;
            else
                y1=0;
            break;
         }
         case 2:
         {
            if(x1<W)
                ++x1;
            else
                x1=0;
            break;
         }
         case 3:
         {
            if(x1>0)
                --x1;
            else
                x1=W;
            break;
         }
     }
}

int collision(BITMAP* buffer,int p,int x,int y)
{
    int col;
    if(p==0)
    {
        col=getpixel(buffer,x,y-r-1);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    if(p==1)
    {
        col=getpixel(buffer,x,y+r+1);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    if(p==2)
    {
        col=getpixel(buffer,x+r+1,y);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    if(p==3)
    {
        col=getpixel(buffer,x-r-1,y);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    else return 0;
}

//display the curve
void dispc(BITMAP* buffer)
{
    circlefill( buffer, x1, y1,r, makecol(0,204,204));
    circlefill( buffer, x2, y2,r, makecol(204,0,0));
    blit(buffer,screen,0,0,0,0,W,H);
    release_screen();
    rest(10);
}

//execution of curve starts here
void startCurve(BITMAP *buffer,FONT *font1)
{

    while ( !key[KEY_ESC] )
        {

        clear_keybuf();

        acquire_screen();



        if (key[KEY_UP]&&p1!=0&&p1!=1)
        {
            p1dir(p1);
            p1=0;
        }
        else if (key[KEY_DOWN]&&p1!=1&&p1!=0)
        {   p1dir(p1);
            p1=1;
        }
        else if (key[KEY_RIGHT]&&p1!=2&&p1!=3)
        {
            p1dir(p1);
            p1=2;
        }
        else if (key[KEY_LEFT]&&p1!=3&&p1!=2)
        {   p1dir(p1);
            p1=3;
        }
        else
        {p1dir(p1);    }
        if (key[KEY_W]&&p2!=1&&p2!=0)
        {
            p2dir(p2);p2=0;
        }
        else if (key[KEY_S]&&p2!=0&&p2!=1)
        {
            p2dir(p2);p2=1;
        }
        else if (key[KEY_D]&&p2!=3&&p2!=2)
        {
            p2dir(p2);p2=2;
        }
        else if (key[KEY_A]&&p2!=2&&p2!=3)
        {
            p2dir(p2);p2=3;
        }
        else
            p2dir(p2);
        if(collision(buffer,p1,x1,y1)&&collision(buffer,p2,x2,y2))
        {
            clear_bitmap(buffer);
            textout_centre_ex(buffer,font,"This round is a draw",W/2,H/2,makecol(0,255,0),-1);
            rest(2000);
            x2 = W-10,y2 = 10,x1 = 10,y1 = H-10,p1=0,p2=1;
        }
        if(collision(buffer,p1,x1,y1))
        {
            w1++;
            if(w1>=2)
            {
                p1=p2=-1;
                clear_bitmap(buffer);
                textout_centre_ex(buffer,font1,"Player 1 wins the game",W/2,H/2,makecol(204,0,0),-1);
                textout_centre_ex(buffer,font,"Press ESC to exit",W/2,0.75*H,makecol(204,0,0),-1);
                blit(buffer,screen,0,0,0,0,W,H);
                rest(2000);
                if(key[KEY_ESC])
                    return;

            }
           else
            {
                clear_bitmap(buffer);
                textout_centre_ex(buffer,font,"Player 1 wins the round",W/2,H/2,makecol(0,255,0),-1);
                rest(1000);

                x2 = W-10,y2 = 10,x1 = 10,y1 = H-10,p1=0,p2=1;
                rest(500);
                //startCurve(buffer,Sprite1,Sprite2);
            }

        }
        if(collision(buffer,p2,x2,y2))
        {
            w2++;
            if(w2>=2)
            {
                p1=p2=-1;
                clear_bitmap(buffer);
                textout_centre_ex(buffer,font1,"Player 2 wins the game",W/2,H/2,makecol(204,0,0),-1);
                textout_centre_ex(buffer,font,"Press ESC to exit",W/2,0.75*H,makecol(204,0,0),-1);
                blit(buffer,screen,0,0,0,0,W,H);
                rest(2000);
                if(key[KEY_ESC])
                    return;
            }
            else
            {
                clear_bitmap(buffer);

                textout_centre_ex(buffer,font,"Player 2 wins the round",W/2,H/2,makecol(0,255,0),-1);
                blit(buffer,screen,0,0,0,0,W,H);
                rest(1000);
                x2 = W-10,y2 = 10,x1 = 10,y1 = H-10,p1=0,p2=1;

            }


        }


        //once updation is over, disp() is called.

        dispc(buffer);



    }
}



