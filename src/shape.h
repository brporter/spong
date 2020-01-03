#ifndef SHAPE_H
#define SHAPE_H

typedef struct Position
{
    int x;
    int y;
} Position;

typedef struct Rectangle
{
    Position pos;
    int w;
    int h;
} Rectangle;

#endif