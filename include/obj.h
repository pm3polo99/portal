#ifndef _OBJ_H
#define _OBJ_H

static int objcnt = 0;
static int wallcnt = 0;
static int portalcnt = 0;

typedef struct _wall
{
	 int ** pos;
	 int isPortal; // not a portal. needed???
} wall;

typedef struct _portal
{
	 int ** pos;
	 int isPortal; // not a portal until there are 2 portals
} portal;

#endif /* obj.h */
