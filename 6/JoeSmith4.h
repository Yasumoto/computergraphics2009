/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/16/09
 *
 * Assignment 4
 * Header file
 * Intro to 3D
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

// How far to go with recursive points
#define DEPTH 5000
