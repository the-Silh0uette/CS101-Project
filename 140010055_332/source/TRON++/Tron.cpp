#include <allegro.h>
#include <iostream>

#define W 1000 //width of screen
#define H 675 //height of screen

using namespace std;
//r1 and r2 denotes the variable radii of the two players.
int  r1t=2.5,r2t=2.5,col1=makecol(0,0,204),col2=makecol(204,0,0);


//x1t,x2t,y1t,y2t denotes the initial positions of the players
int x2t = 10;
int y2t = 10;
int x1t = W-10;
int y1t = H-10;

//d1t,d2t denote the directions of motion of the players respectively
int d1t=0,d2t=1;

//w1t, w2t denote the number of wins of the players respectively
int w1t=0,w2t=0;

//timt denotes the timter for the powerups
int timt=0;

//x, y denote the positions of the powerups
int xt=W/2,yt=H/2;

void d2tdir(int P) // to control player 2
{
    //if condition for normal movement
    //else condition for movement at boundaries.
     switch (P)
     {
         case 0:
         {
            if(y2t>0)
                --y2t;
            else
                y2t=H;
            break;
         }
         case 1:
         {
            if(y2t<H)
                ++y2t;
            else
                y2t=0;
            break;
         }
         case 2:
         {
            if(x2t<W)
                ++x2t;
            else
                x2t=0;
            break;
         }
         case 3:
         {
            if(x2t>0)
                --x2t;
            else
                x2t=W;
            break;
         }
     }
}
void d1tdir(int P) // to control player 1
{
    switch (P)
     {
         case 0:
         {
            if(y1t>0)
                --y1t;
            else
                y1t=H;
            break;
         }
         case 1:
         {
            if(y1t<H)
                ++y1t;
            else
                y1t=0;
            break;
         }
         case 2:
         {
            if(x1t<W)
                ++x1t;
            else
                x1t=0;
            break;
         }
         case 3:
         {
            if(x1t>0)
                --x1t;
            else
                x1t=W;
            break;
         }
         //default: {break;   }
     }
}
void powerupt(BITMAP *buffer) // to create bonus pack
{
    //when timter hits 1000, a new bonus pack appears in a random position in the window.
    if(++timt%1000==0||timt==1)
    {
        //removing existing bonus pack and creating a new one.
        rectfill(buffer, xt, yt,xt+10,yt+10,makecol(0,0,0));
        //updating the position of bonus pack with new random coordinates.
        xt=(rand()%(W-100))+50; yt=(rand()%(H-100))+50;
        rectfill(buffer, xt, yt,xt+10,yt+10,makecol(255,255,0));
    }
}
//to check if the player reaches a power up
int checkpu(BITMAP *buffer,int p,int x,int y,int r)
{
    int col;
    //matching direction with colour of power up
    if(p==0)
    {
        col=getpixel(buffer,x,y-r-1);
        if((getr(col)==255&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==1)
    {
        col=getpixel(buffer,x,y+r+1);
        if((getr(col)==255&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==2)
    {
        col=getpixel(buffer,x+r+1,y);
        if((getr(col)==255&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==3)
    {
        col=getpixel(buffer,x-r-1,y);
        if((getr(col)==255&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    //return 0 if no power up is present in the immediate next pixel.
    else return 0;
}

// to check collisiont of the player with opponent or self.
int collisiont(BITMAP* buffer,int p,int x,int y,int r)
{
    //col stores the rgb values of the colour present in the next pixel.
    //getr, getg, getb extracts the r,g,b values of the colour present in the next pixel.
    int col;
    if(p==0)
    {
        col=getpixel(buffer,x,y-r-1);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
            return 1;
    }
    if(p==1)
    {
        col=getpixel(buffer,x,y+r+1);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
            return 1;

    }
    if(p==2)
    {
        col=getpixel(buffer,x+r+1,y);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
            return 1;

    }
    if(p==3)
    {
        col=getpixel(buffer,x-r-1,y);
        if((getr(col)==204&&getg(col)==0&&getb(col)==0)||getr(col)==0&&getg(col)==204&&getb(col)==204)
            return 1;

    }
    //return 0 if no collisiont occurs in the nextpixel.
    else return 0;
}

//displaying the path of the player.
void disp(BITMAP* buffer,int p1,int p2)
{

    circlefill( buffer, x1t, y1t,r1t, makecol(0,204,204));
    circlefill( buffer, x2t, y2t,r2t, makecol(204,0,0));
    blit(buffer,screen,0,0,0,0,W,H);
    release_screen();
    //after each display, it rests for 0.0005 seconds.
    rest(5);

}

void startTron(BITMAP *buffer,FONT *font1)
{
    int p1,p2;
    start:
    while ( !key[KEY_ESC] )
        {

        clear_keybuf();

        acquire_screen();


        //direction is updated and stored in a variable to provide for
        //continuous movement
        if (key[KEY_UP]&&d1t!=1)
        {
            d1tdir(d1t);d1t=0;
        }
        else if (key[KEY_DOWN]&&d1t!=0)
        {
           d1tdir(d1t);d1t=1;
        }
        else if (key[KEY_RIGHT]&&d1t!=3)
        {
           d1tdir(d1t);d1t=2;
        }
        else if (key[KEY_LEFT]&&d1t!=2)
        {
           d1tdir(d1t);d1t=3;
        }
        else
            d1tdir(d1t);
        if (key[KEY_W]&&d2t!=1)
        {
            d2tdir(d2t);d2t=0;
        }
        else if (key[KEY_S]&&d2t!=0)
        {
            d2tdir(d2t);d2t=1;
        }
        else if (key[KEY_D]&&d2t!=3)
        {
            d2tdir(d2t);d2t=2;
        }
        else if (key[KEY_A]&&d2t!=2)
        {
            d2tdir(d2t);d2t=3;
        }
        else
            d2tdir(d2t);
        //creating powerup happens here.
        powerupt(buffer);
        if(checkpu(buffer,d1t,x1t,y1t,r1t)==1)
        {
            //whenever power up is availiable, timter sets to 999
            //so that when the function is called again, its value becomes
            //1000 and thus a new power up is created.
            r2t+=1;
            timt=999;
            powerupt(buffer);
        }
        if(checkpu(buffer,d2t,x2t,y2t,r2t)==1)
        {
            r1t+=1;
            timt=999;
            powerupt(buffer);
        }
        //if both players collide together, the round reuslts in a draw.
        if(collisiont(buffer,d1t,x1t,y1t,r1t)&&collisiont(buffer,d2t,x2t,y2t,r2t))
        {
            clear_bitmap(buffer);
            textout_centre_ex(buffer,font,"This round is a draw",W/2,H/2,makecol(0,255,0),-1);
            rest(2000);
            x2t = W-10,y2t = 10,x1t = 10,y1t = H-10,d1t=0,d2t=1,r1t=r2t=2.5;
        }
        if(collisiont(buffer,d1t,x1t,y1t,r1t))
        {
            //if collisiont happens, the win count of that particular player increases.
            //w1t and w2t stores the win count.
            w1t++;
            if(w1t>=2)
            {
                //if win count becomes more than 2, exit screen appears.
                w1t=0,w2t=0;
                d1t=d2t=-1;
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
                acquire_screen();
                textout_centre_ex(buffer,font,"Player 1 wins the round",W/2,H/2,makecol(0,200,0),-1);
                release_screen();
               rest(1000);
                blit(buffer,screen,0,0,0,0,W,H);
                x2t = W-10,y2t = 10,x1t = 10,y1t = H-10,d1t=0,d2t=1,r1t=r2t=2.5;;
                //rest(500);

            }

        }
        if(collisiont(buffer,d2t,x2t,y2t,r2t))
        {
            w2t++;
            if(w2t>=2)
            {
                w2t=0,w1t=0;
                d1t=d2t=-1;
                clear_bitmap(buffer);
                textout_centre_ex(buffer,font1,"Player 2 wins the game",W/2,H/2,makecol(204,0,0),-1);
                textout_centre_ex(buffer,font,"Press ESC to exit",W/2,0.75*H,makecol(204,0,0),-1);
                rest(1000);
                blit(buffer,screen,0,0,0,0,W,H);
                if(key[KEY_ESC])
                    return;

            }
            else
            {
                clear_bitmap(buffer);

                textout_centre_ex(buffer,font,"Player 2 wins the round",W/2,H/2,makecol(0,200,0),-1);
                blit(buffer,screen,0,0,0,0,W,H);
                rest(1000);
                //clear_bitmap(buffer);
                x2t = W-10,y2t = 10,x1t = 10,y1t = H-10,d1t=0,d2t=1,r1t=r2t=2.5;

                //startTron(buffer,Sprite1,Sprite2);
            }


        }


        //after updation of coordinates and checking for powerups
        //and collision, if there is no obstruction, disp() is called.

        disp(buffer,p1,p2);



    }
}




