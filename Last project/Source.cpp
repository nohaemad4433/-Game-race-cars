#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>

// 2 - for texture
#include<gl/stb_image.h>
#include<iostream>
#include <Math.h>
#include <gl\glut.h>

using namespace std;

#define PI 3.14159265f		// constant PI for circles 

float raduis;		// the raduis of the circles
long double r[14], speed = 1;
int segment = 100, score = 0, i = 100, cnta = 0;	// segments for the circles
bool fullscreen = 1, close = 0, flag = 1,f=0;
int start = 1;
float blockPositionInZAxes = 150, blockPositionInXAxes = 0;	// the position of the opstacle in x axes and z axes

float blockPositionInZAxes2 = 250, blockPositionInXAxes2 = 4;	// the position of the opstacle in x axes and z axes

float blockPositionInZAxes3 = 200, blockPositionInXAxes3 = -4;	// the position of the opstacle in x axes and z axes

float carPosInZAxes, carPosInXAxes;

//******************************************************************************

//width , height of image  , channel : color system if image (RGB ,Gray scale)
int width, height, nrChannels;
//index of each texture we use :Ê›Ï «·«€·» »” Œœ„ Ê«Õœ »”
unsigned int texture;
unsigned char *data = NULL;


//3- texture
void load(int imgnum);
void check(unsigned char *data);

//*********************************************************************************

//Light

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position0[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat light_position1[] = { 2.0f, 5.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

//*******************************************************************
//sound
bool play = 1;
float counter = 0;
//***************************************************************
//Camera
float eyeX = 0, eyeY = 11, eyeZ = -14, angleX = 0, angleY = 2, angleZ = 0;
bool cam = 1;



// this is the front side of the car
void front(){
	// Front face  (z = 1.0f)
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.3);
	glScalef(2, .7, 1);
	glBegin(GL_POLYGON);                // Begin drawing the color cube with 6 quads
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// border for the front face
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.3);
	glScalef(2, .7, 1);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();


	// the glass of the front side
	glPushMatrix();
	glTranslatef(0, 1.68, 3.31);
	glScalef(2, 0.7, 1);
	glRotatef(135.0f, 1.0f, 0.0f, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);                // Begin drawing the color cube with 6 quads
	glColor3f(1.0f, 1.0f, 1.0f);     // white
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// the glass of the front side double layer
	glPushMatrix();
	glTranslatef(0, 1.69, 3.32);
	glScalef(2, 0.7, 1);
	glRotatef(135.0f, 1.0f, 0.0f, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);                // Begin drawing the color cube with 6 quads
	glColor3f(1.0f, 0.5, 1.0f);     // orange
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

}

void back(){
	// Back face (z = -1.0f)
	glColor3f(1.0f, 0.5, 0.0f);     // orange
	glPushMatrix();
	glTranslatef(0.0, 0.0, -2.3);
	glScalef(2, .7, 1);
	glBegin(GL_POLYGON);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	// border for Back face (z = -1.0f)
	glColor3f(1.0f, 1.0, 1.0f);     // white
	glPushMatrix();
	glTranslatef(0.0, 0.0, -2.3);
	glScalef(2, .7, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();


	// the glass of the back side
	glPushMatrix();
	glTranslatef(0, 1.68, -3.31);
	glScalef(2, 0.7, 1);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);                // Begin drawing the color cube with 6 quads
	glColor3f(1.0f, 1.0f, 1.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// the glass of the back side double layer
	glPushMatrix();
	glTranslatef(0, 1.69, -3.30);
	glScalef(2, 0.7, 1);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0);
	glLineWidth(1.5);
	glBegin(GL_POLYGON);                // Begin drawing the color cube with 6 quads
	glColor3f(1.0f, 1.0f, 1.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

}

void top(){
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glPushMatrix();
	glTranslatef(0.0, 0.7, -0.0);
	glScalef(2.0, 1, 1.87);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// border for Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glPushMatrix();
	glTranslatef(0.0, 0.7, -0.0);
	glScalef(2.0, 1, 1.87);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1, 1);     // white
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

void bottom(){
	// Bottom face (y = -1.0f)
	glPushMatrix();
	glTranslatef(0.0, 0.3, .001);
	glScalef(2.0, 1.0, 3.3);
	glColor3f(1.0f, 0.5, 0.0f);     // Orange
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	// border for Bottom face (y = -1.0f)
	glPushMatrix();
	glTranslatef(0.0, 0.3, .001);
	glScalef(2.0, 1.0, 3.3);
	glColor3f(1.0f, 1, 1);     // White
	glBegin(GL_LINE_LOOP);                // Begin drawing the color cube with 6 quads
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();

}

void left(){
	// the left face (x= -1.0f)
	glPushMatrix();
	glScalef(2.0f, 0.7f, 3.3);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5, 0.0f);     // orange
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// border for the left face
	glPushMatrix();
	glScalef(2.0f, 0.7f, 3.3);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1, 1);     // white
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	// split the door and the tail of the car
	glPushMatrix();
	glTranslatef(1.005, 0, .15);
	glScalef(-3.03f, .7f, 0.02);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0, -1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(1.0f, -1.0, 1.0f);
	glVertex3f(1.0f, -1.0, -1.0f);
	glEnd();
	glPopMatrix();

}

