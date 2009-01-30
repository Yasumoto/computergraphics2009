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

#define LEFT 	25
#define RIGHT 	27
#define UP	26
#define DOWN	28

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

float side = 1.0;

float x_move = 0.0, z_move = 0.0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
    LoadGLTextures();// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);// Enable Texture Mapping
   // Change the light color to white
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

	// The position of the light
	GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };

   glClearColor (1.0, 1.0, 1.0, 1.0);
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

	// For more info on blending, see 231 in
	// the redbook
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
   //glDisable(GL_LIGHTING);
}

void write_stroke(char* write)
{
	while (*write)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *write++);
}


void show_ready()
{
	glPushMatrix();
	//glLoadIdentity();
	
	glTranslatef(-25.0, 0.0, 5.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.01, 0.01, 0.01);

	char* ready = "Ready!";
	glColor3f(RED);
	write_stroke(ready);
	glPopMatrix();
}

void skyworld()
{
	glPushMatrix();
   glDisable(GL_LIGHTING);
	glScalef(1000.0, 1000.0, 1000.0);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, skybox[4]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   
   // Front Face (note that the texture's corners have to match the quad's corners)
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
   glEnd();                                    // done with the polygon.
   
	glBindTexture(GL_TEXTURE_2D, skybox[0]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   // Back Face
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
   glEnd();                                    // done with the polygon.
	
	glBindTexture(GL_TEXTURE_2D, skybox[5]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   // Top Face
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
   glEnd();                                    // done with the polygon.
   
	glBindTexture(GL_TEXTURE_2D, skybox[1]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   // Bottom Face       
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
   glEnd();                                    // done with the polygon.
   
	glBindTexture(GL_TEXTURE_2D, skybox[3]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   // Right face
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
   glEnd();                                    // done with the polygon.
   
	glBindTexture(GL_TEXTURE_2D, skybox[2]);
   glBegin(GL_QUADS);		                // begin drawing a cube
   // Left Face
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
   
   glEnd();                                    // done with the polygon.
   glEnable(GL_LIGHTING);
	glPopMatrix();
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

	skyworld();

	glPushMatrix();
	//y_move += 0.1;
	//x_move += 0.1;
        glRotatef(x_move, 1.0, 0.0, 0.0);
        glRotatef(z_move, 0.0, 0.0, 1.0);

	jet();

	glPopMatrix();
	glPopMatrix();
	if (!display_missile && eyeX == -50.0 && eyeY == 20.0)
		show_ready();
	//glTranslatef(10.0, -5.0, 0.0);
	glScalef(0.3, 0.3, 0.3);
	if (explode_awesomeness)
	{
		explosion(explode_x, explode_awesomeness--);
	}
	if (display_missile)
	{
		glTranslatef(missile_distance+=0.3, 0.0, side*25.0);
		missile();
		if (missile_distance >= 700.0)
		{
			explode_x = missile_distance;
			explode_awesomeness = 500;
			missile_distance = 3.0;
			display_missile = 0;
			side *= -1.0;
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
	gluPerspective (45.0, (GLfloat)w/(GLfloat)h, 0.1, 4000.0 ); 
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
			display_missile = 1;
			break;
		} 
		case GLUT_KEY_UP:
		{
			z_move += 2.1;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			z_move -= 2.1;
			break;
		}
		case GLUT_KEY_LEFT:
		{
			x_move -= 2.1;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			x_move += 2.1;
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
					eyeY = 35.0;
					eyeZ = 200.0;
					break;
			  }
			  //Below
			  case 2:
			  {
					eyeX = 0.0;
					eyeY = 35.0;
					eyeZ = -200.0;
					break;
			  }
			  //Side
			  case 3:
			  {
					eyeX = 120.0;
					eyeY = 0.0;
					eyeZ = 0.0;
					break;
			  }
			  //Up
			  case 4:
			  {    
					eyeY += 150.0;
					break;
			  }
			  //Down
			  case 5:
			  {    
					eyeY -= 150.0;
					break;
			  }
			  //Reset
			  case 6:
			  {
					eyeX = -50.0;
					eyeY = 20.0;
					eyeZ = 0.0;   
					x_move = 0.0;
					z_move = 0.0;
					break;
			  }
	}
}

void clicks(int button, int state, int x, int y)
{
		  if(button == GLUT_LEFT_BUTTON)
					 display_missile = 1;
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
	glutSpecialFunc(keys);
	glutMouseFunc(clicks);
   glutReshapeFunc(reshape);

	int whole_shebang = glutCreateMenu(menu);
		glutAddMenuEntry("Starboard", 1);
		glutAddMenuEntry("Port", 2);
		glutAddMenuEntry("Front", 3);
	
	glutCreateMenu(menu);
		glutAddSubMenu("Jet Views", whole_shebang);
		glutAddMenuEntry("Move Up", 4);
		glutAddMenuEntry("Move Down", 5);
		glutAddMenuEntry("Reset", 6);

   glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
