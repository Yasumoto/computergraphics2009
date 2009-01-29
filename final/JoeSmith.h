/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/26/09
 *
 * Final Project
 * Header file
 * Jets
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define WIDTH 1.0

#define RED 1.0, 0.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0
//Used for glClearColor
#define WHITE 1.0, 1.0, 1.0, 0.0
#define BLACK 0.0, 0.0, 0.0, 0.0

#define WINDOW_WIDTH WIDTH
#define WINDOW_HEIGHT HEIGHT

extern float flame;
extern float side;

extern int texture[1];
extern int skybox[6];
