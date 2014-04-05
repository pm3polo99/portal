#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "obj.h"
#include "log.h"

extern double ** oval;
extern int xres;
extern int yres;
extern int zres;
int objcnt = 0;
int portalcnt = 0;

struct portal * plist[2]; // ptr to a portal object. 2 max.
int plast; // last created portal - the other is the one to modify
struct obj ** olist;
#ifndef _SHAPES_H
#define _SHAPES_H

void destroyObj (int);
//struct obj* destroyObj (struct obj *);
void destroyPortal (struct portal *);
//struct obj* initObj (void);
void initObj (void);
void initPortal (void);
void drawOval(float **);

#endif // shapes.h
