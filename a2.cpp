/**
Edward Guloien	0749435		CS 3GC3		Dr. Teather		Assignment #2

Uses winds and lighting.
**/

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include "2DMathLib_Revised.h"


// Declaration of vector of particles
std::vector<particle> particles;
int numParticles = 25;

//rotation angle of particles
float rot = 0;	


// toggle flags
static bool paused = false;
static bool bounceFriction = true;

//toggle winds
float westerly, easterly, southernly, northernly = false;

//Camera setup
Camera camera;
float ang = 0;
float ang2 = 0;

//Cannon angle setup
float cannonAngX = 0;
float cannonAngZ = 0;

// lighting properties
float light_pos[] = {50.0, 200.0, 50.0, 1.0};		//coord w: 1.0
float amb0[4] = {1,1,1,1};
float diff0[4] = {1,1,1,1};
float spec0[4] = {1,1,1,1};

float m_amb[] = {0.33f,0.22f, 0.03f, 1.0f};
float m_diff[] = {0.2f,0.22f, 0.03f, 1.0f};
float m_spec[] = {0.25f,0.22f, 0.03f, 1.0f};
float m_shiney = 1.0f;		// shiney, 1 -> 100, not shiney


//buildVector. populates the vector with particles
void buildVector(){
	int i;
	std::vector<particle>::iterator it;

	for (i = 0; i < numParticles; i++){
		it = particles.begin();
		particles.insert (it, particle());

		
	}

}
//addParticle. sprays out more particles 
void particleSpray(){
	buildVector();
}

//add 10 particles to spray
void addParticle(){
	numParticles = numParticles + 10;
}

//remove 10 particles from spray
void removeParticle(){
	if (numParticles > 10){
		numParticles = numParticles - 10;
	}
}

//drawPlane. Draws the plane that particles will bounce on.
void drawPlane(){
	point3D a = point3D(100, 0, 100);	//3dpoints
	point3D b = point3D(100, 0, -100);
	point3D c = point3D(-100, 0, -100);
	point3D d = point3D(-100, 0, 100);
	
	plane ground = plane(a,b,c,d);		
	glColor3f(0.25, 0.25, 0.25);
	glBegin(GL_POLYGON);
		glVertex3f(ground.a.x, ground.a.y, ground.a.z);
		glVertex3f(ground.b.x, ground.b.y, ground.b.z);
		glVertex3f(ground.c.x, ground.c.y, ground.c.z);
		glVertex3f(ground.d.x, ground.d.y, ground.d.z);
	glEnd();
}


//restart. resets the animation.
void restart(){
	particles.clear();
	particleSpray();
}

//initComments prints keystrokes for interaction
void initComments(){
	std::cout << std::endl << std::endl << "---------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl << std::endl;
	std::cout << "This is the particle geyser." << std::endl;
	std::cout << "You can control the geyser by keystroke:" << std::endl;
	std::cout << "x:\tMakes your geyser spray 3D particles." << std::endl;
	std::cout << "z:\tAdds particles to your spray." << std::endl;
	std::cout << "c:\tDecreases particles per spray (but can't drop below 5)." << std::endl;
	std::cout << "f:\tToggles friction mode (its already on)." << std::endl;
	std::cout << "h:\tPrint this help menu again." << std::endl;
	std::cout << "q:\tQuit" << std::endl;
	std::cout << "space:\tPauses the animation." << std::endl << std::endl;
	std::cout << " W, E, S, N :\tToggles winds." << std::endl;
	std::cout << "Arrows:\tPan your camera around the scene." << std::endl << std::endl << std::endl;
	std::cout << "Hold x for magical fun!." << std::endl;
	std::cout << "You begin facing West." << std::endl;
}

