#include <iostream>
#include "objects.h"
#include <cmath>

using namespace std;

int main()
{
	 portal *p;
	 p = new portal();

	 cout << p->toString() << endl;

	 Vec vector;
	 vector[0] = p->getPos()[0];
	 vector[1] = p->getPos()[1];
	 vector[2] = p->getPos()[2];
	 cout << "p->getPos() returns:\n";
	 cout << "\t(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")" << endl;
	 cout << "p->isPortalable() returns:\n\t" << p->isPortalable() << endl;
	 cout << "Getting getVert(0)...\n";
	 vector[0] = p->getVert(0)[0];
	 vector[1] = p->getVert(0)[1];
	 vector[2] = p->getVert(0)[2];
	 cout << "Done!\n";
	 cout << "p->getVert(0) returns:\n";
	 cout << "\t(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")" << endl;
	 cout << "Getting getVert(3)...\n";
	 vector[0] = p->getVert(3)[0];
	 vector[1] = p->getVert(3)[1];
	 vector[2] = p->getVert(3)[2];
	 cout << "Done!\n";
	 cout << "p->getVert(3) returns:\n";
	 cout << "\t(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")" << endl;
	 cout << "Getting getVert(7)...\n";
	 vector[0] = p->getVert(7)[0];
	 vector[1] = p->getVert(7)[1];
	 vector[2] = p->getVert(7)[2];
	 cout << "Done!\n";
	 cout << "p->getVert(7) returns:\n";
	 cout << "\t(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")" << endl;
	 cout << "Toggling o to portalable...\n";
	 p->setPortalable();
	 cout << "Done!\n";
	 cout << "p->isPortalable() returns:\n\t" << p->isPortalable() << endl;
	 cout << "Toggling o to not portalable...\n";
	 p->setPortalable();
	 cout << "Done!\n";
	 cout << "p->isPortalable() returns:\n\t" << p->isPortalable() << endl;

	 vector[0] = 50;
	 vector[1] = 50;
	 vector[2] = 0;
	 cout << "Setting position to 50, 50, 0 with setPos(vector)...\n";
	 p->setPos(vector);
	 cout << "Done!\n";
	 cout << p->toString() << endl;
	 cout << "Setting position to 70, 70, 0 with setPos(70, 70, 0)...\n";
	 p->setPos(70, 70, 0);
	 cout << "Done!\n";
	 cout << p->toString() << endl;
	 cout << "Shifting position -10, -20, 0 with shiftPos(-10, -20, 0)...\n";
	 p->setPos(-20, -10, 0);
	 cout << "Done!\n";
	 cout << p->toString() << endl;

	 vector[0] = -5;
	 vector[1] = 10;
	 vector[2] = 0;
	 cout << "Shifting position -5, 10, 0 with shiftPos(vector)...\n";
	 p->setPos(vector);
	 cout << "Done!\n";
	 cout << p->toString() << endl;

	 cout << "cleaning up...\n";
	 delete p;
	 cout << "Done!\nGoodbye!\n\n";
	 return 0;
}
