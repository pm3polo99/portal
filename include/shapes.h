#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "obj.h"

extern double ** oval;
extern int xres;
extern int yres;
extern int zres;
extern int objcnt;
extern int portalcnt;

#ifndef _SHAPES_H
#define _SHAPES_H

void destroyObj (obj *);
void destroyPortal (portal *);
void initWall (obj *);
void initPortal (portal *);
void createOval(void);

#endif // shapes.h