//kbd. Handles toggle switching system settings with regular keys. 
void kbd(unsigned char key, int x, int y){
	if (key == 'q'|| key == 'Q'){
		exit(0);
	}
	
	if (key == 'r'|| key == 'R'){
		restart();
	}

	if (key == ' '){
		paused = !paused;
		if(paused == true){
		std::cout << "The animation is paused" << std::endl;
		}
		else{ std::cout <<"The animation is running!" << std::endl;}
	}

	if (key == 'z' || key == 'Z'){
		addParticle();
	}

	if (key == 'x' || key == 'X'){
		particleSpray();
	}

	if (key == 'c' || key == 'C'){
		removeParticle();
	}

//Wind toggles
	if (key == 'w' || key == 'W'){
		westerly = !westerly;
		if(westerly == true){
		std::cout << "There's a western wind!" << std::endl;
		}
		else{ std::cout <<"The western wind has died down." << std::endl;}
	}

	if (key == 'e' || key == 'E'){
		easterly = !easterly;
		if(easterly == true){
		std::cout << "There's an eastern wind!" << std::endl;
		}
		else{ std::cout <<"The eastern wind has died down." << std::endl;}
	}

	if (key == 's' || key == 'S'){
		southernly = !southernly;
		if(southernly == true){
		std::cout << "There's a southernly wind!" << std::endl;
		}
		else{ std::cout << "The southernly wind has died down." << std::endl;}
	}

	if (key == 'n' || key == 'N'){
		northernly = !northernly;
		if(northernly == true){
		std::cout << "There's a northernly wind!" << std::endl;
		}
		else{ std::cout <<"The northernly wind has died down." << std::endl;}
	}
//Friction
	if (key == 'f'){
		bounceFriction = !bounceFriction;
		if(bounceFriction == true){
		std::cout << "Bounce friction has been turned on" << std::endl;
		}
		else{ std::cout <<"Bounce friction has been turned off." << std::endl;}
	}

//as close as you'll get to a help menu toggler
	if (key == 'h'){
		initComments();
	}
}

//Special. Handles rotation interaction of arrow keys
void special(int key, int x, int y){
	switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
  }
	glutPostRedisplay();
}

//Render. draws cube at point location.
void render(){
	glMatrixMode(GL_MODELVIEW);
	
	//cannon rendering - Reminants from cannon that was aesthetically functional, but physcially not.
	glPushMatrix();
	glColor3f(.25,.5,.75);
	glTranslatef(0,4,0);
	glRotatef(90, 1,0,0);
	glRotatef(cannonAngX, 1, 0, 0);
	glRotatef(cannonAngZ, 0, 1, 0);
	glutSolidCone(5,10,5,1);
	glPopMatrix();

	//particle rendering
	int j;
	for(j=0; j<particles.size(); j++){
		glPushMatrix();
		glColor3f(particles[j].clr.r,particles[j].clr.g,particles[j].clr.b);
		glTranslatef(particles[j].p.x, particles[j].p.y, particles[j].p.z);
		glRotatef(rot,particles[j].rotation.x, particles[j].rotation.y, particles[j].rotation.z);
		glutSolidCube(3);
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}

//Update particle fields for each particle. Sends to rendering function.
void updateAll(){
	int j;
	for(j=0; j<particles.size(); j++){
		particles[j].moveP();								
		particles[j].speedY = particles[j].speedY - .1f;	//gravity
		particles[j].age++;									//aging
		rot = rot + 0.1;									//spinning
		
		//wind updates
		if(westerly == true){
			particles[j].p.x = particles[j].p.x - 1.0f;}
		if(easterly == true){
			particles[j].p.x = particles[j].p.x + 1.0f;}
		if(northernly == true){
			particles[j].p.z = particles[j].p.z - 1.0f;}
		if(southernly == true){
			particles[j].p.z = particles[j].p.z + 1.0f;}

		//plane physics -- bounce
		if((particles[j].p.y < 0) && (particles[j].p.x < 100 && particles[j].p.x > -100) && ( particles[j].p.z < 100 && particles[j].p.z > -100)){
			particles[j].speedY = -particles[j].speedY;
			if(bounceFriction == true ){
				particles[j].speedY = particles[j].speedY * 0.5f;
				
				if(particles[j].p.y < 0){
				particles[j].p.y = -particles[j].p.y;
				}
				
			}
		}
		//age: death predictor
		if (particles[j].age >= 1200 ){
				particles.pop_back ();
			}
	}

	void render();
}



// Idle. Sends to update when not paused.
void idle(){
	if(!paused){
	updateAll();
	}

	glutPostRedisplay();
}


// display. Sets lighting conditions, camera positions...
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0 );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shiney);

	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	drawPlane();
	
	render();
}



//Main: Initializing procedures
int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(700,100);
	glutCreateWindow("particle fountain");	//creates the window
	
	initComments();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);		//disregards face colour during drawing
	glEnable(GL_LIGHT0);			//because we're going to use materials
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150, 150,-150, 150, -150, 150);
	glRotatef(10, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	
	buildVector();
	glutSpecialFunc(special);
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();		
	
	return 0;			
}

