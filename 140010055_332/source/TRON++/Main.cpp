#include <allegro.h>
#include <string>
#include <iostream>


#define W 1000 //width of screen
#define H 675  //height of screen
using namespace std;

volatile int closewindow=false;
int M;
//function to add the close button
void closeButtonCallBack()
{
    closewindow=true;
}
int getMouseInfo()
// function to read in the mouse inputs
{
    int stat=0;

    if(mouse_b & 1)
    // this means that when the right mouse button is clicked
    {
        stat=1;

        if(mouse_x<189&&mouse_x>129&&mouse_y<673&&mouse_y>615)
            M=0;
        else if(mouse_x<549&&mouse_x>489&&mouse_y<673&&mouse_y>615)
            M=1;
        else if(mouse_x<886&&mouse_x>826&&mouse_y<673&&mouse_y>615)
            M=2;
        else
            stat=0;

     }
     return stat;
}

//declaration of the three functions to start the three modes.

void startTron(BITMAP *buffer,FONT *font1);

void startSnake(BITMAP *buffer,FONT *font1);

void startCurve(BITMAP *buffer,FONT *font1);

int main()
{
    int mouse_x,mouse_y;
    char ch();
    //initializing allegro.
    allegro_init();
    set_window_title("~~~~TRON++~~~~");
    //enabling inputs from mouse and keyboard.
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, W,H , 0,0);
    //loading custom font.
    FONT *font1=load_font("tronfont.pcx",NULL,NULL);

    LOCK_FUNCTION(closeButtonCallBack);

    set_close_button_callback(closeButtonCallBack);
    //this calls the close button function which enables the user to close
    //the program even during its execution
    int counter=0;
    string word="TRON++";
    string draw="";
    BITMAP *buffer=create_bitmap(W,H);
    // buffer created which acts as a secondary screen
    //visible to only the creator

    BITMAP *img = load_bitmap( "menu.bmp", NULL);
    while(!closewindow)
    {
        //loop to create the starting screen of game.
        while(counter<word.length()+1)
        {
            draw+=word[counter];
            counter++;
            textout_centre_ex(buffer,font1,draw.c_str(),W/2,H/2,makecol(0,255,0),-1);

            if(!closewindow)
                rest(200);
            else
                rest(1000);
            blit(buffer,screen,0,0,0,0,W,H);
            clear_bitmap(buffer);
        }
        //this function writes the image to the buffer
        blit(img,buffer,0,0,0,0,W,H);rest(2000);
        clear_bitmap(screen);
        // the screen is cleared
        blit(buffer,screen,0,0,0,0,W,H);
        // once the buffer is created the blit writes from the buffer to the screen



        acquire_screen();                       //command toget a new screen
        draw_sprite( screen, buffer,0,0);       //draw sprite command installs images on
                                                //  the screen
        release_screen();
        show_mouse(buffer);
        if(key[KEY_ESC]) goto label; // to go to end of program
        while( !key[KEY_ESC])
        {

             acquire_screen();
             draw_sprite( screen, buffer, 0, 0);
             release_screen();

            if(getMouseInfo())
            break;
        }
        // ends the mouse input functionality


        show_mouse(NULL);

        rest(400);

        clear_bitmap(buffer);


        if(M==0)
        {
            img = load_bitmap( "Instructions Tron.bmp", NULL);
            blit(img,buffer,0,0,0,0,W,H);rest(2000);
            clear_bitmap(screen);
            blit(buffer,screen,0,0,0,0,W,H);
            rest(5000);
            clear_bitmap(buffer);
            startTron(buffer,font1);
            goto label;
        }
        if(M==1)
        {
            img = load_bitmap( "Instructions Curve.bmp", NULL);
            blit(img,buffer,0,0,0,0,W,H);
            clear_bitmap(screen);
            blit(buffer,screen,0,0,0,0,W,H);
            rest(5000);
            clear_bitmap(buffer);
            startCurve(buffer,font1);
            goto label;
        }
        if(M==2)
        {
            img = load_bitmap( "Instructions Snake.bmp", NULL);
            blit(img,buffer,0,0,0,0,W,H);
            clear_bitmap(screen);
            blit(buffer,screen,0,0,0,0,W,H);
            rest(5000);
            clear_bitmap(buffer);
            startSnake(buffer,font1);
            goto label;
        }

        acquire_screen();
        draw_sprite( screen, buffer, 0, 0);

        release_screen();

    }
    label:
        destroy_bitmap( buffer);
        destroy_bitmap( img);
        return 0;
}


END_OF_MAIN();



