#ifndef _OBJ_H
#define _OBJ_H

struct obj
{
	 float ** pos;
	 int isPortal; // not a portal. needed???
};

struct portal
{
	 float ** pos;
	 int isPortal; // not a portal until there are 2 portals
};

#endif /* obj.h */
