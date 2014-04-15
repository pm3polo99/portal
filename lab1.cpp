/****** TO DO *****
 * create list of portal objects to check when collision occurs
 * maybe create list of all objects - walls, obstacles, etc
 * make sure to free used memory
 */


//cs335 Spring 2014
//
//program: lab1.c
//author:  Gordon Griesel
//date:    2014
//
//This program demonstrates the use of OpenGL and XWindows
//
//Assignment:
//
//Simplify this program by placing some of the functionality in other files.
//See the lab assignment web page for instructions.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include <X11/keysym.h>
//#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/gl.h>
//#include <GL/glu.h>

#include "log.h"
#include "fonts.h"
#include "timing.h"
#include "xwin.h"
#include "const.h"
#include "objects.h"

using namespace std;

// defined types
typedef double Flt;
//typedef double Vec[3]; // defined in objects.h
typedef Flt	Matrix[4][4];

// X Windows variables
int xres = 800;
int yres = 600;
int zres = 1;

// Timing variables
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)

//function prototypes
void init_opengl(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e);
void check_keys(XEvent *e);
void init();
void init_sounds(void);
void physics(void);
void render(void);

void putWall(void);
void putOval(void);
void cleanupObjects(void);

void initObjects(void);

//global variables
int done=0;
int objcnt = 0;
int keys[65536];

object **objects;
portal * pLeft;
portal * pRight;

// shapes
// instead of individual shapes, make a list of shapes
// to do a list of shapes (general), need to move to c++, no issue i think, try for pure c
// maybe struct obj with structs for every obj and integers for count of each object type, one int for count of total objects
Display *dpy;
Window win;
GLXContext glc;

static float pos[3]={200.0,200.0,0.0};
static float vel[3]={0.0,0.0,0.0};

int main(void)
{
	 logOpen();
	 Log("start of main\n");
	 initXWindows();
	 init_opengl();
	 init();
	 clock_gettime(CLOCK_REALTIME, &timePause);
	 clock_gettime(CLOCK_REALTIME, &timeStart);
	 while(!done) {
		  while(XPending(dpy)) {
				XEvent e;
				XNextEvent(dpy, &e);
				check_resize(&e);
				check_mouse(&e);
				check_keys(&e);
		  }
		  //
		  //Below is a process to apply physics at a consistent rate.
		  //1. Get the time right now.
		  clock_gettime(CLOCK_REALTIME, &timeCurrent);
		  //2. How long since we were here last?
		  timeSpan = timeDiff(&timeStart, &timeCurrent);
		  //3. Save the current time as our new starting time.
		  timeCopy(&timeStart, &timeCurrent);
		  //4. Add time-span to our countdown amount.
		  physicsCountdown += timeSpan;
		  //5. Has countdown gone beyond our physics rate? 
		  //       if yes,
		  //           In a loop...
		  //              Apply physics
		  //              Reducing countdown by physics-rate.
		  //              Break when countdown < physics-rate.
		  //       if no,
		  //           Apply no physics this frame.
		  while(physicsCountdown >= physicsRate) {
				//6. Apply physics
				physics();
				//7. Reduce the countdown by our physics-rate
				physicsCountdown -= physicsRate;
		  }
		  //Always render every frame.
		  render();
		  glXSwapBuffers(dpy, win);
	 }
	 Log("in main, about to call cleanupXWindows\n");
	 cleanupXWindows();
	 //	 cleanup_fonts();
	 Log("in main, about to call cleanupObjects\n");
	 cleanupObjects();
	 logClose();
	 return 0;
}

void cleanupObjects()
{
	 Log("start of cleanupObjects\n");
	 delete pLeft;
	 /*
		 int i = objcnt;
		 while (i > 0)
		 {
		 Log("objcnt = %d\n", i);
		 destroyObj(--i);
		 }
		 i = portalcnt;
		 while (i > 0)
		 {
		 Log("portalcnt = %d\n", i);
		 destroyPortal(--i);
		 }
		 */
	 Log("end of cleanupObjects\n");
}

void reshape_window(int width, int height)
{
	 //window has been resized.
	 setup_screen_res(width, height);
	 //
	 glViewport(0, 0, (GLint)width, (GLint)height);
	 glMatrixMode(GL_PROJECTION); glLoadIdentity();
	 glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	 glOrtho(0, xres, 0, yres, -1, 1);
	 set_title();
}