void right(){
	// Right face (x = 1.0f)
	glPushMatrix();
	glScalef(2.0f, 0.7f, 3.3);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5, 0.0f);     // Magenta
	glVertex3f(1.0f, 1.0, -1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(1.0f, -1.0, 1.0f);
	glVertex3f(1.0f, -1.0, -1.0f);
	glEnd();
	glPopMatrix();

	// border for Right face (x = 1.0f)
	glPushMatrix();
	glScalef(2.0f, 0.7f, 3.3);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1, 1);     // Magenta
	glVertex3f(1.0f, 1.0, -1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(1.0f, -1.0, 1.0f);
	glVertex3f(1.0f, -1.0, -1.0f);
	glEnd();
	glPopMatrix();

	// split the door and the tail of the car
	glPushMatrix();
	glTranslatef(1.005, 0, .15);
	glScalef(1.03f, .7f, 0.02);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0, -1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(1.0f, -1.0, 1.0f);
	glVertex3f(1.0f, -1.0, -1.0f);
	glEnd();
	glPopMatrix();

}

void wheel(float raduis, float x, float y, float z){
	float th;
	glRotatef(90, 0, 1, 0);
	float j;
	for (j = 0; j < .3; j += .02){
		glBegin(GL_POLYGON);
		for (int i = 0; i < segment; i++){
			th = i*2.0*PI / segment;
			glVertex3f(x + cos(th)*raduis, y + sin(th)*raduis, z + j);
		}
		glEnd();
	}
}

void car(){
	//glTranslatef(0.5f, 0.0f, 5.0f);
	back();
	front();
	top();
	bottom();
	left();
	right();

	glColor3f(0.7, 0.7, 0.7);
	wheel(0.6, -2.3, -0.25, -2.01);// front left wheel

	glColor3f(0.7, 0.7, 0.7);
	glRotatef(90, 0, 1, 0);
	wheel(0.6, 2.3, -0.25, -2.01); // front right wheel	

	glColor3f(0.7, 0.7, 0.7);
	glRotatef(90, 0, 1, 0);
	wheel(0.6, 2.3, -0.25, -2.01); // back left wheel

	glColor3f(0.7, 0.7, 0.7);
	glRotatef(90, 0, 1, 0);
	wheel(0.6, -2.3, -0.25, -2.01); // back right wheel

	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 0, 1, 0);
	wheel(0.3, -2.3, -0.25, -2.02);  // front left wheel

	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 0, 1, 0);
	wheel(0.3, 2.3, -0.25, -2.02); // front right wheel	

	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 0, 1, 0);
	wheel(0.3, 2.3, -0.25, -2.02);  // back left wheel

	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 0, 1, 0);
	wheel(0.3, -2.3, -0.25, -2.02); // back right wheel
}


