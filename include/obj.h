#ifndef _OBJ_H
#define _OBJ_H

typedef struct _obj
{
	 int ** pos;
	 int isPortal; // not a portal. needed???
} obj;

typedef struct _portal
{
	 int ** pos;
	 int isPortal; // not a portal until there are 2 portals
} portal;

#endif /* obj.h */
