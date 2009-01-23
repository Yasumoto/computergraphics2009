/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/16/09
 *
 * Assignment 4 
 * Intro to 3D
 *
 */

/* Based off light.c from the redbook */

#include <GL/glut.h>
#include <stdlib.h>
// The position of the light to change.
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   // Change the light color to blue
   GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_COLOR_MATERIAL);

   // Specifies material info for lighting
   // Changed to diffuse lighting
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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
   // update the lighting
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   // this sure makes life easy
   glutSolidTeapot (0.80);
   glFlush ();
   // Never forget to swap buffers when GL_DOUBLE
   // is on
   glutSwapBuffers();
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
 * The keyboard callback function
 */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'u':
      {
	 light_position[1] += 0.1;
	 display();
         break;
      }
      case 'd':
      {
	 light_position[1] -= 0.1;
	 display();
         break;
      }
// vi controls ftw
      case 'k':
      {
	 light_position[1] += 0.1;
	 display();
         break;
      }
      case 'j':
      {
	 light_position[1] -= 0.1;
	 display();
         break;
      }
      case 'l':
      {
	 light_position[0] += 0.1;
	 display();
         break;
      }
      case 'h':
      {
	 light_position[0] -= 0.1;
	 display();
         break;
      }
      // hooray reset :)
      case 'r':
      {
	 light_position[0] = 1.0 ;
	 light_position[1] = 1.0 ;
	 display();
         break;
      }
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
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