void road(){

	//Road
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_POLYGON);
	glVertex3f(-12, -1.1, -25);
	glVertex3f(-12, -1.1, 156);
	glVertex3f(12, -1.1, 156);
	glVertex3f(12, -1.1, -25);
	glEnd();

	//Road Left Border
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-12, -1.1, -25);
	glVertex3f(-12, -1.1, 156);
	glVertex3f(-12.3, -1.1, 156);
	glVertex3f(-12.3, -1.1, -25);
	glEnd();

	//Road Right Border
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(12, -1.1, -25);
	glVertex3f(12, -1.1, 156);
	glVertex3f(12.3, -1.1, 156);
	glVertex3f(12.3, -1.1, -25);
	glEnd();

	//Road Middel Border
	//first left
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[1] - 10);
	glVertex3f(4.5, -1.05, r[1]);
	glVertex3f(5.0, -1.05, r[1]);
	glVertex3f(5.0, -1.05, r[1] - 10);
	glEnd();


	//first right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[1] - 10);
	glVertex3f(-4.5, -1.05, r[1]);
	glVertex3f(-5.0, -1.05, r[1]);
	glVertex3f(-5.0, -1.05, r[1] - 10);
	glEnd();
	r[1] -= speed;
	if (r[1] < -10){ r[1] = 156; }
	counter+=0.1;
	//second left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[2] + 3);
	glVertex3f(4.5, -1.05, r[2] + 13);
	glVertex3f(5.0, -1.05, r[2] + 13);
	glVertex3f(5.0, -1.05, r[2] + 3);
	glEnd();

	//second right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[2] + 3);
	glVertex3f(-4.5, -1.05, r[2] + 13);
	glVertex3f(-5.0, -1.05, r[2] + 13);
	glVertex3f(-5.0, -1.05, r[2] + 3);
	glEnd();
	r[2] -= speed;
	if (r[2]<-23)r[2] = 143;
	//3rd left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[3] + 16);
	glVertex3f(4.5, -1.05, r[3] + 26);
	glVertex3f(5.0, -1.05, r[3] + 26);
	glVertex3f(5.0, -1.05, r[3] + 16);
	glEnd();
	
	//3rd right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[3] + 16);
	glVertex3f(-4.5, -1.05, r[3] + 26);
	glVertex3f(-5.0, -1.05, r[3] + 26);
	glVertex3f(-5.0, -1.05, r[3] + 16);
	glEnd();
	r[3] -= speed;
	if (r[3]<-36)r[3] = 130;
	//4th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[4] + 29);
	glVertex3f(4.5, -1.05, r[4] + 39);
	glVertex3f(5.0, -1.05, r[4] + 39);
	glVertex3f(5.0, -1.05, r[4] + 29);
	glEnd();
	
	//4th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[4] + 29);
	glVertex3f(-4.5, -1.05, r[4] + 39);
	glVertex3f(-5.0, -1.05, r[4] + 39);
	glVertex3f(-5.0, -1.05, r[4] + 29);
	glEnd();
	r[4] -= speed;
	if (r[4]<-49)r[4] = 117;
	//5th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[5] + 42);
	glVertex3f(4.5, -1.05, r[5] + 52);
	glVertex3f(5.0, -1.05, r[5] + 52);
	glVertex3f(5.0, -1.05, r[5] + 42);
	glEnd();
	
	//5th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[5] + 42);
	glVertex3f(-4.5, -1.05, r[5] + 52);
	glVertex3f(-5.0, -1.05, r[5] + 52);
	glVertex3f(-5.0, -1.05, r[5] + 42);
	glEnd();
	r[5] -= speed;
	if (r[5]<-62)r[5] = 104;
	//6th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[6] + 55);
	glVertex3f(4.5, -1.05, r[6] + 65);
	glVertex3f(5.0, -1.05, r[6] + 65);
	glVertex3f(5.0, -1.05, r[6] + 55);
	glEnd();

	//6th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[6] + 55);
	glVertex3f(-4.5, -1.05, r[6] + 65);
	glVertex3f(-5.0, -1.05, r[6] + 65);
	glVertex3f(-5.0, -1.05, r[6] + 55);
	glEnd();
	r[6] -= speed;
	if (r[6]<-75)r[6] = 91;
	//7th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[7] + 68);
	glVertex3f(4.5, -1.05, r[7] + 78);
	glVertex3f(5.0, -1.05, r[7] + 78);
	glVertex3f(5.0, -1.05, r[7] + 68);
	glEnd();

	//7th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[7] + 68);
	glVertex3f(-4.5, -1.05, r[7] + 78);
	glVertex3f(-5.0, -1.05, r[7] + 78);
	glVertex3f(-5.0, -1.05, r[7] + 68);
	glEnd();
	r[7] -= speed;
	if (r[7]<-88)r[7] = 78;
	//8th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[8] + 81);
	glVertex3f(4.5, -1.05, r[8] + 91);
	glVertex3f(5.0, -1.05, r[8] + 91);
	glVertex3f(5.0, -1.05, r[8] + 81);
	glEnd();


	//8th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[8] + 81);
	glVertex3f(-4.5, -1.05, r[8] + 91);
	glVertex3f(-5.0, -1.05, r[8] + 91);
	glVertex3f(-5.0, -1.05, r[8] + 81);
	glEnd();
	r[8] -= speed;
	if (r[8]<-101)r[8] = 65;
	//9th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[9] + 94);
	glVertex3f(4.5, -1.05, r[9] + 104);
	glVertex3f(5.0, -1.05, r[9] + 104);
	glVertex3f(5.0, -1.05, r[9] + 94);
	glEnd();

	//9th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[9] + 94);
	glVertex3f(-4.5, -1.05, r[9] + 104);
	glVertex3f(-5.0, -1.05, r[9] + 104);
	glVertex3f(-5.0, -1.05, r[9] + 94);
	glEnd();
	r[9] -= speed;
	if (r[9]<-114)r[9] = 52;
	//10th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[10] + 107);
	glVertex3f(4.5, -1.05, r[10] + 117);
	glVertex3f(5.0, -1.05, r[10] + 117);
	glVertex3f(5.0, -1.05, r[10] + 107);
	glEnd();


	//10th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[10] + 107);
	glVertex3f(-4.5, -1.05, r[10] + 117);
	glVertex3f(-5.0, -1.05, r[10] + 117);
	glVertex3f(-5.0, -1.05, r[10] + 107);
	glEnd();
	r[10] -= speed;
	if (r[10]<-127)r[10] = 39;
	//11th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[11] + 120);
	glVertex3f(4.5, -1.05, r[11] + 130);
	glVertex3f(5.0, -1.05, r[11] + 130);
	glVertex3f(5.0, -1.05, r[11] + 120);
	glEnd();

	//11th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[11] + 120);
	glVertex3f(-4.5, -1.05, r[11] + 130);
	glVertex3f(-5.0, -1.05, r[11] + 130);
	glVertex3f(-5.0, -1.05, r[11] + 120);
	glEnd();
	r[11] -= speed;
	if (r[11]<-140)r[11] = 26;
	//12th left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[12] + 133);
	glVertex3f(4.5, -1.05, r[12] + 143);
	glVertex3f(5.0, -1.05, r[12] + 143);
	glVertex3f(5.0, -1.05, r[12] + 133);
	glEnd();
	
	//12th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[12] + 133);
	glVertex3f(-4.5, -1.05, r[12] + 143);
	glVertex3f(-5.0, -1.05, r[12] + 143);
	glVertex3f(-5.0, -1.05, r[12] + 133);
	glEnd();
	r[12] -= speed;
	if (r[12]<-153)r[12] = 13;
	//13 left
	glBegin(GL_POLYGON);
	glVertex3f(4.5, -1.05, r[13] + 146);
	glVertex3f(4.5, -1.05, r[13] + 153);
	glVertex3f(5.0, -1.05, r[13] + 153);
	glVertex3f(5.0, -1.05, r[13] + 146);
	glEnd();

	//13th right
	glBegin(GL_POLYGON);
	glVertex3f(-4.5, -1.05, r[13] + 146);
	glVertex3f(-4.5, -1.05, r[13] + 153);
	glVertex3f(-5.0, -1.05, r[13] + 153);
	glVertex3f(-5.0, -1.05, r[13] + 146);
	glEnd();
	r[13] -= speed;
	if (r[13]<-166)r[13] = 0;

	if (score % 10 == 0)speed *= 1.0005;
}

