/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/26/09
 *
 * Final Project
 * Jets
 *
 */

#include "JoeSmith.h"

/*
 * The following are used to control the camera
 */
GLfloat eyeX = 0.0;  
GLfloat eyeY = 20.0;  
GLfloat eyeZ = 5.0;  
GLfloat centerX = 0.0;
GLfloat centerY = 0.0;
GLfloat centerZ = 0.0;
GLfloat upX = 0.0;   
GLfloat upY = 1.0;   
GLfloat upZ = 0.0;;  

GLfloat x_rot = 1.0, y_rot = 0.0, z_rot = 0.0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
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

	// ta-da!
	glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); 

	//The Sun
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glRotatef(rotation, 0.0, 1.0, 0.0);
   glDisable(GL_LIGHTING);
	glutSolidSphere((GLdouble) 2.0, (GLint)20, (GLint)20);
	glPopMatrix();
   glEnable(GL_LIGHT1);

   glFlush ();
   // Never forget to swap buffers when GL_DOUBLE
   // is on
   glutSwapBuffers();
}

/*
 * Idle function
 */
void idle()
{
	display();
}

/*
 * the reshape callback function
 * set up the view window
 */
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
	gluPerspective (45.0, (GLfloat)w/(GLfloat)h, 0.1, 200.0 ); 
   glMatrixMode(GL_MODELVIEW);
}

/*
 * Set up q to quit, for convenience
 */
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

/*
 * The menu to view different angles
 */
void menu(GLint selected)
{
	switch(selected)
	{
			  //Above
			  case 1:
			  {
					eyeX = 0.0;
					eyeY = 0.0;
					eyeZ = 25.0;
					break;
			  }
			  //Below
			  case 2:
			  {
					eyeX = 0.0;
					eyeY = 0.0;
					eyeZ = -25.0;
					break;
			  }
			  //Side
			  case 3:
			  {
					eyeX = 20.0;
					eyeY = 0.0;
					eyeZ = 0.0;
					break;
			  }
			  //Zoom
			  case 4:
			  {    
					eyeY -= 10.0;
					break;
			  }
			  //Reset
			  case 5:
			  {
					eyeX = 0.0;
					eyeY = 20.0;
					eyeZ = 5.0;   
					break;
			  }
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   
	init ();

   glutDisplayFunc(display); 
   glutKeyboardFunc(keys); 
   glutReshapeFunc(reshape);

	/*int whole_shebang = glutCreateMenu(menu);
		glutAddMenuEntry("Above", 1);
		glutAddMenuEntry("Below", 2);
		glutAddMenuEntry("Side", 3);
	
	glutCreateMenu(menu);
		glutAddSubMenu("Solar System", whole_shebang);
		glutAddMenuEntry("Zoom", 4);
		glutAddMenuEntry("Reset", 5);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
	*/

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
