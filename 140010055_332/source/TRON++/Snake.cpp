#include <allegro.h>
#include <iostream>

#define W 1000 //width of screen
#define H 675 //height of screen

using namespace std;
//Radius of snakes is a constant r.
const int  r=2.5,col1=makecol(0,0,204),col2=makecol(204,0,0);

//x1s,y1s,x2s,y2s denotes coordinates of snakes
int x2s = 10,y2s = 10;
int x1s = W-10,y1s = H-10;

//d1s,d2s denotes the direction of the snakes
int d1s=0,d2s=1;
//w1s and w2s denotes the win count
int w1s=0,w2s=0;
int tims=0;
//xs and ys denotes position of bonus packs
int xs=W/2,ys=H/2;
//n is used for making the tail
//l1 and l2 denotes the length of snakes.
int n=0,l1=25,l2=25;

void d2sdir(int P) // to control player 2
{
     switch (P)
     {
         case 0:
         {
            if(y2s>0)
                --y2s;
            else
                y2s=H;
            break;
         }
         case 1:
         {
            if(y2s<H)
                ++y2s;
            else
                y2s=0;
            break;
         }
         case 2:
         {
            if(x2s<W)
                ++x2s;
            else
                x2s=0;
            break;
         }
         case 3:
         {
            if(x2s>0)
                --x2s;
            else
                x2s=W;
            break;
         }
     }
}
void d1sdir(int P) // to control player 1
{
    switch (P)
     {
         case 0:
         {
            if(y1s>0)
                --y1s;
            else
                y1s=H;
            break;
         }
         case 1:
         {
            if(y1s<H)
                ++y1s;
            else
                y1s=0;
            break;
         }
         case 2:
         {
            if(x1s<W)
                ++x1s;
            else
                x1s=0;
            break;
         }
         case 3:
         {
            if(x1s>0)
                --x1s;
            else
                x1s=W;
            break;
         }
     }
}

// to create bonus pack
void bonus(BITMAP *buffer)
{
    //timer updates in every iteration
    //tim=1 condition is for initial bonus pack
    if(++tims%1000==0||tims==1)
    {
        circlefill (buffer, xs, ys,5,makecol(0,0,0));
        xs=(rand()%(W-100))+50; ys=(rand()%(H-100))+50;
        circlefill (buffer, xs, ys,5,makecol(0,255,0));
    }
}