void opstacle(float z){
	glColor3f(1, 0, 0);
	glutSolidCube(4);

	if (((carPosInXAxes - blockPositionInXAxes >= 0 && carPosInXAxes - blockPositionInXAxes <3.9) || (carPosInXAxes - blockPositionInXAxes <= 0 && carPosInXAxes - blockPositionInXAxes >-3.7)) && blockPositionInZAxes < carPosInZAxes + 5){
		f = 0;
		//exit(0);
		carPosInZAxes = 0;
		blockPositionInZAxes = 150;
		blockPositionInZAxes2 = 170;
		blockPositionInZAxes3= 190;
		start = 2;
	}

	if (blockPositionInZAxes < -z + 140){
		blockPositionInZAxes = z;
		blockPositionInXAxes = carPosInXAxes + (rand() % (2 - (-2 + 1))) + (-2);
	}


}

void opstacle2(float z){
	glColor3f(0, 1, 0);
	glutSolidCube(4);

	if (((carPosInXAxes - blockPositionInXAxes2 >= 0 && carPosInXAxes - blockPositionInXAxes2 <3.9) || (carPosInXAxes - blockPositionInXAxes2 <= 0 && carPosInXAxes - blockPositionInXAxes2 >-3.7)) && blockPositionInZAxes2 < carPosInZAxes + 5){
		
		f = 0;
		carPosInZAxes = 0;
		blockPositionInZAxes = 150;
		blockPositionInZAxes2 = 170;
		blockPositionInZAxes3 = 190;
		start = 2;

	}
	

	if (blockPositionInZAxes2 < -z + 160){
		blockPositionInZAxes2 = z;
		blockPositionInXAxes2 = carPosInXAxes + (rand() % (3 - (-3 + 1))) + (-3);
	}
}