void init_opengl(void)
{
	 //OpenGL initialization
	 glViewport(0, 0, xres, yres);
	 //Initialize matrices
	 glMatrixMode(GL_PROJECTION); glLoadIdentity();
	 glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	 //This sets 2D mode (no perspective)
	 glOrtho(0, xres, 0, yres, -1, 1);
	 //Disable some states for simple 2D animation
	 glDisable(GL_LIGHTING);
	 glDisable(GL_DEPTH_TEST);
	 glDisable(GL_FOG);
	 glDisable(GL_CULL_FACE);
	 //Set the clear color of the screen to white
	 glClearColor(1.0, 1.0, 1.0, 1.0);
	 //glClear(GL_COLOR_BUFFER_BIT);
	 //Do this to allow fonts
	 glEnable(GL_TEXTURE_2D);
	 //	 initialize_fonts();
}

void check_resize(XEvent *e)
{
	 //The ConfigureNotify is sent by the
	 //server if the window is resized.
	 if (e->type != ConfigureNotify)
		  return;
	 XConfigureEvent xce = e->xconfigure;
	 if (xce.width != xres || xce.height != yres) {
		  //Window size did change.
		  reshape_window(xce.width, xce.height);
	 }
}

void init()
{
	 initObjects();

	 pLeft = new portal();
	 pLeft->setPos(xres/3, yres/3, 0);

	 memset(keys, 0, 65536);
	 Log("end of init\n");
}

void initObjects(void)
{
	 try
	 {
		  objects = new object * [maxobj];
		  objects[0] = new object(); // floor
		  objects[1] = new object(); // left wall
		  objects[2] = new object(); // right wall
		  objects[3] = new object(); // ceiling
	 }
	 catch (bad_alloc)
	 {
		  printf("Insufficient memory! Aborting\n");
		  exit(1);
	 }
	 catch (...)
	 {
		  printf("An unknown error occured! Exiting\n");
		  exit(2);
	 }
}

void check_mouse(XEvent *e)
{
	 //Did the mouse move?
	 //Was a mouse button clicked?
	 static int savex = 0;
	 static int savey = 0;
	 //
	 if (e->type == ButtonRelease) {
		  return;
	 }
	 if (e->type == ButtonPress) {
		  if (e->xbutton.button==1) {
				//Left button is down
		  }
		  if (e->xbutton.button==3) {
				//Right button is down
		  }
	 }
	 if (savex != e->xbutton.x || savey != e->xbutton.y) {
		  //Mouse moved
		  savex = e->xbutton.x;
		  savey = e->xbutton.y;
	 }
}

static int jumped = 0;

void check_keys(XEvent *e)
{
	 //keyboard input?
	 static int shift=0;
	 int key = XLookupKeysym(&e->xkey, 0);
	 //Log("key: %i\n", key);
	 if (e->type == KeyRelease)
	 {
		  keys[key]=0;
		  if (key == XK_Shift_L || key == XK_Shift_R)
				shift=0;
		  if (key == XK_space)
		  {
				jumped = 0;
		  }
		  return;
	 }
	 if (e->type == KeyPress)
	 {
		  if (key == XK_Escape)
		  {
				done = 1;
				return;
		  }
		  keys[key]=1;
		  if (key == XK_Shift_L || key == XK_Shift_R) {
				shift=1;
				return;
		  }
	 }
	 else
	 {
		  return;
	 }
	 if (shift)
	 {
		  // run?
	 }
}

