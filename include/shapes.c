/* TO DO 
 * overload destroy to take no args to destroy all, one int to destroy one. void on all.
 */

#include "shapes.h"

void destroyPortal (int p)
{
	 Log("start of destroyPortal\n");
	 if (p == 000)
		  return p;
	 int i = 0;
	 p->isPortal = 0; // not a portal - yet
	 while (i < 1000)
	 {
		  free(p->pos[i++]);
	 }
	 free(p->pos);
	 p = 000;
	 Log("end of destroyPortal\n");
	 return p;
}

//struct obj * destroyObj (struct obj *o)
void destroyObj (int o)
{
	 Log("start of destroyObj\n");
	 int i = 0;
	 olist[o]->isPortal = 0; // not a portal
	 while (i < 1000)
	 {
		  free(olist[o]->pos[i++]);
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
	 if (objcnt < 1) // maybe init objects first, then after initialized, cnt > 0
	 {
	 struct portal * p = 000;
	 if (p == 000)
	 {
		  p = (struct portal*)malloc(1*sizeof(struct portal*));
	 }
	 p->pos = (float **)malloc(1000*sizeof(float**));
	 int i = 0;
	 while (i < 1000)
	 {
		  p->pos[i++] = (float *)malloc(1000*sizeof(float*));
	 }
	 p->isPortal = 0; // not a portal - yet
	 p->halfWidth = pWidth/2.0;
	 p->halfHeight = pHeight/2.0;
	 Log("end of initPortal\n");
	 return p;
}

void initObj (void) // make a new object. check for full/uninitialized list.
{
	 Log("start of initObj\n");
	 if (objcnt == 0 || olist[objcnt+1] == 000) // uninitialized or full
	 {
		  objcnt += 1;
		  // get more memory
		  olist = (struct obj**)malloc((objcnt)*2*sizeof(struct obj*));
		  objcnt -= 1;
	 }
	 struct obj * o = 000;
	 if (o == 000)
	 {
		  o = (struct obj*)malloc(1*sizeof(struct obj*));
	 }
	 o->pos = (float **)malloc(1000*sizeof(float**));
	 int i = 0;
	 while (i < 1000)
	 {
		  o->pos[i] = (float *)malloc(1000*sizeof(float*));
		  o->pos[i++] = 000;
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
		  t += ((2*pi)/1000.0); // 1000 points for the circle
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
	 while (t < 360 && i < 1000); // try t as a counter
	 Log("end drawOval\n");
}
