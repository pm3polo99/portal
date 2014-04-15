#include "objects.h"

using namespace std;

object::object (const object& r)
{
	 pos[0] = r.pos[0];
	 pos[1] = r.pos[1];
	 pos[2] = r.pos[2];
	 portable = r.portable;
	 n[0] = r.n[0];
	 n[1] = r.n[1];
	 n[2] = r.n[2];
	 head = r.head;
}

object::object (const Vec p, const int able, vec_list * vl) // acts as default constructor
{
	 pos[0] = p[0];
	 pos[1] = p[1];
	 pos[2] = p[2];
	 portable = able;
	 if (vl == 0)
	 {
		  head = initNode();
	 }
	 else
	 {
		  head = vl;
	 }
	 /* facing left */
	 n[0] = -1.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
}

object::~object()
{
	 pos[0] = empty_vec[0];
	 pos[1] = empty_vec[1];
	 pos[2] = empty_vec[2];
	 portable = 0;
	 n[0] = -1.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
	 head = initNode();
}

vec_list * object::initNode(void)
{
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = empty_vec[0];
	 a->v[1] = empty_vec[1];
	 a->v[2] = empty_vec[2];
	 a->next = 0;
	 return a;
}

/* following takes FIRST TWO VECTORS and calculates the normal vector based off of them */
void object::setN(void)
{
	 n[0] = (head->next->v[0] - head->v[0]);
	 n[1] = (head->next->v[1] - head->v[1]);
	 n[2] = (head->next->v[2] - head->v[2]);
}

// accessors
float * object::getPos (void)
{
	 return pos;
}

float * object::getN(void)
{
	 return n;
}

void object::getPos (Vec &p)
{
	 p[0] = pos[0];
	 p[1] = pos[1];
	 p[2] = pos[2];
}

int object::isPortalable (void)
{
	 return portable;
}

int object::getPortable (void)
{
	 return portable;
}

vec_list * object::getHead (void)
{
	 return head;
}

void object::getVert (Vec &p, int i = 0)
{
	 if (i == 0)
	 {
		  p[0] =  head->v[0];
		  p[1] =  head->v[1];
		  p[2] =  head->v[2];
		  return;
	 }
	 vec_list *t = head;
	 while (i > 0)
	 {
		  t = t->next;
		  if (t == 0)
		  {
				p[0] = empty_vec[0];
				p[1] = empty_vec[1];
				p[2] = empty_vec[2];
				return;
		  }
		  i--;
	 }
	 p[0] = t->v[0];
	 p[1] = t->v[1];
	 p[2] = t->v[2];
}

float * object::getVert (int i = 0)
{
	 if (i == 0)
		  return head->v;
	 vec_list *t = head;
	 while (i > 0)
	 {
		  t = t->next;
		  if (t == 0)
				return 0;
		  i--;
	 }
	 return t->v;
}

vec_list * object::getLastVert (void)
{
	 vec_list *t = head;
	 while (t->next != 0)
	 {
		  t = t->next;
	 }
	 return t;
}

string object::toString(void)
{
	 ostringstream oss;
	 oss << "Object pos: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << endl;
	 oss << "Object portalable? ";
	 if (isPortalable())
		  oss << "True\n";
	 else
		  oss << "False\n";
	 oss << "Object Veriticies:\n";
	 vec_list * t = head;
	 while (t != 0)
	 {
		  oss << "\t(" << t->v[0] << ", " << t->v[1] << ", " << t->v[2] << ")\n";
		  t = t->next;
	 }
	 oss << "Normal vector:\n";
	 oss << "\t<" << n[0] << ", " << n[1] << ", " << n[2] << ">";
	 oss << endl;
	 return oss.str();
}

string object::dumpCsv(void)
{
	 ostringstream oss;
	 oss << pos[0] << "," << pos[1] << "," << pos[2] << "," << isPortalable() << ",";
	 vec_list * t = head;
	 while (t != 0)
	 {
		  oss << t->v[0] << "," << t->v[1] << "," << t->v[2] << ",";
		  t = t->next;
	 }
	 oss << n[0] << "," << n[1] << "," << n[2];
	 oss << endl;
	 return oss.str();
}

// mutators
/* HERE
 * need to account for object edges being outside of boundaries of arena
 * maybe try to shift all vectors first, then, if no collision (with xres, yres, zres), shift pos?
 * if collision, undo all changes?
 * or keep a max width of the object?
 */