void opstacle3(float z){
	glColor3f(0, 0, 3);
	glutSolidCube(4);

	if (((carPosInXAxes - blockPositionInXAxes3 >= 0 && carPosInXAxes - blockPositionInXAxes3 <3.9) || (carPosInXAxes - blockPositionInXAxes3 <= 0 && carPosInXAxes - blockPositionInXAxes3 >-3.7)) && blockPositionInZAxes3 < carPosInZAxes + 5){
		//exit(0);
		f = 0;
		carPosInZAxes = 0;
		blockPositionInZAxes = 150;
		blockPositionInZAxes2 = 170;
		blockPositionInZAxes3 = 190;
		start = 2;
	}
	
	if (blockPositionInZAxes3 < -z + 180){
		blockPositionInZAxes3 = z;
		blockPositionInXAxes3 = carPosInXAxes + (rand() % (6 - (-6 + 1))) + (-6);
	}
}


void side(){
	//1 area
	//2 suface

	//left side 
	int Zleft = -15;
	int Zleft2 = Zleft + 5;
	float Xleft=300;

	//important for speration of colors between road and sides
	glEnable(GL_TEXTURE_2D);

	load(1);
	glBegin(GL_QUADS);

	for (int i = 0; i <= 32; i++){
		

		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(Xleft, -1.1, Zleft);

		glTexCoord2d(5.0f, 0.0f);
		glVertex3f(12.3, -1.1, Zleft);

		glTexCoord2d(5.0f, 5.0f);
		glVertex3f(12.3, -1.1, Zleft2);

		glTexCoord2d(0.0f, 5.0f);
		glVertex3f(Xleft, -1.1, Zleft2);



		Zleft = Zleft2;
		Zleft2 = Zleft + 5;
	}

	glEnd();

	//****************************************************	
	//Right part

	int ZRight = -15;
	int ZRight2 = ZRight + 5;
	float Xright = -300;

	//glColor3f(0.486, 0.988, 0);
	glBegin(GL_QUADS);

	for (int i = 0; i <= 32; i++){

		/*if (i > 10 ){
			Xright = -200;
		}*/
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(Xright, -1.1, ZRight);

		glTexCoord2d(5.0f, 0.0f);
		glVertex3f(-12.3, -1.1, ZRight);

		glTexCoord2d(5.0f, 5.0f);
		glVertex3f(-12.3, -1.1, ZRight2);

		glTexCoord2d(0.0f, 5.0f);
		glVertex3f(Xright, -1.1, ZRight2);


		ZRight = ZRight2;
		ZRight2 = ZRight + 5;
	}

	glEnd();
	//separation of colors
	glDisable(GL_TEXTURE_2D);


	//************************************************************************

	/*
	//glEnable(GL_TEXTURE_2D);
	load(2);
	//front image
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-28, -1.1, 156);

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(28, -1.1, 156);

	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(28, 40, 180);

	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-28, 40, 180);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	*/
}

