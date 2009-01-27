/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/22/09
 *
 * Assignment 6 
 * The Solar System
 *
 */

#include "JoeSmith.h"
GLfloat eyeX = 0.0;  
GLfloat eyeY = 3.0;  
GLfloat eyeZ = 2.0;  
GLfloat centerX = 0.0;
GLfloat centerY = 0.0;
GLfloat centerZ = 0.0;
GLfloat upX = 0.0;   
GLfloat upY = 1.0;   
GLfloat upZ = 0.0;;  

GLfloat x_rot = 1.0, y_rot = 0.0, z_rot = 0.0;

GLfloat rotation = 0.0;

GLfloat mercury_orbit = 0.0;
GLfloat venus_orbit = 0.0;
GLfloat earth_orbit = 0.0;
GLfloat mars_orbit = 0.0;
GLfloat jupiter_orbit = 0.0;
GLfloat saturn_orbit = 0.0;
GLfloat uranus_orbit = 0.0;
GLfloat neptune_orbit = 0.0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
	//GLfloat h = 100.0, w = 100.0;
	//glOrtho (-10.0, 10.0, -2.0*(GLfloat)h/(GLfloat)w,
 	//		2.0*(GLfloat)h/(GLfloat)w, -2.0*(GLfloat)h/(GLfloat)w, -2.0*(GLfloat)h/(GLfloat)w);
   //glMatrixMode (GL_MODELVIEW);
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); 
	//gluPerspective ( fovy, aspect, zNear, zFar ); 
   //glLoadIdentity();
	//gluPerspective (20.0, 1.0, 1.0, 100.0 );

   // Change the light color to white
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

	// The position of the light
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

	GLfloat light_position2[] = { 1.0, 1.0, 0.0, 1.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
	
   glEnable(GL_COLOR_MATERIAL);

   // Specifies material info for lighting
   // Changed to diffuse lighting
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
   // update the lighting
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);


   // Turn on GL settings
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
}

/*
 * The display callback
 */
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //glMatrixMode (GL_PROJECTION);
   //glLoadIdentity();
	//gluPerspective (2.0, 1.0, 1.0, 1.0 );

	glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); 

	//The Sun
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(0.01, 0.01, 0.01);
	glRotatef(rotation, 0.0, 1.0, 0.0);
   glDisable(GL_LIGHTING);
	glutSolidSphere((GLdouble) 2.0, (GLint)20, (GLint)20);
	glPopMatrix();
   glEnable(GL_LIGHT1);

	mercury();
	venus();
	earth();
	mars();
	jupiter();
	saturn();
	uranus();
	neptune();


   glFlush ();
   // Never forget to swap buffers when GL_DOUBLE
   // is on
   glutSwapBuffers();
}


void mercury()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScalef(MERCURY_SIZE);
	glTranslatef(EARTH_DISTANCE*cos((float)mercury_orbit), EARTH_DISTANCE*sin((float)mercury_orbit), 0.0);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void venus()
{
	glPushMatrix();
	glColor3f(1.0, 0.0555555, 0.0);
	glScalef(VENUS_SIZE);
	glTranslatef(VENUS_DISTANCE*cos((float)venus_orbit), VENUS_DISTANCE*sin((float)venus_orbit), 0.0);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void earth()
{
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(EARTH_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(EARTH_DISTANCE*cos((float)earth_orbit), EARTH_DISTANCE*sin((float)earth_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void mars()
{
	glPushMatrix();
	glColor3f(1.0, 0.01, 0.0);
	glScalef(MARS_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(MARS_DISTANCE*cos((float)mars_orbit), MARS_DISTANCE*sin((float)mars_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void jupiter()
{
	glPushMatrix();
	glColor3f(1.0, 5.0, 0.0);
	glScalef(JUPITER_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(JUPITER_DISTANCE*cos((float)jupiter_orbit), JUPITER_DISTANCE*sin((float)jupiter_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void saturn()
{
	glPushMatrix();
	glColor3f(5.0, 1.0, 0.0);
	glScalef(SATURN_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(SATURN_DISTANCE*cos((float)saturn_orbit), SATURN_DISTANCE*sin((float)saturn_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void uranus()
{
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glScalef(URANUS_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(URANUS_DISTANCE*cos((float)uranus_orbit), URANUS_DISTANCE*sin((float)uranus_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void neptune()
{
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(NEPTUNE_SIZE);
	glRotatef(0.0, 1.0, 0.0, rotation);
	glTranslatef(NEPTUNE_DISTANCE*cos((float)neptune_orbit), NEPTUNE_DISTANCE*sin((float)neptune_orbit), 0.0);
	glutSolidSphere((GLdouble) 0.5, (GLint)20, (GLint)20);
	glPopMatrix();
}

void orbits()
{
	mercury_orbit = (mercury_orbit + 0.005);
	if (mercury_orbit >= 360.0)
	{
		mercury_orbit = 0.0;
	}

	venus_orbit = (venus_orbit + 0.003);
	if (venus_orbit >= 360.0)
	{
		venus_orbit = 0.0;
	}

	earth_orbit = (earth_orbit + 0.002);
	if (earth_orbit >= 360.0)
	{
		earth_orbit = 0.0;
	}

	mars_orbit = (mars_orbit + 0.001);
	if (mars_orbit >= 360.0)
	{
		mars_orbit = 0.0;
	}

	jupiter_orbit = (jupiter_orbit + 0.0009);
	if (jupiter_orbit >= 360.0)
	{
		jupiter_orbit = 0.0;
	}

	saturn_orbit = (saturn_orbit + 0.0008);
	if (saturn_orbit >= 360.0)
	{
		saturn_orbit = 0.0;
	}

	uranus_orbit = (uranus_orbit + 0.0007);
	if (uranus_orbit >= 360.0)
	{
		uranus_orbit = 0.0;
	}

	neptune_orbit = (neptune_orbit + 0.0006);
	if (neptune_orbit >= 360.0)
	{
		neptune_orbit = 0.0;
	}
}
void idle()
{
	rotation += 0.01;
	orbits();
	display();
}

/*
 * the reshape callback function
 * Does some thngs with GL_PROJECTION
 * and GL_MODELVIEW which I still
 * don't fully understand yet, but it works.
 */
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
	gluPerspective (45.0, (GLfloat)w/(GLfloat)h, 0.1, 200.0 ); 
   /*if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);*/
   glMatrixMode(GL_MODELVIEW);
}

void keys(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		{
			exit(0);
			break;
		} 
	}
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1200, 1200); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   
	init ();

   glutDisplayFunc(display); 
   glutKeyboardFunc(keys); 
   glutReshapeFunc(reshape);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