void object::setPos (const Vec &p)
{
	 if (p[0] < 0)
		  pos[0] = 0;
	 else
		  pos[0] = p[0];
	 if (p[1] < 0)
		  pos[1] = 0;
	 else
		  pos[1] = p[1];
	 if (p[2] < 0)
		  pos[2] = 0;
	 else
		  pos[2] = p[2];
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += p[0];
		  t->v[1] += p[1];
		  t->v[2] += p[2];
		  t = t->next;
	 }
}
void object::setPos (const int p[3])
{
	 if (p[0] < 0)
		  pos[0] = 0;
	 else
		  pos[0] = p[0];
	 if (p[1] < 0)
		  pos[1] = 0;
	 else
		  pos[1] = p[1];
	 if (p[2] < 0)
		  pos[2] = 0;
	 else
		  pos[2] = p[2];
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += p[0];
		  t->v[1] += p[1];
		  t->v[2] += p[2];
		  t = t->next;
	 }
}
void object::setPos (const int &x = 0, const int &y = 0, const int &z = 0)
{
	 if (x < 0)
		  pos[0] = 0;
	 else
		  pos[0] = x;
	 if (y < 0)
		  pos[1] = 0;
	 else
		  pos[1] = y;
	 if (z < 0)
		  pos[2] = 0;
	 else
		  pos[2] = z;
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += x;
		  t->v[1] += y;
		  t->v[2] += z;
		  t = t->next;
	 }
}

void object::setPortable (const int &a)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(portable);
	 }
	 else
	 {
		  portable = a;
	 }
}

void object::setPortalable (const int &a)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(portable);
	 }
	 else
	 {
		  portable = a;
	 }
}

void object::setHead (const vec_list * p = 0)
{
	 if (p == 0)
		  return;
	 head = (vec_list *)p;
}

int object::isEmpty(void)
{
	 if (head == 0)
		  return 1;
	 if (head->v[0] == empty_vec[0] && head->v[1] == empty_vec[1] && head->v[2] == empty_vec[2])
		  return 2;
	 return 0;
}

void object::addVert (const Vec p)
{
	 if (p == 0)
		  return;
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = p[0];
		  head->v[1] = p[1];
		  head->v[2] = p[2];
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = p[0];
	 a->v[1] = p[1];
	 a->v[2] = p[2];
	 //				n->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::addVec (const Vec p)
{
	 if (p == 0)
		  return;
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = p[0];
		  head->v[1] = p[1];
		  head->v[2] = p[2];
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = p[0];
	 a->v[1] = p[1];
	 a->v[2] = p[2];
	 //				n->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::addVert (const int p[3])
{
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = p[0];
		  head->v[1] = p[1];
		  head->v[2] = p[2];
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = p[0];
	 a->v[1] = p[1];
	 a->v[2] = p[2];
	 //				a->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::addVec (const int p[3])
{
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = p[0];
		  head->v[1] = p[1];
		  head->v[2] = p[2];
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = p[0];
	 a->v[1] = p[1];
	 a->v[2] = p[2];
	 //				n->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::addVert (const int &x = 0, const int &y = 0, const int &z = 0)
{
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = x;
		  head->v[1] = y;
		  head->v[2] = z;
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = x;
	 a->v[1] = y;
	 a->v[2] = z;
	 //				n->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::addVec (const int &x = 0, const int &y = 0, const int &z = 0)
{
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = x;
		  head->v[1] = y;
		  head->v[2] = z;
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = x;
	 a->v[1] = y;
	 a->v[2] = z;
	 //				n->next = head; // head insertion
	 getLastVert()->next = a; // tail insertion
	 a->next = 0;
	 return;
}

void object::shift (const Vec &p)
{
	 pos[0] = p[0];
	 pos[1] = p[1];
	 pos[2] = p[2];
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += p[0];
		  t->v[1] += p[1];
		  t->v[2] += p[2];
		  t = t->next;
	 }
}

void object::shift (const int p[3])
{
	 pos[0] = p[0];
	 pos[1] = p[1];
	 pos[2] = p[2];
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += p[0];
		  t->v[1] += p[1];
		  t->v[2] += p[2];
		  t = t->next;
	 }
}

void object::shift (const int &x, const int &y, const int &z)
{
	 pos[0] = x;
	 pos[1] = y;
	 pos[2] = z;
	 /* shift image's position with position */
	 vec_list * t = head;
	 while (t != 0)
	 {
		  t->v[0] += x;
		  t->v[1] += y;
		  t->v[2] += z;
		  t = t->next;
	 }
}

object & object::operator = (const object &r)
{
	 pos[0] = r.pos[0];
	 pos[1] = r.pos[1];
	 pos[2] = r.pos[2];
	 portable = r.portable;
	 /* need to create entire new list of vectors? or not??
	  *
	  try
	  {
	  head = new vec_list;
	  }
	  catch (bad_alloc)
	  {
	  cout << "Insufficient memory! Aborting\n";
	  exit(1);
	  }
	  catch (...)
	  {
	  cout << "An unknown error occured! Aborting\n";
	  exit(2);
	  }
	  */
	 head = r.head;

	 return (*this);
}

/* automatically calls object constructor? */
portal::portal()
{
	 setIsPlaced(0);
	 drawPortal();
}

portal::portal(const portal &r) : object(r)
{
	 is_placed = r.is_placed;
}

/* automatically calls object destructor? */
portal::~portal()
{
	 is_placed = 0;
}

int portal::isPlaced(void)
{
	 return is_placed;
}

int portal::getIsPlaced(void)
{
	 return is_placed;
}

string portal::toString(void)
{
	 ostringstream oss;
	 oss << object::toString();
	 oss << "Is placed?\n\t";
	 if (isPlaced())
		  oss << "Yes\n";
	 else
		  oss << "No\n";
	 oss << endl;
	 return oss.str();
}

string portal::dumpCsv(void)
{
	 ostringstream oss;
	 oss << object::dumpCsv();
	 oss << isPlaced() << ",";
	 return oss.str();
}

void portal::setIsPlaced(const int &a = -1)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(is_placed);
	 }
	 else
	 {
		  is_placed = a;
	 }
}

void portal::setPlaced(const int &a = -1)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(is_placed);
	 }
	 else
	 {
		  is_placed = a;
	 }
}

