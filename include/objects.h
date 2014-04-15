#pragma once
#include "const.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecNegate(a)	(a)[0]=(-(a)[0]); (a)[1]=(-(a)[1]); (a)[2]=(-(a)[2]);
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a)	((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecLenSq(a)	sqrtf((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecCopy(a,b)	(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];
#define VecAdd(a,b,c) (c)[0]=(a)[0]+(b)[0]; (c)[1]=(a)[1]+(b)[1]; (c)[2]=(a)[2]+(b)[2]
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; (c)[1]=(a)[1]-(b)[1]; (c)[2]=(a)[2]-(b)[2]
#define VecS(A,a,b) (b)[0]=(A)*(a)[0]; (b)[1]=(A)*(a)[1]; (b)[2]=(A)*(a)[2]
#define VecAddS(A,a,b,c) (c)[0]=(A)*(a)[0]+(b)[0]; (c)[1]=(A)*(a)[1]+(b)[1]; (c)[2]=(A)*(a)[2]+(b)[2]
#define VecCross(a,b,c) (c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; (c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; (c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]
#define VecZero(v) (v)[0]=0.0;(v)[1]=0.0;v[2]=0.0
#define ABS(a) (((a)<0)?(-(a)):(a))
#define SGN(a) (((a)<0)?(-1):(1))
#define SGND(a) (((a)<0.0)?(-1.0):(1.0))
#define TOGGLE(a) (a = (a + 1) % 2)

typedef float Vec[3];
static const Vec zero_vec = {0.0, 0.0, 0.0};
static const Vec empty_vec = {-1.0, -1.0, -1.0};

static float pWidth = 100;
static float pHeight = 150;
static float pDepth = 1;

typedef struct _vec_list
{
	 Vec v;
	 _vec_list * next;
} vec_list;

class object
{
	 protected:
		  Vec pos;
		  int portable;
		  vec_list * head;
		  Vec n;

		  void setN(void);

	 public:
		  object (const object&);
		  object (const Vec p = zero_vec, const int able = 0, vec_list * vl = 0);
		  ~object();
		  vec_list * initNode(void);
		  float * getN(void);
		  float * getPos (void);
		  void getPos (Vec &);
		  int isPortalable (void);
		  int getPortable (void);
		  vec_list * getHead (void);
		  float * getVert (int);
		  void getVert (Vec &, int);
		  vec_list * getLastVert (void);
		  string toString(void);
		  string dumpCsv(void);
		  void setPos (const int &, const int &, const int &);
		  void setPos (const Vec &);
		  void setPos (const int [3]);
		  void setPortalable (const int &a = -1);
		  void setPortable (const int &a = -1);
		  void setHead (const vec_list *);
		  void addVec (const Vec);
		  void addVert (const Vec);
		  void addVec (const int [3]);
		  void addVert (const int [3]);
		  void addVec (const int&, const int &, const int&);
		  void addVert (const int &, const int &, const int &);
		  int isEmpty(void);
		  void shift (const Vec &);
		  void shift (const int [3]);
		  void shift (const int &, const int &, const int &);

		  object& operator = (const object&);
};

class portal : public object
{
	 protected:
		  int is_placed;

		  void drawPortal (void); // a rectangle idiot

	 public:
		  portal();
		  portal(const portal &);
		  ~portal();

		  int getIsPlaced (void);
		  int isPlaced (void);
		  string toString(void);
		  string dumpCsv(void);

		  void setIsPlaced (const int &);
		  void setPlaced (const int &);


		  portal& operator = (const portal&);

		  friend bool operator == (const portal&, const portal&);
};

/*
class portal_list : public portal
{
	 protected:
		  int portal_count;
		  int plast;
		  portal * plist;

	 public:
		  portal_list();
		  portal_list(const portal_list &);
		  portal_list(const portal &, const portal &, const int &);
		  ~portal_list();

		  portal * getPortal(const int &);
		  int getPlast(void);
		  int getPortalCount(void);
		  string toString(void);
		  string dumpCsv(void);

		  void setPlast (const int &);
		  void setPortalCount (const int &);

		  void destroyPortal (const int &);
		  void makePortal (void);
		  portal_list& operator = (const portal_list&);
};
*/