void physics(void)
{
	 int addgrav = 0;
	 //Update position of object using its velocity
	 /* DEBUG */
	 /*
		 printf("\nin phys:\npos[0] = %f\npos[1] = %f\nvel[0] = %f\nvel[1] = %f\n",
		 pos[0], pos[1], vel[0], vel[1]);
		 */
	 /* DEBUG */
	 // move
	 pos[0] += vel[0];
	 pos[1] += vel[1];
	 //Now, update the velocity...
	 //Check for collision with window edges
	 // *** i added a small buffer so were not exactly on the edge of the thing
	 // for loop, go through a list of objects, check for collision
	 //

	 if (keys[LEFT_PORTAL_KEY] || keys[XK_z])
	 {
		  /* create a portal */
	 }
	 if (keys[RIGHT_PORTAL_KEY] || keys[XK_x])
	 {
		  /* create a portal */
	 }
	 if (keys[XK_d] || keys[XK_Right])
	 {
		  if (pos[0] + 2 + 38.0 >= (float)xres) // right edge
		  {
				//		  pos[0] = 2.0+38.0; // wrap

				// do nothing
		  }
		  else
		  {
				pos[0] += 15;
		  }
		  if (vel[1] > 0.0)
				addgrav = 1;
	 }
	 if (keys[XK_a] || keys[XK_Left])
	 {
		  if (pos[0] - 2 - 38.0 <= 0.0) // on left edge
		  {
				//		  pos[0] = (float)xres - 38.0 - 2;
				//gravity not important now
				//do nothing
		  }
		  else
		  {
				pos[0] -= 15;
		  }
		  if (vel[1] > 0.0)
				addgrav = 1;
	 }

	 if (keys[XK_s] || keys[XK_Down])
	 {
		  // change aim angle
	 }

	 if (keys[XK_w] || keys[XK_Up])
	 {
		  // change aim angle
	 }

	 if (keys[XK_space])
	 {
		  if (jumped && vel[1] != 0.0)
		  {
				// already jumped, do nothing
		  }
		  else if (pos[1] + 10 - 38.0 >= (float)yres) // top
		  {
				//		  pos[1] = 0.0 + 38.0 + 2;
				//		  do nothing
				if (vel[1] > 0.0)
					 addgrav = 1;
		  }
		  else
		  {
				vel[1] = 10;
				pos[1] += vel[1];
				if (vel[1] > 0.0)
					 addgrav = 1;
		  }
		  jumped = 1;
	 }
	 if (pos[1] - 38.0 + 2 > 0)
	 {
		  addgrav = 1;
	 }
	 if (pos[1] - 38.0 + 2 < 0)
	 {
		  pos[1] = 36.0;
		  vel[1] = 0.0;
	 }
	 if (vel[0] == 0.0)
	 {
		  //done with jump ??
		  jumped = 0;
	 }
	 //Apply gravity
	 if (addgrav)
		  vel[1] -= 2.5;
}

void putOval(void)
{
	 Vec v;
	 int i = 0;
	 glClear (GL_COLOR_BUFFER_BIT);
	 glColor3ub (0, 0, 0);
	 glPushMatrix();
	 //	 glTranslatef(plist[(plast+1)%2]->pos[0], plist[(plast+1)%2]->pos[1], plist[(plast+1)%2]->pos[2]);
	 glBegin(GL_TRIANGLE_FAN);
	 while (i < portalres)
	 {
		  v[0] = pLeft->getVert(i)[0];
		  v[1] = pLeft->getVert(i)[1];
		  v[2] = pLeft->getVert(i)[2];
		  glVertex3f(v[0], v[1], v[2]);
		  //		  glVertex3f(pLeft->getVert(i)[0], pLeft->getVert(i)[1], pLeft->getVert(i)[2]);
		  i++;
	 }
	 /* actually starting at mid right??
	  * x = sin(t), y = cos(t)
	  */
	 /* HERE
		 int i = 0, j = 0, k = 0;
		 do
		 {
		 while (i < imgres)
		 {
		 j = 0;
		 while (j < imgres)
		 {
		 k = 0;
		 while (k < imgres)
		 {
		 if (plist[(plast+1)%2]->img[i][j][k][0] == 1)
		 {
		 glVertex3f(i, j, k);
		 }
		 k++;
		 }
		 j++;
		 }
		 i++;
		 }
		 i++;
		 }
		 while (i < imgres);
		 */

	 glEnd();
	 glPopMatrix();
}

void putWall(void)
{
	 glClear (GL_COLOR_BUFFER_BIT);
	 glColor3ub (0, 0, 0);
	 float left = (float)xres/3.0;
	 float right = 2*(float)xres/3.0;
	 float top = (float)yres/1.3;
	 float bot = 0.0;
	 float z = 0.0;
	 glBegin(GL_POLYGON);
	 glVertex3f (left, bot, z);
	 glVertex3f (right, bot, z);
	 glVertex3f (right, top, z);
	 glVertex3f (left, top, z);
	 glEnd();
	 glPopMatrix();
}

void render(void)
{
	 //	 const char heading[] = "animation";
	 //	 Rect r;

	 glClear(GL_COLOR_BUFFER_BIT);
	 //	 r.bot = yres - 20;
	 //	 r.left = 10;
	 //	 r.center = 0;
	 //	 ggprint8b(&r, 16, 0, heading);
	 putOval();
	 //Draw a simple square
	 {
		  float wid = 40.0f;
		  glColor3ub(30,60,90);
		  glPushMatrix();
		  glTranslatef(pos[0], pos[1], pos[2]);
		  glBegin(GL_QUADS);
		  glVertex2i(-wid,-wid);
		  glVertex2i(-wid, wid);
		  glVertex2i( wid, wid);
		  glVertex2i( wid,-wid);
		  glEnd();
		  glPopMatrix();
	 }
	 // try to draw a rectangle in the middle of the screen
}

