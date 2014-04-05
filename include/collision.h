#pragma once
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "obj.h"
#include "const.h"
#include "shapes.h"


#ifndef _COLLISION_H
#define _COLLISION_H

int px (int *);
int py (int *);
int pz (int *);
int nx (int *);
int ny (int *);
int nz (int *);
int collide(int *, int *);

#endif /* collision.h */
