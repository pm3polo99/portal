/* TO DO 
 * overload destroy to take no args to destroy all, one int to destroy one. void on all.
 */

#include "shapes.h"

void destroyPortal (int p)
{
	 Log("start of destroyPortal\n");
	 if (plist[p] == 000)
		  return;
	 int i = 0, j = 0;
	 plist[p]->isPortal = 0; // not a portal - yet
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				free(plist[p]->pos[i][j]);
				j++;
		  }
		  i++;
	 }
	 free(plist[p]->pos);
	 plist[p] = 000;
	 Log("end of destroyPortal\n");
	 return;
}

//struct obj * destroyObj (struct obj *o)
void destroyObj (int o)
{
	 Log("start of destroyObj\n");
	 int i = 0, j = 0;
	 olist[o]->isPortal = 0; // not a portal
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				free(olist[o]->pos[i][j]);
				j++;
		  }
		  i++;
	 }
	 free(olist[o]->pos);
	 olist[o] = 000;
	 objcnt--;
	 Log("end of destroyObj\n");
	 return;
}

/* so you have a portal count, starting at 0. if == 0, initialize the portal array; initialize both objects to all zeros for pos arrays; lastportal ++ % 2. if cnt == 0, 1, at beginning. if at 1, portal[0]->isPortal = false. else, if ct == 2, portal[0] and [1] -> isPortal = true.
 * */

void initPortal (void) // easy - only ever two, check if two, then one turns into new portal. need to check age??
{
	 Log("start of initPortal\n");
	 struct portal * p = 000;
	 if (p == 000)
	 {
		  p = (struct portal*)malloc(1*sizeof(struct portal*));
	 }
	 p->pos = (float ***)malloc(imgres*sizeof(float***));
	 int i = 0, j = 0;
	 while (i < imgres)
	 {
		  p->pos[i++] = (float **)malloc(imgres*sizeof(float**));
	 }
	 i = 0;
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				p->pos[i][j++] = (float *)malloc(imgres*sizeof(float*));
		  }
		  i++;
	 }
	 p->isPortal = 0; // not a portal - yet
	 p->halfWidth = pWidth/2.0;
	 p->halfHeight = pHeight/2.0;
	 Log("end of initPortal\n");
	 return;
}

void initObj (void) // make a new object. check for full/uninitialized list.
{
	 Log("start of initObj\n");
	 int i = 0;
	 if (objcnt == 0) // uninitialized
	 {
		  objcnt += 1;
		  // get more memory
		  olist = (struct obj**)malloc((objcnt)*2*sizeof(struct obj*));
		  objcnt -= 1;
	 }
	 else if (objcnt == maxobj-1)
	 {
		  struct obj ** tmp;
		  int c = objcnt;
		  tmp = (struct obj**)malloc((maxobj)*2*sizeof(struct obj*));
		  while (i < c)
		  {
				tmp[i] = olist[i];
				destroyObj(i);
				i++;
		  }
		  olist = tmp;
		  objcnt = c;
	 }
	 struct obj * o = 000;
	 if (o == 000)
	 {
		  o = (struct obj*)malloc(1*sizeof(struct obj*));
	 }
	 int j = 0;
	 o->pos = (float ***)malloc(imgres*sizeof(float***));
	 while (i < imgres)
	 {
		  o->pos[i++] = (float **)malloc(imgres*sizeof(float**));
	 }
	 i = 0;
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				o->pos[i][j++] = (float *)malloc(imgres*sizeof(float*));
		  }
		  i++;
	 }
	 o->isPortal = 0; // not a portal
	 olist[objcnt++] = o;
	 Log("end of initObj\n");
	 //	 return o;
}

void drawOval(float ** oval)
{
	 Log("start drawOval\n");
	 float x = 0.0, y = 0.0;
	 float t = 0.0;
	 int i = 0;
	 do
	 {
		  t += ((2*pi)/imgres); // 1000 points for the circle
		  x = cos(t);
		  y = sin(t);
		  x += 1;
		  y += 1;
		  x *= pWidth; // scale circle - radius
		  y *= pHeight;
		  oval[i][0] = x;
		  oval[i][1] = y;
		  i++;
	 }
	 while (t < 360 && i < imgres); // try t as a counter
	 Log("end drawOval\n");
}
