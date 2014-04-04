#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "obj.h"

extern double ** oval;
extern int xres;
extern int yres;
#ifndef _ZRES
#define _ZRES
int zres = 1;
#else
extern int zres;
#endif

#ifndef _SHAPES_H
#define _SHAPES_H

void initWall (wall *);
void createOval(void);

#endif // shapes.h
