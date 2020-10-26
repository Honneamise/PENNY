//interface
#ifndef PENNY_H
#define PENNY_H

//suppress crt warning on vs
#define _CRT_SECURE_NO_WARNINGS

//headers
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

//pixel color
typedef uint8_t color[3];

//penny image
typedef struct ppm
{
    int w;
    int h;
    color *data;

}ppm;

//defines
#define WHITE   (color){0xFF, 0xFF, 0xFF}
#define SILVER  (color){0xC0, 0xC0, 0xC0}
#define GRAY    (color){0x80, 0x80, 0x80}
#define BLACK   (color){0x00, 0x00, 0x00}
#define RED     (color){0xFF, 0x00, 0x00}
#define MAROON  (color){0x80, 0x00, 0x00}
#define YELLOW  (color){0xFF, 0xFF, 0x00}
#define OLIVE   (color){0x80, 0x80, 0x00}
#define LIME    (color){0x00, 0xFF, 0x00}
#define GREEN   (color){0x00, 0x80, 0x00}
#define AQUA    (color){0x00, 0xFF, 0xFF}
#define TEAL    (color){0x00, 0x80, 0x80}
#define BLUE    (color){0x00, 0x00, 0xFF}
#define NAVY    (color){0x00, 0x00, 0x80}
#define FUCHSIA (color){0xFF, 0x00, 0xFF}
#define PURPLE  (color){0x80, 0x00, 0x80}

#define _ERR_ALLOCATION     "[penny error] Allocation failed"
#define _ERR_FILE_NAME      "[penny error] File name is null"
#define _ERR_FILE_OPEN      "[penny error] Failed opening file"
#define _ERR_FILE_HEADER    "[penny error] Failed writing header to file"
#define _ERR_FILE_DATA      "[penny error] Failed writing data to file"

#define _SIGNATURE "#Generated by Penny lib (honneamise@hotmail.com)"

//globals
static ppm      _ppm = {0};
static color    _color = {0};
static char    *_error = NULL;

//utils
#define _min(a,b) (((a)<(b))?(a):(b))

#define _max(a,b) (((a)>(b))?(a):(b))

//functions
int penny_init(int w, int h);

void penny_color(color c);

void penny_point(int x, int y);

void penny_line(int x0, int y0, int x1, int y1);

void penny_rect(int x, int y, int w, int h);

void penny_fillrect(int x, int y, int w, int h);

void penny_circle(int x, int y, int r);

void penny_fillcircle(int x, int y, int r);

int penny_save(char *file);

void penny_close();

char *penny_error();

//implementation
#ifdef PENNY

/**********/
int penny_init(int w, int h)
{
    _ppm.data = calloc(w*h, sizeof(color));

    if (_ppm.data == NULL) { _error=_ERR_ALLOCATION; return -1;}
    else
    {
        _ppm.w = w;
        _ppm.h = h;

        for(int counter =0;counter<w*h;counter++)
        {
            _ppm.data[counter][0] = 0xFF;
            _ppm.data[counter][1] = 0xFF;
            _ppm.data[counter][2] = 0xFF;
        }
    }
    
    return 0;    
}

/**********/
void penny_color(color c)
{
    _color[0] = c[0];
    _color[1] = c[1];
    _color[2] = c[2];
}

/**********/
void penny_point(int x, int y)
{
    if(x<0 || x>=_ppm.w || y<0 || y>=_ppm.h){ return; }
    _ppm.data[_ppm.w*y + x][0] = _color[0]; 
    _ppm.data[_ppm.w*y + x][1] = _color[1]; 
    _ppm.data[_ppm.w*y + x][2] = _color[2]; 
}

/**********/
void penny_line(int x0, int y0, int x1, int y1)
{
    if(x0==x1)//v-line
    {
        int start = _min(y0,y1);
        int len = _max(y0,y1)-start;
        for(int i=0;i<=len;i++){ penny_point(x0, start+i);};
        return;
    }

    if(y0==y1)//h-line
    {
        int start = _min(x0,x1);
        int len = _max(x0,x1)-start;
        for(int i=0;i<=len;i++){ penny_point(start+i, y0);};
        return;
    }

    int dx = abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0);
    int sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;
 
    for(;;)
    {
        penny_point(x0, y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

/**********/
void penny_rect(int x, int y, int w, int h)
{
    penny_line(x,y,x+w,y);
    penny_line(x+w,y,x+w,y+h);
    penny_line(x+w,y+h,x,y+h);
    penny_line(x,y+h,x,y);
}

/**********/
void penny_fillrect(int x, int y, int w, int h)
{
    for(int i=0;i<=h;i++)
    {
        penny_line(x,y+i,x+w,y+i);
    }
}

/**********/
void penny_circle(int x, int y, int r)
{
	int offsetx = 0; 
    int offsety = r;
	int d = r-1;
	
    while (offsety >= offsetx) 
    {
        penny_point( x + offsetx, y + offsety);
        penny_point( x + offsety, y + offsetx);
        penny_point( x - offsetx, y + offsety);
        penny_point( x - offsety, y + offsetx);
        penny_point( x + offsetx, y - offsety);
        penny_point( x + offsety, y - offsetx);
        penny_point( x - offsetx, y - offsety);
        penny_point( x - offsety, y - offsetx);
	
        if (d >= 2*offsetx) 
        {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
	    else if (d < 2 * (r - offsety)) 
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else 
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

/**********/
void penny_fillcircle(int x, int y, int r)
{
	int offsetx = 0; 
    int offsety = r;
	int d = r-1;
	
    while (offsety >= offsetx) 
    {	
        penny_line( x - offsety, y + offsetx, x + offsety, y + offsetx);
        penny_line( x - offsetx, y + offsety, x + offsetx, y + offsety);
        penny_line( x - offsetx, y - offsety, x + offsetx, y - offsety);
        penny_line( x - offsety, y - offsetx, x + offsety, y - offsetx);
        
        if (d >= 2*offsetx) 
        {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (r - offsety)) 
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else 
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}


/**********/
int penny_save(char *file)
{
    if(file==NULL){ _error=_ERR_FILE_NAME; return -1; };

    FILE *fp = fopen(file,"wb");

    if(fp)
    {
        //header
        fprintf(fp, "P6\n%s\n%d\n%d\n255\n", _SIGNATURE, _ppm.w, _ppm.h);
        if(ferror(fp))
        {
            _error=_ERR_FILE_HEADER; 
            fclose(fp);
            return -1;
        }

        //data
        fwrite(_ppm.data, sizeof(color), _ppm.w*_ppm.h, fp);
        if(ferror(fp))
        {
            _error=_ERR_FILE_DATA; 
            fclose(fp);
            return -1;
        }

        fclose(fp);
        return 0;
    }
    else
    {
        _error=_ERR_FILE_OPEN; 
        return -1;
    }

}

/**********/
void penny_close()
{
    _ppm.w = 0;
    _ppm.h = 0;
    if(_ppm.data!=NULL){ free(_ppm.data); }; 
    _ppm.data = NULL;
}

/**********/
char *penny_error()
{
    return _error;
}

#endif

#endif
