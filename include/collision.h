#pragma once
#include "objects.h"
#include "const.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


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