//*****************··ﬂ «»… **************************
void drawStrokeText(string str, float x, float y, float z)
{
	
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	glScalef(0.002f, 0.002f, 0);

	for (int i=0; i<str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}


//*****************··ﬂ «»… **************************
void drawStrokeText2(string str, float x, float y, float z)
{

	
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	glScalef(0.007f, 0.007f, 0);


	for (int i = 0; i<str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}



void display(){

	//glColor3f(0.8, 0.52, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (start==0){
		gluLookAt(
			eyeX, eyeY, eyeZ,
			angleX, angleY, angleZ,
			0, 1, 0
			);


		glPushMatrix();
		glTranslatef(carPosInXAxes, 0, carPosInZAxes);
		car();
		glPopMatrix();

		road();

		side();

		glPushMatrix();
		glTranslatef(blockPositionInXAxes, 1, blockPositionInZAxes);
		opstacle(150);
		blockPositionInZAxes -= 1.7*speed;
		glPopMatrix();

		glPushMatrix();
		glTranslatef(blockPositionInXAxes2, 1, blockPositionInZAxes2);
		opstacle2(170);
		blockPositionInZAxes2 -= 1.5*speed;
		glPopMatrix();

		glPushMatrix();
		glTranslatef(blockPositionInXAxes3, 1, blockPositionInZAxes3);
		opstacle3(190);
		blockPositionInZAxes3 -= 1.2*speed;
		glPopMatrix();

	

	}
	else if (start==1){
		//to show words with image
		gluLookAt(0.0, 6, 4.0,
			0, 6, 0,
			0, 1.0f, 0.0f);


		glColor3f(1, 1, 1);
		load(2);

		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);


		glTexCoord2d(1, 1);
		glVertex3f(-25, -8, -10);

		glTexCoord2d(0, 1);
		glVertex3f(25, -8, -10);

		glTexCoord2d(0, 0);
		glVertex3f(25, 20, -10);

		glTexCoord2d(1, 0);
		glVertex3f(-25, 20, -10);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glColor3f(0, 0, 0);
		drawStrokeText("Press S to Start", 2.8, -1, 0);
		drawStrokeText2("Survival Game", 0.6, 0, 0);


	}
	else if (start == 2){

		gluLookAt(0.0, 6, 4.0,
			0, 6, 0,
			0, 1.0f, 0.0f);

		glColor3f(1, 1, 1);
		
		string s;
		int n = counter,m;
		while (n){
			m = n % 10;
			s += char(m + '0');
			n /= 10;
			cout << counter;
		}
		reverse(s.begin(), s.end());
		string score = "Your Score : " + s;
		
		drawStrokeText(score,-1,-2,0);
		drawStrokeText("Press S to Try Again", -1.3, -4, 0);
		drawStrokeText2("Game Over", -2.3, 0, 0);

	}
	glutSwapBuffers();
	glutPostRedisplay();

}

