

# PENNY
A single header library to create .ppm files

![screenshot](test.jpg)

# Functions
- int penny_init(int w, int h);
- void penny_color(color c);
- void penny_point(int x, int y);
- void penny_line(int x0, int y0, int x1, int y1);
- void penny_rect(int x, int y, int w, int h);
- void penny_fillrect(int x, int y, int w, int h);
- void penny_circle(int x, int y, int r);
- void penny_fillcircle(int x, int y, int r);
- int penny_save(char *file);
- void penny_close();
- char *penny_error();

## Notes
- penny_init() and penny_save() returns -1 on errors, you can check the error type calling penny_error()
Example: if ( penny_init(800,600)<0 ) { printf("%s\n",penny_error() ); };
- penny_color() set the current drawing color.
Available colors macro are : WHITE, SILVER,GRAY, BLACK, RED, MAROON, YELLOW, OLIVE, LIME, GREEN, AQUA, TEAL, BLUE, NAVY, FUCHSIA and PURPLE.
- you have to #define PENNY only once before an #include "penny.h" in your code 
- remember to call penny_close() when done to free internal allocated resources
