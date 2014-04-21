#include "objects.h"

using namespace std;

object::object (const object& r)
{
	 Log("in object copy constructor\n");
	 pos[0] = r.pos[0];
	 pos[1] = r.pos[1];
	 pos[2] = r.pos[2];
	 portable = r.portable;
	 n[0] = r.n[0];
	 n[1] = r.n[1];
	 n[2] = r.n[2];
	 head = r.head;
	 d[0] = r.n[0];
	 d[1] = r.n[1];
	 d[2] = r.n[2];
	 deadly = r.deadly;
	 objcnt++;
	 Log("end of object copy constructor, objcnt now = %d\n", objcnt);
}

object::object (const Vec p, const int able, vec_list * vl) // acts as default constructor
{
	 Log("in default object constructor\n");
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
	 /* both zero vectors - this will serve as a sentinel value when we check to see if we need to set these */
	 n[0] = 0.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
	 d[0] = 0.0;
	 d[1] = 0.0;
	 d[2] = 0.0;
	 setDeadly(0);
	 objcnt++;
	 Log("end of object constructor, objcnt now = %d\n", objcnt);
}

object::~object()
{
	 Log("in object destructor\n");
	 pos[0] = empty_vec[0];
	 pos[1] = empty_vec[1];
	 pos[2] = empty_vec[2];
	 portable = 0;
	 n[0] = 0.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
	 d[0] = 0.0;
	 d[1] = 0.0;
	 d[2] = 0.0;
	 head = initNode();
	 setDeadly(0);
	 objcnt--;
	 Log("end of object destructor, objcnt now = %d\n", objcnt);
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

// accessors
Vec * object::getPos (void)
{
	 return &pos;
}

void object::setD (const Vec &v)
{
	 d[0] = v[0];
	 d[1] = v[1];
	 d[2] = v[2];
}

void object::setN (const Vec &v)
{
	 n[0] = v[0];
	 n[1] = v[1];
	 n[2] = v[2];
}

Vec * object::getD(void)
{
	 return &d;
}

Vec * object::getN(void)
{
	 return &n;
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
		  return (head->v);
	 vec_list *t = head;
	 while (i > 0)
	 {
		  t = t->next;
		  if (t == 0)
				return 0;
		  i--;
	 }
	 return (t->v);
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

void object::makeUnit(Vec * v)
{
	 double l = (pow((double)(*v[0]), 2.0) + pow((double)(*v[1]), 2.0) + pow((double)(*v[2]), 2.0));
	 Log("in makeUnit, l calculated to be %f\n", l);
	 if (l != 0.0)
		  l = sqrt(l);
	 else
		  l = 1;
	 Log("l calculated to be %f\n", l);
	 *v[0] = (*v[0]/l);
	 *v[1] = (*v[1]/l);
	 *v[2] = (*v[2]/l);
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
	 oss << "Directional vector:\n";
	 oss << "\t<" << d[0] << ", " << d[1] << ", " << d[2] << ">";
	 oss << endl;
	 oss << "Object is deadly?\n";
	 if (isDeadly())
		  oss << "True\n";
	 else
		  oss << "False\n";
	 return oss.str();
}

// position vector, isPortalable, verticies, normal vector, directional vector, isDeadly
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
	 oss << n[0] << "," << n[1] << "," << n[2] << ",";
	 oss << d[0] << "," << d[1] << "," << d[2] << ",";
	 oss << isDeadly();
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

int object::isDeadly(void)
{
	 return deadly;
}

void object::setDeadly(const int &a = 1)
{
	 deadly = a;
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
	 objcnt--;
	 setIsPlaced(0);
	 drawPortal();
	 setDeadly(0);
}

portal::portal(const portal &r) : object(r)
{
	 objcnt--;
	 is_placed = r.is_placed;
	 setDeadly(0);
}

/* automatically calls object destructor? */
portal::~portal()
{
	 objcnt++;
	 is_placed = 0;
	 setDeadly(0);
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
	 int x = 0, y = 0, z = 0;
	 x = p_width;
	 y = p_height;
	 Vec a, b, c;
	 a[0] = -1*x;
	 a[1] = -1*y;
	 a[2] = 0;
	 b[0] = -1*x;
	 b[1] = 1*y;
	 b[2] = 0;
	 c[0] = 1*x;
	 c[1] = 1*y;
	 c[2] = 0;
	 addVec(-1*x, -1*y, z); // draw a basic portal
	 addVec(-1*x, 1*y, z);
	 addVec(1*x, 1*y, z);
	 addVec(1*x, -1*y, z);
	 Log("in drawPortal, creating vectors:\n");
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
	 VecSub(a, b, d); // directional vector, not unit
	 VecSub(b, c, n); // normal vector, not unit
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
	 Log("making magnitude 1...\n");
	 makeUnit(&d);
	 makeUnit(&n);
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
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