// main function is to index each image we use it in the project
//»⁄·„ ﬂ· ’Ê—… » index „⁄Ì‰
void load(int imgnum){
	if (imgnum == 1){

		//stbi_load exist in header file we insert 
		data = stbi_load("area.bmp", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 2){

		data = stbi_load("splash.bmp", &width, &height, &nrChannels, 0);
		check(data);

	}

}

void check(unsigned char *data){
	if (data)
	{
		//    1
		//⁄œœ «· ﬂ ‘—” «·Ï ⁄«Ê“ «⁄„·Â« ··’Ê—… «·Ï «‰  »⁄ Â«
		glGenTextures(1, &texture);
		//»ÌﬂÊ‰ «· texture «·Ï „”«Õ … 1 * 1
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//filter part
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//deconstructor
	stbi_image_free(data);
}

void init(){
	glClearColor(0.2, .75, 0.75, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h){

	if (h == 0) h = 1;
	float aspect = (float)w / (float)h;
	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, aspect, 0.1f, 500.0f);


	glMatrixMode(GL_MODELVIEW);

}
void spkeyboard(int key, int x, int y){

	if (key == GLUT_KEY_F1){
		fullscreen = !fullscreen;
		if (fullscreen)glutFullScreen();
		else{
			glutPositionWindow(GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) /4 );   //center of window is center of screen
			glutReshapeWindow(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);             //to change screen size 
		}
	}
	switch (key){
	case GLUT_KEY_LEFT:
		carPosInXAxes += 1.5;
		if (carPosInXAxes > 9.5){
			carPosInXAxes = 9.5;
		}
		break;
	case GLUT_KEY_RIGHT:
		carPosInXAxes -= 1.5;
		if (carPosInXAxes < -9.5){
			carPosInXAxes = -9.5;
		}
		break;
	case GLUT_KEY_UP:
		carPosInZAxes += 0.7;
		if (carPosInZAxes > 10){
			carPosInZAxes = 10;
		}
		break;
	case GLUT_KEY_DOWN:
		carPosInZAxes -= 0.7;
		if (carPosInZAxes < -7.5){
			carPosInZAxes = -7.5;
		}
		break;
	}
	switch (key){
	case GLUT_KEY_LEFT:
		carPosInXAxes += 0.7;
		if (carPosInXAxes > 9.5){
			carPosInXAxes = 9.5;
		}
		break;
	case GLUT_KEY_RIGHT:
		carPosInXAxes -= 0.7;
		if (carPosInXAxes < -9.5){
			carPosInXAxes = -9.5;
		}
		break;
	}

}
void mylight(){

	//**************************** Light ***********************************************
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	//***********************************************************************************************

	//**************************** Light ***********************************************
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);


	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	//***********************************************************************************************
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {

	case 27:
		exit(0);
		break;
	case 115:
		start = 0;
		if (!f){ f = 1;		speed = 1;		counter = 0; }
		break;
	case 99:
		cam = !cam;
		if (cam == true){
			eyeX = 0;
			eyeY = 11;
			eyeZ = -14;
			angleX = 0;
			angleY = 2;
			angleZ = 0;

		}
		else{
			eyeX = 0;
			eyeY = 6;
			eyeZ = -5;
			angleX = 0;
			angleY = 2;
			angleZ = 0;

		}
		break;
	case 108:
		mylight();
	}
	
}

void timer(int v){
	glutTimerFunc(750, timer, 0);
	
}

void sound(){
	PlaySound("sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow("Car");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spkeyboard);
	glutFullScreen();
	glutTimerFunc(750, timer, 0);
	mylight();
	if (play){
		sound();
	}
	init();
	if (close)exit(0);
	glutMainLoop();

	
}