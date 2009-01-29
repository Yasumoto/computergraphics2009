/*
 * The code for drawing a jet
 */

#include "JoeSmith.h"

/*
 * To make a cylinder, one must work with quadrics.
 * See page 516 in the red book.
 */
void fuselage()
{
	glPushMatrix();
	glRotatef(-90, 0.0, 1.0, 0.0);
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluCylinder(qobj, 1.0, 1.0, 10.0, 15, 15);
	glPopMatrix();
}

void nose()
{
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	double base = 1.0, height = 2.0;
	int slices = 10, stacks = 10;
	glutSolidCone((GLdouble) base, (GLdouble) height, (GLint) slices, (GLint) stacks);
	glPopMatrix();
}

void flames()
{
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 9.5);

	double base = 0.8, height = 3.0;
	int slices = 10, stacks = 10;
	glutSolidCone((GLdouble) base, (GLdouble) height*flame, (GLint) slices, (GLint) stacks);

	glEnable(GL_BLEND);
	glColor4f(1.0,1.0,0.0,0.8);
	glutSolidCone((GLdouble) base+0.2, (GLdouble) (height+0.8)*flame, (GLint) slices, (GLint) stacks);
	glDisable(GL_BLEND);
	//glColor4f(1.0,1.0,0.0,1.0);
}


void wing()
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 4.0, 0.0);
		glTexCoord2f(1.0, 0.0);
	glEnd();
}

void cockpit()
{
   GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
   GLdouble eqn2[4] = {1.0, 0.0, 0.0, 0.0};

   glPushMatrix();
   glTranslatef (-3.0, 0.8, 0.0);

/*    clip lower half -- y < 0          */
   glClipPlane (GL_CLIP_PLANE0, eqn);
   glEnable (GL_CLIP_PLANE0);
/*    clip left half -- x < 0           */
   glClipPlane (GL_CLIP_PLANE1, eqn2);
   glEnable (GL_CLIP_PLANE1);

	glEnable(GL_BLEND);
	glColor4f(0.0,0.0,100.0,0.9);

   glRotatef (90.0, 1.0, 0.0, 0.0);
   glutSolidSphere(0.7, 20, 16);


   glDisable (GL_CLIP_PLANE1);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glRotatef (-90.0, 0.0, 1.0, 0.0);

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluCylinder(qobj, 0.7, 0.7, 2.0, 15, 15);

	glTranslatef(0.0, 0.0, 2.0);
   glutSolidSphere(0.7, 20, 16);

	glDisable(GL_BLEND);

   glDisable (GL_CLIP_PLANE0);
   glPopMatrix();
}


void jet()
{
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glScalef(2.0, 2.0, 2.0);
	nose();
	fuselage();
	//glPopMatrix();
	cockpit();
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(1.3, 1.3, 1.0);
	glTranslatef(-7.0, -4.5, 0.0);
   wing();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glScalef(1.3, 1.3, 1.0);
	glTranslatef(-7.0, -4.5, 0.0);
   wing();
	glPopMatrix();

	flames();

	glPopMatrix();
}
