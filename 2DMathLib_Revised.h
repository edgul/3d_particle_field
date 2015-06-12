#ifndef _H_2DMATHLIB_H_	
#define _H_2DMATHLIB_H_
#include <math.h>

class randgen{
public:
	float randf(float temp);
	float randN(float temp);
};

class point3D{
public:								
	float x, y, z;
	point3D();							
	point3D(float inx, float iny, float inz);
	void randPoint();
	float getX(), getY(), getZ();
	float dist(point3D q);
	float fastDist(point3D q);		
	
};

class vec3D{
public:
	float x, y, z, mag;
	vec3D();								
	vec3D(float inx, float iny, float inz);
	vec3D(point3D p1, point3D p2); 
	void vMag();
	vec3D vNorm();
	void vMult(float s);
	vec3D createV(point3D p, point3D q);	
};


class colour{
public:
	float r, g, b;
	colour();
	colour(float Inr, float Ing, float Inb);
	void randColour();
};



class particle{
public:
	point3D p;
	vec3D dir;
	vec3D rotation;
	colour clr;
	randgen r;
	float speedX, speedY, speedZ, age;
	
	
	particle();
	void moveP();
	void changeDir(point3D p);
};
	
class plane{
public:
	point3D a, b, c, d;
	colour clr;
	plane(point3D ina, point3D inb, point3D inc, point3D ind);

};

// A camera.  Code borrowed from http://cs.lmu.edu/~ray/notes/openglexamples/
//It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.
class Camera {
  double theta;      // determines the x and z positions
  double y;          // the current y position
  double dTheta;     // increment in theta for swinging the camera around
  double dy;         // increment in y for moving the camera up/down
public:
  Camera(): theta(0), y(3), dTheta(0.04), dy(0.2) {}
  double getX() {return 10 * cos(theta);}
  double getY() {return y;}
  double getZ() {return 10 * sin(theta);}
  void moveRight() {theta += dTheta;}
  void moveLeft() {theta -= dTheta;}
  void moveUp() {y += dy;}
  void moveDown() {if (y > dy) y -= dy;}
};


#endif
