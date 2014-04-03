#pragma once
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int xres;
extern int yres;

#ifndef XWIN_H
#define XWIN_H
Display *dpy;
Window win;
GLXContext glc;

void initXWindows(void);
void cleanupXWindows(void);
void setup_screen_res(const int, const int);

void set_title(void);

#endif /* xwin.h */