//check for bonus pack in new position
int checkbonus(BITMAP *buffer,int p,int x,int y)
{
    int col;
    if(p==0)
    {
        col=getpixel(buffer,x,y-r-1);
        if((getr(col)==0&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==1)
    {
        col=getpixel(buffer,x,y+r+1);
        if((getr(col)==0&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==2)
    {
        col=getpixel(buffer,x+r+1,y);
        if((getr(col)==0&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else if(p==3)
    {
        col=getpixel(buffer,x-r-1,y);
        if((getr(col)==0&&getg(col)==255&&getb(col)==0))
            return 1;
    }
    else return 0;
    //returns 0 if no bonus pack is found in new position
}

//collision function
//two cases for avoiding collision with oneself
int collisions(BITMAP* buffer,int player,int p,int x,int y)
{
    int col;
    if (player==1)
    {
        if(p==0)
        {
            col=getpixel(buffer,x,y-r-1);
            if((getr(col)==204&&getg(col)==0&&getb(col)==0))
            {
                return 1;
            }
        }
        else if(p==1)
        {
            col=getpixel(buffer,x,y+r+1);
            if((getr(col)==204&&getg(col)==0&&getb(col)==0))
            {
                return 1;
            }
        }
        else if(p==2)
        {
            col=getpixel(buffer,x+r+1,y);
            if((getr(col)==204&&getg(col)==0&&getb(col)==0))
            {
                return 1;
            }
        }
        else if(p==3)
        {
            col=getpixel(buffer,x-r-1,y);
            if((getr(col)==204&&getg(col)==0&&getb(col)==0))
            {
                return 1;
            }
        }
        else return 0;
    }

    if(player==2)
    {
        if(p==0)
        {
            col=getpixel(buffer,x,y-r-1);
            if(getr(col)==0&&getg(col)==204&&getb(col)==204)
            {
                return 1;
            }
        }
        else if(p==1)
        {
            col=getpixel(buffer,x,y+r+1);
            if(getr(col)==0&&getg(col)==204&&getb(col)==204)
            {
                return 1;
            }
        }
    else if(p==2)
    {
        col=getpixel(buffer,x+r+1,y);
        if(getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    else if(p==3)
    {
        col=getpixel(buffer,x-r-1,y);
        if(getr(col)==0&&getg(col)==204&&getb(col)==204)
        {
            return 1;
        }
    }
    else return 0;
    }

}

//to create black snake which follows around
//this function accounts for shedding skin
void tail(BITMAP *buffer)
{
    if(d1s==0)
        circlefill(buffer,x1s,y1s+l1,r,makecol(0,0,0));
    if(d1s==1)
        circlefill(buffer,x1s,y1s-l1,r,makecol(0,0,0));
    if(d1s==2)
        circlefill(buffer,x1s-l1,y1s,r,makecol(0,0,0));
    if(d1s==3)
        circlefill(buffer,x1s+l1,y1s,r,makecol(0,0,0));
    if(d2s==0)
        circlefill(buffer,x2s,y2s+l2,r,makecol(0,0,0));
    if(d2s==1)
        circlefill(buffer,x2s,y2s-l2,r,makecol(0,0,0));
    if(d2s==2)
        circlefill(buffer,x2s-l2,y2s,r,makecol(0,0,0));
    if(d2s==3)
        circlefill(buffer,x2s+l2,y2s,r,makecol(0,0,0));
    blit(buffer,screen,0,0,0,0,W,H);
}

//displaying the head of snake
void head(BITMAP* buffer,int d1s,int d2s)
{

    circlefill( buffer, x1s, y1s,r, makecol(0,204,204));
    circlefill( buffer, x2s, y2s,r, makecol(204,0,0));
    blit(buffer,screen,0,0,0,0,W,H);
    release_screen();
    rest(2);
}

//executes the snake mode

void startSnake(BITMAP *buffer,FONT *font1)
{

    while ( !key[KEY_ESC] )
        {

        clear_keybuf();

        acquire_screen();



        if (key[KEY_UP]&&d1s!=1)
        {
            d1sdir(d1s);d1s=0;
        }
        else if (key[KEY_DOWN]&&d1s!=0)
        {
           d1sdir(d1s);d1s=1;
        }
        else if (key[KEY_RIGHT]&&d1s!=3)
        {
           d1sdir(d1s);d1s=2;
        }
        else if (key[KEY_LEFT]&&d1s!=2)
        {
           d1sdir(d1s);d1s=3;
        }
        else
            d1sdir(d1s);
        if (key[KEY_W]&&d2s!=1)
        {
            d2sdir(d2s);d2s=0;
        }
        else if (key[KEY_S]&&d2s!=0)
        {
            d2sdir(d2s);d2s=1;
        }
        else if (key[KEY_D]&&d2s!=3)
        {
            d2sdir(d2s);d2s=2;
        }
        else if (key[KEY_A]&&d2s!=2)
        {
            d2sdir(d2s);d2s=3;
        }
        else
            d2sdir(d2s);
        //new position is now updated based on keypress
        //bonus pack is created here
        bonus(buffer);
        //bonus pack is checked for in the new position
        if(checkbonus(buffer,d1s,x1s,y1s))
        {
            l1+=15;
            tims=999;
            bonus(buffer);
        }
        if(checkbonus(buffer,d2s,x2s,y2s))
        {
            l2+=15;
            tims=999;
            bonus(buffer);
        }
        //collision of both leads to draw
        if(collisions(buffer,1,d1s,x1s,y1s)&&collisions(buffer,2,d2s,x2s,y2s))
        {
            clear_bitmap(buffer);
            textout_centre_ex(buffer,font,"This round is a draw",W/2,H/2,makecol(0,255,0),-1);
            rest(2000);
            x2s = W-10,y2s = 10,x1s = 10,y1s = H-10,d1s=0,d2s=1;
        }
        //collision of player 1
        if(collisions(buffer,1,d1s,x1s,y1s))
        {
            w1s++;
            if(w1s>=2)
            {
                w1s=0,w2s=0;
                d1s=d2s=-1;
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
                x2s = W-10,y2s = 10,x1s = 10,y1s = H-10,d1s=0,d2s=1;
                //rest(500);

            }

        }
        //collison of player 2
        if(collisions(buffer,2,d2s,x2s,y2s))
        {
            w2s++;
            if(w2s>=2)
            {
                w2s=0,w1s=0;
                d1s=d2s=-1;
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
                x2s = W-10,y2s = 10,x1s = 10,y1s = H-10,d1s=0,d2s=1;

                //startTron(buffer,Sprite1,Sprite2);
            }


        }

        //snake head is displayed once updation and checking is over.
       head(buffer,d1s,d2s);
       //for initial length of snake
        n++;
        if(n>25)
            tail(buffer);

    }
}




