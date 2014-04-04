#include "shapes.h"

void destroyPortal (portal *p)
{
	 int i = 0;
	 p->isPortal = 0; // not a portal - yet
	 while (i < xres)
	 {
		  free(p->pos[i++]);
	 }
	 free(p->pos);
	 p = 000;
	 objcnt--;
	 portalcnt--;
}

void destroyWall (wall *w)
{
	 int i = 0;
	 w->isPortal = 0; // not a portal
	 while (i < xres)
	 {
		  free(w->pos[i++]);
	 }
	 free(w->pos);
	 w = 000;
	 objcnt--;
	 wallcnt--;
}

void initPortal (portal *p)
{
	 p->pos = (int **)malloc(xres*sizeof(int**));
	 int i = 0;
	 while (i < xres)
	 {
		  p->pos[i++] = (int *)malloc(yres*sizeof(int*));
	 }
	 p->isPortal = 0; // not a portal - yet
	 objcnt++;
	 portalcnt++;
}

void initWall (wall *w)
{
	 w->pos = (int **)malloc(xres*sizeof(int**));
	 int i = 0;
	 while (i < xres)
	 {
		  w->pos[i++] = (int *)malloc(yres*sizeof(int*));
	 }
	 w->isPortal = 0; // not a portal
	 objcnt++;
	 wallcnt++;
}

void createOval(void)
{
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
		  x *= 100; // scale circle - radius
		  y *= 150;
		  oval[i][0] = x;
		  oval[i][1] = y;
		  i++;
	 }
	 while (t < 360 && i < 1000); // try t as a counter
}
