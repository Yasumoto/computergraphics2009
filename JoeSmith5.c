/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/21/09
 *
 * Assignment 5 
 * 3d Cube Fun
 *
 */

#include "JoeSmith.h"

GLfloat x_rot = 1.0, y_rot = 0.0, z_rot = 0.0;
GLfloat rotated = 0.0;


/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   // Change the light color to white
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

	// The position of the light
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

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

	glutSolidCube(1);

   glFlush ();
   // Never forget to swap buffers when GL_DOUBLE
   // is on
   glutSwapBuffers();
}

void idle()
{
	//glRotatef((rotated+=1.0)%360.0, x_rot, y_rot, z_rot);
	display();
}

/*
 * the reshape callback function
 * Does some things with GL_PROJECTION
 * and GL_MODELVIEW which I still
 * don't fully understand yet, but it works.
 */
void reshape (int w, int h)
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
   glLoadIdentity();
}

/* 
 * The menu option
 */ 
void menu_choice(GLint selected)
{
	switch(selected)
	{
		case TWO: 
		{
			glScalef(2.0, 2.0, 2.0);
			display();
			break;
		}
		case HALF: 
		{
			glScalef(0.5, 0.5, 0.5); 
			display();
			break;
		}

		case UP: break;
		case DOWN: break;
		case LEFT: break;
		case RIGHT: break;

		case X: x_rot = 1.0, y_rot = 0.0, z_rot = 0.0; break;
		case Y: x_rot = 0.0, y_rot = 1.0, z_rot = 0.0; break;
		case Z: x_rot = 0.0, y_rot = 0.0, z_rot = 1.0; break;
	}
}

int main(int argc, char** argv)
{
	int scale, translate, rotate, menu;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   
	init ();

	scale = glutCreateMenu(menu_choice);
		glutAddMenuEntry("2", TWO);
		glutAddMenuEntry("0.5", HALF);
	translate = glutCreateMenu(menu_choice);
		glutAddMenuEntry("Up", UP);
		glutAddMenuEntry("Down", DOWN);
		glutAddMenuEntry("Left", LEFT);
		glutAddMenuEntry("Right", RIGHT);
	rotate = glutCreateMenu(menu_choice);
		glutAddMenuEntry("X", X);
		glutAddMenuEntry("Y", Y);
		glutAddMenuEntry("Z", Z);
	
	menu = glutCreateMenu(menu_choice);
		glutAddSubMenu("Scale", scale);
		glutAddSubMenu("Translate", translate);
		glutAddSubMenu("Rotate", rotate);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
