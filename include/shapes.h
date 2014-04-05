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
extern int objcnt;
extern int portalcnt;

struct portal * p1;
struct obj ** objlist;
#ifndef _SHAPES_H
#define _SHAPES_H

void destroyObj (int);
//struct obj* destroyObj (struct obj *);
struct portal* destroyPortal (struct portal *);
//struct obj* initObj (void);
void initObj (void);
struct portal* initPortal (void);
void drawOval(float **);

#endif // shapes.h
