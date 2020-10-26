#define PENNY
#include "penny.h"

int main(int argc, char **argv)
{
    if(penny_init(800,600)<0)
    { printf("%s\n",penny_error()); exit(-1); };

    penny_color(BLACK);
    penny_line(50,50,100,100);
    penny_line(50,100,100,50);
    
    penny_color(RED);
    penny_rect(150,50,100,50);

    penny_color(BLUE);
    penny_fillrect(300,50,100,50);

    penny_color(LIME);
    penny_circle(500,75,30);

    penny_color(TEAL);
    penny_fillcircle(600,75,29);

    penny_color(BLACK);
    for(int i=0;i<20;i++)
    {
        penny_line(0,i*50, i*50, 600);
    }

    if(penny_save("test.ppm")<0)
    { printf("%s\n",penny_error()); exit(-1); };
    
    penny_close();

    return 0;
}
