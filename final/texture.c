#include "JoeSmith.h"

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
int skybox[6];

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(char *filename, Image *image, int x, int y) {
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
    image->sizeX = x;
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    image->sizeY = y;
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;
    //printf("%d\n", size);

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

    Image *sky1;
    sky1 = (Image *) malloc(sizeof(Image));
    if (sky1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    Image *sky2;
    sky2 = (Image *) malloc(sizeof(Image));
    if (sky2 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    Image *sky3;
    sky3 = (Image *) malloc(sizeof(Image));
    if (sky3 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    Image *sky4;
    sky4 = (Image *) malloc(sizeof(Image));
    if (sky4 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    Image *sky5;
    sky5 = (Image *) malloc(sizeof(Image));
    if (sky5 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    Image *sky6;
    sky6 = (Image *) malloc(sizeof(Image));
    if (sky6 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("images/linux.bmp", image1, 64, 128)) {
	exit(1);
    }        
    // Create Texture	
    glGenTextures(1, &texture[0]);
    
    if (!ImageLoad("images/skybk.bmp", sky1, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[0]);

    if (!ImageLoad("images/skydn.bmp", sky2, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[1]);
    
    if (!ImageLoad("images/skyft.bmp", sky3, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[2]);
    
    if (!ImageLoad("images/skylf.bmp", sky4, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[3]);
    
    if (!ImageLoad("images/skyrt.bmp", sky5, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[4]);
    
    if (!ImageLoad("images/skyup.bmp", sky6, 512, 512)) {
	exit(1);
    }        
    glGenTextures(1, &skybox[5]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

    glBindTexture(GL_TEXTURE_2D, skybox[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky1->sizeX, sky1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky1->data);

    glBindTexture(GL_TEXTURE_2D, skybox[1]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky2->sizeX, sky2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky2->data);

    glBindTexture(GL_TEXTURE_2D, skybox[2]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky3->sizeX, sky3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky3->data);

    glBindTexture(GL_TEXTURE_2D, skybox[3]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky4->sizeX, sky4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky4->data);

    glBindTexture(GL_TEXTURE_2D, skybox[4]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky5->sizeX, sky5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky5->data);

    glBindTexture(GL_TEXTURE_2D, skybox[5]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sky6->sizeX, sky6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, sky6->data);

};
