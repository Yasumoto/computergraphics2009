/* Computer Graphics 360
 * Chapman University
 * Joe Smith
 * 0949140
 * 01/22/09
 *
 * Assignment 6
 * Header file
 * The Solar System
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

#define MERCURY_SIZE 0.03, 0.03, 0.03  
#define MERCURY_DISTANCE 4.16 

#define VENUS_SIZE 0.08, 0.08, 0.08
#define VENUS_DISTANCE 7.76

#define EARTH_SIZE 0.09, 0.09, 0.09
#define EARTH_DISTANCE 10.74

#define MARS_SIZE 0.04, 0.04, 0.04
#define MARS_DISTANCE 16.36

#define JUPITER_SIZE 0.1, 0.1, 0.1
#define JUPITER_DISTANCE 55.89

#define SATURN_SIZE 0.083, 0.083, 0.083
#define SATURN_DISTANCE 102.56

#define URANUS_SIZE 0.03, 0.03, 0.03
#define URANUS_DISTANCE 206.21

#define NEPTUNE_SIZE 0.03, 0.03, 0.03
#define NEPTUNE_DISTANCE 323.29

void mercury();
void venus();
void earth();
void mars();
void jupiter();
void saturn();
void uranus();
void neptune();
