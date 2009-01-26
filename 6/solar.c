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
GLfloat eyeY = 0.0;  
GLfloat eyeZ = 1.0;  
GLfloat centerX = 0.0;
GLfloat centerY = 1.0;
GLfloat centerZ = 0.0;
GLfloat upX = 1.0;   
GLfloat upY = 0.0;   
GLfloat upZ = 0.0;;  

GLfloat x_rot = 1.0, y_rot = 0.0, z_rot = 0.0;

GLint earth_rotate = 0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
	GLfloat h = 100.0, w = 100.0;
	glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
 		1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   glMatrixMode (GL_MODELVIEW);
	
   // Change the light color to white
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

	// The position of the light
	GLfloat light_position[] = { 5.0, 1.0, 1.0, 0.0 };


   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
	
   glEnable(GL_COLOR_MATERIAL);

   // Specifies material info for lighting
   // Changed to diffuse lighting
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
   // update the lighting
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);


   // Turn on GL settings
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

/*
 * The relatively simply display callback
 */
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*
	glPushMatrix();
*/
	gluLookAt(eyeX, 
				 eyeY, 
				 eyeZ, 
				 centerX, 
				 centerY, 
				 centerZ, 
				 upX, 
				 upY, 
				 upZ);
/*
	glPopMatrix();
*/

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutWireSphere((GLdouble) 1.0, (GLint)50, (GLint)50);
	glPopMatrix();

	earth();


   glFlush ();
   // Never forget to swap buffers when GL_DOUBLE
   // is on
   glutSwapBuffers();
}

void earth()
{
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef((GLfloat)earth_rotate, 0.0, 0.0);
	glutWireSphere((GLdouble) 0.5, (GLint)50, (GLint)50);
	glPopMatrix();
}

void idle()
{
	//earth_rotate = (earth_rotate + 1) % 360;
	//display();
}

/*
 * the reshape callback function
 * Does some thngs with GL_PROJECTION
 * and GL_MODELVIEW which I still
 * don't fully understand yet, but it works.
 */
/*void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}*/

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   
	init ();

   glutDisplayFunc(display); 
   //glutReshapeFunc(reshape);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
