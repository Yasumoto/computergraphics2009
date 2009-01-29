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

/*
 * This is the initialization and camera code
 */

#include "JoeSmith.h"

/*
 * The following are used to control the camera
 */
GLfloat eyeX = -50.0;  
GLfloat eyeY = 20.0;  
GLfloat eyeZ = 0.0;  
GLfloat centerX = 12.0;
GLfloat centerY = -1.0;
GLfloat centerZ = 2.0;
GLfloat upX = 0.0;   
GLfloat upY = 1.0;   
GLfloat upZ = 0.0;;  

float orbit_x = 0.0, orbit_y = 0.0;

float flame = 1.0;

int display_missile = 0;

float missile_distance = 2.5;

int explode_awesomeness = 0;
float explode_x = 0.0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   // Change the light color to white
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

	// The position of the light
	GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };

   glClearColor (0.7, 0.7, 1.0, 0.0);
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
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);

	// For more info on blending, see 231 in
	// the redbook
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
   //glDisable(GL_LIGHTING);
}

/*
 * The display callback
 */
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

	// ta-da!
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); 

	jet();

	glPopMatrix();
	//glTranslatef(10.0, -5.0, 0.0);
	glScalef(0.3, 0.3, 0.3);
	if (explode_awesomeness)
	{
		explosion(explode_x, explode_awesomeness--);
	}
	display_missile = 1;
	if (display_missile)
	{
		glTranslatef(missile_distance+=0.3, 0.0, -25.0);
		missile();
		if (missile_distance >= 700.0)
		{
			explode_x = missile_distance;
			explode_awesomeness = 5;
			missile_distance = 3.0;
			display_missile = 0;
		}
	}

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
	// The kookity camera swing code
	/*if (orbit_x < 360.0)
		orbit_x += 0.001;
	else
		orbit_x = 0.0;
	
	if (orbit_y < 360.0)
		orbit_y += 0.001;
	else
		orbit_y = 0.0;
		
	eyeX = 50.0*cos((float)orbit_x);
	eyeY = 50.0*sin((float)orbit_y);
	*/

	if (flame >= 1.7)
			  flame = 1.0;
	else
			  flame += 0.01;
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
	gluPerspective (45.0, (GLfloat)w/(GLfloat)h, 0.1, 2000.0 ); 
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
		case 'k':
		{
			//glTranslatef(15.0, -5.0, 0.0);
			//glScalef(0.2, 0.2, 0.2);
			display_missile += 1;
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
   glutInitWindowSize (700, 700); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   
	init ();

   glutDisplayFunc(display); 
   glutKeyboardFunc(keys); 
   glutReshapeFunc(reshape);

	int whole_shebang = glutCreateMenu(menu);
		glutAddMenuEntry("Above", 1);
		glutAddMenuEntry("Below", 2);
		glutAddMenuEntry("Side", 3);
	
	glutCreateMenu(menu);
		glutAddSubMenu("Solar System", whole_shebang);
		glutAddMenuEntry("Zoom", 4);
		glutAddMenuEntry("Reset", 5);

   glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
