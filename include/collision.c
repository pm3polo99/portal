#include "collision.h"

#ifndef _COLLISION_C
#define _COLLISION_C


/* make the args an array of 3 pts, the first arg being current position, 
 * second being desired position. 
 * then we get a direction and can tell if we need to check >= or <=.
 * function should return index number of object collision occured with, or special case
 * make sure to always pass 1 for z value, not 0
 * */

int collide(int *a, int *b)
{
	 // sanity checking
	 if (a == 000 || b == 000)
		  return -1; // bad args
	 if (b[0] < 1)
		  return -2; // x at 0
	 if (b[1] < 1)
		  return -3; // y at 0
	 if (b[2] < 1)
		  return -4; // z at 0
	 if (b[0] > xres)
		  return -5; // x at max
	 if (b[0] > yres)
		  return -6; // y at max
	 if (b[0] > zres)
		  return -7; // z at max

	 int vec[3] = {(b[0]-a[0]), (b[1]-a[1]), (b[2]-a[2])}; // vector
	 int result = 0;

	 /* below is a fairly basic algo to keep checking until there is no conflict
	  * may be optimizable
	  */
	 do
	 {
		  result = 0;
		  if (vec[0] > 0)
		  {
				result += px(&b[0]);
		  }
		  if (vec[1] > 0)
		  {
				result += py(&b[1]);
		  }
		  if (vec[2] > 0)
		  {
				result += pz(&b[2]);
		  }
		  if (vec[0] < 0)
		  {
				result += nx(&b[0]);
		  }
		  if (vec[1] < 0)
		  {
				result += ny(&b[1]);
		  }
		  if (vec[2] < 0)
		  {
				result += nz(&b[2]);
		  }
		  vec[0] = (b[0]-a[0]);
		  vec[1] = (b[1]-a[1]);
		  vec[2] = (b[2]-a[2]); // recalc. should eliminate unnecessary checks
	 }
	 while (result != 0);

	 return 0;
}

int nx (int * b)
{
	 int i = 0, y = 0, z = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (y < imgres)
		  {
				while (z < imgres)
				{
					 if (olist[i]->img[*b][y][z] == 1) // collision. on this planei
					 {
						  (*b)++;
						  Log("Collision with olist[%d] on x-axis!\n", i);
						  return i;
					 }
					 z++;
				}
				y++;
		  }
		  i++;
	 }
	 return 0;
}

int ny (int * b)
{
	 int i = 0, x = 0, z = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (x < imgres)
		  {
				while (z < imgres)
				{
					 if (olist[i]->img[x][*b][z] == 1) // collision. on this planei
					 {
						  (*b)++;
						  Log("Collision with olist[%d] on y-axis!\n", i);
						  return i;
					 }
					 z++;
				}
				x++;
		  }
		  i++;
	 }
	 return 0;
}

// check b on xy-plane. if any b on xy == 1, collision, else, no collision.
// maybe add in limits on xy to be within size of object and witihn size of person
int nz (int * b)
{
	 int i = 0, x = 0, y = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (x < imgres)
		  {
				while (y < imgres)
				{
					 if (olist[i]->img[x][y][*b] == 1) // collision. on this planei
					 {
						  (*b)++;
						  Log("Collision with olist[%d] on z-axis!\n", i);
						  return i;
					 }
					 y++;
				}
				x++;
		  }
		  i++;
	 }
	 return 0;
}


int px (int * b)
{
	 int i = 0, y = 0, z = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (y < imgres)
		  {
				while (z < imgres)
				{
					 if (olist[i]->img[*b][y][z] == 1) // collision. on this planei
					 {
						  (*b)--; // since in positive direction, decrement
						  Log("Collision with olist[%d] on x-axis!\n", i);
						  return i;
					 }
					 z++;
				}
				y++;
		  }
		  i++;
	 }
	 return 0;
}

int py (int * b)
{
	 int i = 0, x = 0, z = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (x < imgres)
		  {
				while (z < imgres)
				{
					 if (olist[i]->img[x][*b][z] == 1) // collision. on this planei
					 {
						  (*b)--; // since in positive direction, decrement
						  Log("Collision with olist[%d] on y-axis!\n", i);
						  return i;
					 }
					 z++;
				}
				x++;
		  }
		  i++;
	 }
	 return 0;
}

// check b on xy-plane. if any b on xy == 1, collision, else, no collision.
// maybe add in limits on xy to be within size of object and witihn size of person
int pz (int * b)
{
	 int i = 0, x = 0, y = 0;
	 while (i < objcnt) // check all objects
	 {
		  while (x < imgres)
		  {
				while (y < imgres)
				{
					 if (olist[i]->img[x][y][*b] == 1) // collision. on this planei
					 {
						  (*b)--; // since in positive direction, decrement
						  Log("Collision with olist[%d] on z-axis!\n", i);
						  return i;
					 }
					 y++;
				}
				x++;
		  }
		  i++;
	 }
	 return 0;
}

#endif /* collision.c */
