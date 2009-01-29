/*
 * The missile components.
 * For flame, fuselage, and nose,
 * see the jet code.
 */

#include "JoeSmith.h"

void fin(float* v1, float* v2, float* v3)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
	glEnd();
	glPopMatrix();
}

void fins()
{
	glPushMatrix();
	glTranslatef(-10.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);

	float v1[3] = {0.0, 0.0, 0.0};
  	float v2[3] = {0.0, 5.0, 0.0};
	float v3[3] = {1.0, 0.0, 1.0};  

	float v4[3] = {0.0, 0.0, 0.0};
  	float v5[3] = {0.0, -5.0, 0.0};
	float v6[3] = {1.0, 0.0, 1.0};  

	float v7[3] = {0.0, 0.0, 0.0};
  	float v8[3] = {0.0, 0.0, 5.0};
	float v9[3] = {1.0, 0.0, 1.0};  

	float va[3] = {0.0, 0.0, 0.0};
  	float vb[3] = {0.0, 0.0, -5.0};
	float vc[3] = {1.0, 0.0, 1.0};  

	fin(v1, v2, v3);
	fin(v4, v5, v6);
	fin(v7, v8, v9);
	fin(va, vb, vc);
	glPopMatrix();
}

void missile()
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//glScalef(0.1, 0.1, 0.1);

	nose();
	glColor3f(1.0, 1.0, 1.0);
	fuselage();
	glColor3f(1.0, 0.0, 0.0);
	fins();

	flames();

	glPopMatrix();
   glEnable(GL_LIGHT1);
}
