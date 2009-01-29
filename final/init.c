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

float side = 1.0;

/* Image type - contains height, width, and data * One of the contributions from http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06
 */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;
/* storage for one texture  */
int texture[1];

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    //TODO: Yeah, this probably isn't right......
    image->sizeX = 64;
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}
    
// Load Bitmaps And Convert To Textures
void LoadGLTextures() {	
    // Load Texture
    Image *image1;
    
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("linux.bmp", image1)) {
	exit(1);
    }        

    // Create Texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
};


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

   glClearColor (0.7, 0.7, 1.0, 0.1);
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
			display_missile = 1;
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
					eyeZ = 200.0;
					break;
			  }
			  //Below
			  case 2:
			  {
					eyeX = 0.0;
					eyeY = 0.0;
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
			  //Zoom
			  case 4:
			  {    
					eyeY += 150.0;
					break;
			  }
			  //Reset
			  case 5:
			  {
					eyeX = -50.0;
					eyeY = 20.0;
					eyeZ = 0.0;   
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
	glutMouseFunc(clicks);
   glutReshapeFunc(reshape);

	int whole_shebang = glutCreateMenu(menu);
		glutAddMenuEntry("Starboard", 1);
		glutAddMenuEntry("Port", 2);
		glutAddMenuEntry("Front", 3);
	
	glutCreateMenu(menu);
		glutAddSubMenu("Jet Views", whole_shebang);
		glutAddMenuEntry("Move Above", 4);
		glutAddMenuEntry("Reset", 5);

   glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutIdleFunc(idle);

   glutMainLoop();
   return 0;
}
