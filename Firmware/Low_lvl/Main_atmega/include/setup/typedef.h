#pragma once

typedef  short ang_t;

typedef struct duo{
    short f;
    short s;    
}duo;

typedef struct coords{
    short x = 0;
    short y = 0;
} coords;


typedef struct vec{

    ang_t ang;
    short len;

    coords beg, end; 

} vec;