void portal::drawPortal(void)
{
	 float x = 0.0, y = 0.0, z = 0.0, t = 0.0;
	 for (int i = 0; i < portalres; i++)
	 {
		  t += (pi / portalres);
		  x = (cos(t) + 1) * pWidth;
		  y = (sin(t) + 1) * pHeight;
		  z = (0 + 1) * pDepth;
		  addVec((int)x, (int)y, (int)z);
	 }
}

portal & portal::operator = (const portal &r)
{
	 object::operator=(r);
	 is_placed = r.is_placed;
	 return (*this);
}

bool operator == (const portal &l, const portal &r)
{
	 return (l.pos == r.pos);
}

/*
portal_list::portal_list()
{
	 try
	 {
		  plist = new portal[2];
	 }
	 catch (bad_alloc)
	 {
		  cout << "Insufficient memory! Aborting\n";
		  exit(1);
	 }
	 catch (...)
	 {
		  cout << "An unknown error occured. Aborting\n";
		  exit(2);
	 }
	 portal t, u;
	 plist[LEFT] = t;
	 plist[RIGHT] = u;
	 plast = 0;
	 portal_count = 0;
}

portal_list::portal_list(const portal_list &p) : portal(p)
{
	 try
	 {
		  plist = new portal[2];
	 }
	 catch (bad_alloc)
	 {
		  cout << "Insufficient memory! Aborting\n";
		  exit(1);
	 }
	 catch (...)
	 {
		  cout << "An unknown error occured. Aborting\n";
		  exit(2);
	 }
	 plist[LEFT] = p.plist[LEFT];
	 plist[RIGHT] = p.plist[RIGHT];
	 plast = p.plast;
	 portal_count = p.portal_count;
}

portal_list::portal_list(const portal &a, const portal &b, const int &c = 0)
{
	 plast = c;
	 portal_count = 2;
	 if (&a == 0)
		  portal_count--;
	 if (&b == 0)
		  portal_count--;
	 try
	 {
		  plist = new portal[2];
	 }
	 catch (bad_alloc)
	 {
		  cout << "Insufficient memory! Aborting\n";
		  exit(1);
	 }
	 catch (...)
	 {
		  cout << "An unknown error occured. Aborting\n";
		  exit(2);
	 }
	 plist[LEFT] = a;
	 plist[RIGHT] = b;
}

portal_list::~portal_list()
{
	 delete plist;
	 plast = 0;
	 portal_count = 0;
}

portal * portal_list::getPortal(const int &c = -1)
{
	 if (plist == 0)
		  return 0;
	 if (c != LEFT && c != RIGHT)
	 {
		  return &(plist[plast]);
	 }
	 return (&(plist[c]));
}

int portal_list::getPlast(void)
{
	 return plast;
}

int portal_list::getPortalCount(void)
{
	 return portal_count;
}

string portal_list::toString(void)
{
	 ostringstream oss;
	 oss << "Portal Count:\n\t" << getPortalCount() << endl;
	 oss << "Last portal placed:\n\t" << (getPlast() ? ("1 (Right Portal)"):("0 (Left Portal)")) << endl;
	 for (int i = 0; i  < portal_count; i++)
	 {
		  oss << plist[i].toString();
	 }
	 return oss.str();
}

string portal_list::dumpCsv(void)
{
	 ostringstream oss;
	 oss << getPortalCount() << ",";
	 oss << getPlast() << ",";
	 for (int i = 0; i  < portal_count; i++)
	 {
		  oss << plist[i].dumpCsv();
	 }
	 return oss.str();
}

void portal_list::setPlast(const int &a = -1)
{
	 if (a < 0 || a > 1)
	 {
		  plast = 0;
		  return;
	 }
	 plast = a;
}

void portal_list::setPortalCount(const int &a = -1)
{
	 if (a < 0 || a > 2)
	 {
		  portal_count = 0;
		  return;
	 }
	 portal_count = a;
}

void portal_list::destroyPortal(const int &c = -1)
{
	 if (c != LEFT && c != RIGHT)
	 {
		  plist[plast].~portal(); // ??
	 }
	 else
	 {
		  plist[c].~portal();
	 }
	 portal_count--;
	 TOGGLE(plast);
}

void portal_list::makePortal(void)
{
	 if (portal_count == 2)
	 {
		  destroyPortal(plast);
	 }
	 TOGGLE(plast);
	 portal t;
	 plist[plast] = t;
	 portal_count++;
}

portal_list & portal_list::operator = (const portal_list &r)
{
	 plist = r.plist;
	 plast = r.plast;
	 portal_count = r.portal_count;
	 return (*this);
}
*/
