#include "2DMathLib_Revised.h"
#include <cstdlib>


///////////////////////////////////////////////////////////////
//Point2D 
///////////////////////////////////////////////////////////////
point3D::point3D(){
}
point3D::point3D(float inx, float iny, float inz){
	x = inx;
	y = iny;
	z = inz;
	//vec2D v = vec2D(1,2);
}

void point3D::randPoint(){
	randgen r;
	x = r.randf(500);
	y = r.randf(500);
}

float point3D::getX(){
	return x;
}

float point3D::getY(){
	return y;
}

float point3D::getZ(){
	return z;
}

float point3D::dist(point3D p){
	float xyDist = sqrt (pow(x - p.getX(), 2.0f) + pow(y- p.getY(), 2.0f));
	return sqrt(pow(xyDist, 2.0f) + pow(z - p.getZ(), 2.0f));
}

float point3D::fastDist(point3D q){
	float xyDist = (pow(x - q.getX(), 2.0f) + pow(y- q.getY(), 2.0f));
	return (pow(xyDist, 2.0f) + pow(z-q.getZ(), 2.0f));
}


///////////////////////////////////////////////////////////////
//Vec2D
///////////////////////////////////////////////////////////////
vec3D::vec3D(){}
vec3D::vec3D(float inx, float iny, float inz){
	x = inx;
	y = iny;
	z = inz;
	vMag();
}

vec3D::vec3D(point3D p1, point3D p2){
	x = p2.x-p1.x;
	y = p2.y-p1.y;
	z = p2.z-p1.z;
}

void vec3D::vMag(){
	mag = sqrt( pow(sqrt(pow(x, 2.0f) + pow(y, 2.0f)), 2.0f) + pow(z, 2.0f));
}

vec3D vec3D::vNorm(){		
	//float xNorm, yNorm;
	
	x = x/mag;
	y = y/mag;
	z = z/mag;
	vec3D vec = vec3D(x, y, z);
	return vec;
}

void vec3D::vMult(float s){
	x = s* x;
	y = s* y;
}

vec3D vec3D::createV(point3D p, point3D q){
	float nX, nY, nZ;
	nX = p.x - q.x;
	nY = p.y - q.y;
	nZ = p.z - q.z;

	vec3D vect;
	vect = vec3D(nX, nY, nZ);
	return vect;
}

///////////////////////////////////////////////////////////////
//colour
///////////////////////////////////////////////////////////////
colour::colour(){}
colour::colour(float inr, float ing, float inb){
	r = inr;
	g = ing;
	b = inb;
}

void colour::randColour(){
	randgen q;
	r = q.randf(1.0f);
	g = q.randf(1.0f);
	b = q.randf(1.0f);
}

//////////////////////////////////////////////////////////////
//particle
//////////////////////////////////////////////////////////////
particle::particle(){
	p = point3D(0, 0, 0);
	dir = vec3D(r.randN(0.04),r.randf(0.2),r.randN(0.04));
	rotation = vec3D(r.randf(1), r.randf(1), r.randf(1));
	clr = colour(r.randf(1.0f), r.randf(1.0f), r.randf(1.0f));
	speedX = 10;
	speedZ = 10;
	speedY = 10 + r.randf(10);
	age = 0;
	
}

void particle::moveP(){
	p.x = p.x + speedX * dir.x;		// x = x + vector x
	p.y = p.y + speedY * dir.y;
	p.z = p.z + speedZ * dir.z;
}

void particle::changeDir(point3D pCursor){
	vec3D vect = dir.createV(pCursor, p);
	vect.vNorm();
	vect.x = (vect.x)/100;
	vect.y = (vect.y)/100;
	vect.z = (vect.z)/100;
	dir.x = vect.x;
	dir.y = vect.y;
	dir.z = vect.z;
}

////////////////////////////////////////////////////////////////////////////
//randgen
///////////////////////////////////////////////////////////////////////



//returns a float value: 0 to temp
float randgen::randf(float temp){
	return temp*(float)rand()/RAND_MAX;
}

//returns a float: -temp to temp
float randgen::randN(float temp){
	return ((2*(float)rand() - RAND_MAX)/RAND_MAX) * randf(temp);
}

/////////////////////////////////////////////////////////////////////////////////
// Plane
/////////////////////////

plane::plane(point3D ina, point3D inb, point3D inc, point3D ind){
	a = ina;
	b = inb;
	c = inc;
	d = ind;

}
