#ifdef _APPLE_
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glew.h>
#include <GL/freeglut.h> 
#endif
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

//References:
// 
//https://stackoverflow.com/questions/71974453/visual-studio-express-2017-output-not-displaying-for-stroke-text-function
//https://youtu.be/Wzykvg7t9l8?si=i974zdJn2Q8tdjX3

//Raghad_alsebayyil,Yusra Zain,Sara Abdulmalek,Shooq Authaynani,Doha Alhazmi

using namespace std;

GLint win_width = 550,
win_hight = 550;

GLdouble PI = 3.14159265359;

char userCake;
char again;

BOOLEAN Scene1 = true;   // start
BOOLEAN Scene2q1;        // Q:which cake
BOOLEAN Scene3ing;        //  ingred...
BOOLEAN Scene4butter;        // butter
BOOLEAN Scene4AfterAddbutter;        //After Add Butter
BOOLEAN Scene5egg;        //egg 
BOOLEAN Scene5AfterAddegg;        // after add egg
BOOLEAN Scene6milk;       //milk
BOOLEAN Scene6AfterAddmilk; //After Add milk
BOOLEAN Scene7flour;      //Flour
BOOLEAN Scene7AfterAddflour;      //After Add Flour
BOOLEAN Scene8mix;      //mixing red velvet cake
BOOLEAN Scene9cakePanToOvenR;      //put the pan in oven
BOOLEAN Scene9cakePanToOvenC;       //put the pan in oven 
BOOLEAN Scene10cakePanDoneInR; //cake done in oven
BOOLEAN Scene10cakePanDoneInC; //  cake done in oven
BOOLEAN Scene11cakePanDoneOutR; //cake done out oven
BOOLEAN Scene11cakePanDoneOutC; //cake done out oven        
BOOLEAN Scene12Q2; //Q: which color                        
BOOLEAN Scene13RW;     // red velvet and white cream                        
BOOLEAN Scene13CB;      // carrot and Brown cream
BOOLEAN Scene13RB;     // red velvet and Brown cream
BOOLEAN Scene13CW;     // carrot and white cream

// for the mixture
float CakePanMinX = 28;
float CakePanMinY = 260;
float CakePanMaxX = 275;
float CakePanMaxY = 265;
float CakePanXU = 285;
float CakePanYU = 262;

// for the whisk
float _angle = 30.0f;
float _cameraAngle = 0.0f;

// for moving milk,butter,egg and flour
float transValueYB2;
float transValueXB2;
float transValueYM2;
float transValueXM2;
float scaleValueXB2;
float scaleValueYB2;
float scaleValueE2;
float transValueY2;
float transValueX2;
float rotateValue;

//float transValue;
float transValueX;
float transValueY;
float transValueZ;
float near1;
float far1;

// buffers
GLuint myTexture1;
char image1Path[] = ".................................../A2.bmp";   // the bmp photo path

GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;

	//The following code will read in our RAW file
	fopen_s(&file, filename, "rb");

	if (file == NULL)
	{
		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
		exit(0);
		return 0;
	}

	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);

	fclose(file);


	// reorder the image colors to RGB not BGR
	for (int i = 0; i < width * height; ++i) {
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &texture);            //generate the texture with the loaded data
	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data); //free the texture array
	if (glGetError() != GL_NO_ERROR)
		printf("GLError in genTexture()\n");
	return texture; //return whether it was successfull  
}

void update(int value) {
	_angle += 4.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	glutPostRedisplay(); ////Tell GLUT that the scene has changed
	glutTimerFunc(25, update, 0);
}
// for the whisk
void OvalHollow(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
void OvalHollow2(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 1.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
//lamp
void OvalHollow3(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = -1.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}  // lamp  


void OvalFilled(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void OvalFilled2(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = 1.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void OvalFilled3(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = -1.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (0.2f * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
// to draw a half oval Downward

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void drawFilledCircle2(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = -1.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void drawFilledCircle3(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = 1.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
// used in the table 
void drawFilledCircle4(GLfloat x, GLfloat y, GLfloat radius, GLfloat radius2) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius2 * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount)));
	}
	glEnd();
}
void drawHollowCircle2(GLfloat x, GLfloat y, GLfloat radius, GLfloat radius2) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius2 * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}  //oven
// used in cake
void drawHollowCircle3(GLfloat x, GLfloat y, GLfloat radius, GLfloat radius2) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = -1.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius2 * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
void drawHollowCircle4(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = -1.0f * PI;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount)));
	}
	glEnd();
}

void drawStrokeText(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 600, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void drawStrokeText2(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 600, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void drawStrokeText1(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 600, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		GLUT_BITMAP_9_BY_15,
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);

	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void drawStrokeText3(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 600, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		GLUT_BITMAP_9_BY_15,
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);

	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void DrawCurve(float cx, float cy, float r, int num_segments, float arc_length)
{//GL_LINE_STRIP
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = arc_length * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();

}

static void special(int key, int x, int y)
{
	//handle special keys
	switch (key) {
	case GLUT_KEY_RIGHT:

		transValueX += 0.1;
		CakePanXU += 1;
		break;
	case GLUT_KEY_LEFT:

		transValueX -= 0.1;
		CakePanXU -= 1;
		break;

	case GLUT_KEY_UP:

		transValueY += 0.1;
		CakePanYU += 1;
		break;

	case GLUT_KEY_DOWN:

		transValueY -= 0.1;
		CakePanYU -= 1;
		break;
	default:
		break;
	}
}
static void key(unsigned char keyPressed, int x, int y) // key handling
{

	switch (keyPressed)
	{
	case 's':
	case 'S':
		Scene1 = false;
		Scene2q1 = true;
		break;
	case 'r':
	case 'R':
		userCake = 'r';
		Scene2q1 = false;
		Scene3ing = true;
		break;
	case 'c':
	case 'C':
		userCake = 'c';
		Scene2q1 = false;
		Scene3ing = true;
		break;

	case 'w':
	case 'W':
		if (userCake == 'r') {
			Scene12Q2 = false;
			Scene13RW = true;
			break;
		}
		Scene12Q2 = false;
		Scene13CW = true;
		break;
	case 'b':
	case 'B':
		if (userCake == 'c') {
			Scene12Q2 = false;
			Scene13CB = true;
			break;
		}
		Scene12Q2 = false;
		Scene13RB = true;
		break;
	case 'q':
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
static void mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
			{   // egg
				transValueY2 = .3;
				transValueX2 = -.1;
				scaleValueE2 = .4;
				//
			}

			{
				//  milk and flour
				transValueYM2 = 0.0;
				transValueXM2 = 0.0;
				rotateValue = 0;


			}

		}
		if (state == GLUT_DOWN) {

			// milk and flour
			transValueYM2 = .5;
			transValueXM2 = -.1;
			rotateValue = 45;


		}

	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_UP) {

			if (Scene3ing == true) {
				Scene3ing = false;
				Scene4butter = true;

			}
			else if (Scene4butter == true) {
				Scene4butter = false;
				Scene4AfterAddbutter = true;
			}
			else if (Scene4AfterAddbutter == true) {
				Scene4AfterAddbutter = false;
				Scene5egg = true;
			}
			else if (Scene5egg == true) {
				Scene5egg = false;
				Scene5AfterAddegg = true;
			}
			else if (Scene5AfterAddegg == true) {
				Scene5AfterAddegg = false;
				Scene6milk = true;
			}
			else if (Scene6milk == true) {
				Scene6milk = false;
				Scene6AfterAddmilk = true;

			}
			else if (Scene6AfterAddmilk == true) {
				Scene6AfterAddmilk = false;
				Scene7flour = true;
			}
			else if (Scene7flour == true) {
				Scene7flour = false;
				Scene7AfterAddflour = true;
			}
			else if (Scene7AfterAddflour == true) {
				Scene7AfterAddflour = false;
				Scene8mix = true;

			}
			else if (Scene8mix == true) {
				Scene8mix = false;
				if (userCake == 'r') {
					Scene9cakePanToOvenR = true;
				}
				else {
					Scene9cakePanToOvenC = true;
				}

			}
			else if (Scene9cakePanToOvenR == true) {
				Scene9cakePanToOvenR = false;
				Scene10cakePanDoneInR = true;
			}
			else if (Scene9cakePanToOvenC == true) {
				Scene9cakePanToOvenC = false;
				Scene10cakePanDoneInC = true;
			}
			else if (Scene10cakePanDoneInR == true) {
				Scene10cakePanDoneInR = false;
				Scene11cakePanDoneOutR = true;
			}
			else if (Scene10cakePanDoneInC == true) {
				Scene10cakePanDoneInC = false;
				Scene11cakePanDoneOutC = true;
			}
			else if (Scene11cakePanDoneOutR == true) {
				Scene11cakePanDoneOutR = false;
				Scene12Q2 = true;
			}
			else if (Scene11cakePanDoneOutC == true) {
				Scene11cakePanDoneOutC = false;
				Scene12Q2 = true;
			}else {
				exit(0);
			}

		}
	}

}


static void play(void)
{
	glutPostRedisplay();
}


void doorFrame()
{
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.5f, 0.6f, 0.5f);

	glVertex2f(-0.65f, 0.8f);
	glVertex2f(0.65f, 0.8f);
	glVertex2f(0.65f, -0.8f);
	glVertex2f(-0.65f, -0.8f);
	glEnd();

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.9f, 0.5f, 0.6f);

	glVertex2f(-0.70f, -0.80f);  // door frame
	glVertex2f(0.70f, -0.80f);

	glVertex2f(0.66f, 0.80f);
	glVertex2f(-0.66f, 0.80f);

	glVertex2f(-0.65f, -0.80f);
	glVertex2f(-0.65f, 0.80f);

	glVertex2f(0.65f, -0.80f);
	glVertex2f(0.65f, 0.80f);


	glVertex2f(-0.70f, -0.85f);  // door frame -out
	glVertex2f(0.70f, -0.85f);

	glVertex2f(0.71f, 0.85f);
	glVertex2f(-0.71f, 0.85f);

	glVertex2f(-0.70f, -0.85f);
	glVertex2f(-0.70f, 0.85f);

	glVertex2f(0.70f, -0.85f);
	glVertex2f(0.70f, 0.85f);



	glVertex2f(-0.79f, -0.95f);  // door frame bottom
	glVertex2f(0.79f, -0.95f);

	glVertex2f(-0.78f, -0.95f);
	glVertex2f(-0.70f, -0.85f);

	glVertex2f(0.78f, -0.95f);
	glVertex2f(0.70f, -0.85f);
	glEnd();
}
void doorkey()
{
	glColor3f(1.0f, 0.8f, 0.2f);
	drawFilledCircle(0.56, -0.019, 0.019);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(0.60f, 0.2f);
	glVertex2f(0.60f, -0.1f);

	glVertex2f(0.52f, 0.2f);
	glVertex2f(0.52f, -0.1f);

	glVertex2f(0.60f, -0.1f);
	glVertex2f(0.52f, -0.1f);

	glVertex2f(0.60f, 0.2f);
	glVertex2f(0.52f, 0.2f);
	glEnd();

	drawFilledCircle(0.56, 0.10, 0.055);  // hand 

	glBegin(GL_QUADS);                  // key        
	glVertex2f(0.551f, -0.059f);
	glVertex2f(0.551f, -0.02f);
	glVertex2f(0.570f, -0.02f);
	glVertex2f(0.570f, -0.059f);
	glEnd();
}
void doorWriting()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text;
	text = " CG BAKERY";
	drawStrokeText1(text.data(), text.size(), 200, 310);
}
void doorHeart()
{
	glLineWidth(2.0f);                       // heart
	glColor3f(.7f, .0f, .1f);
	drawFilledCircle(-0.06, 0.60, 0.075);
	drawFilledCircle(0.06, 0.60, 0.075);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.14, 0.59f);
	glVertex2f(0.0f, 0.40f);

	glVertex2f(0.14, 0.59f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCurve(-0.04, 0.59, -0.09, 6, -1.20);

	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text;
	text = "START";
	drawStrokeText(text.data(), text.size(), 275, 470);

}

void ovenHearts()
{
	glLineWidth(1.0f);
	//hearts
	// drawing the filled circle
	glColor3f(0.8, 0.0, 0.0);
	drawFilledCircle(-0.514, 0.457, .01);
	glColor3f(0.8, 0.0, 0.0);
	drawFilledCircle(-0.532, 0.457, .01);

	glBegin(GL_TRIANGLES);  // Begin drawing triangles
	glColor3f(0.8f, 0.0f, 0.0f);

	glVertex2f(-0.52f, 0.43f);   // Vertex 1
	glVertex2f(-0.506f, 0.45f);   // Vertex 2
	glVertex2f(-0.538f, 0.45f);  // Vertex 3

	glEnd();  // End drawing triangles
}
void oven()
{
	glLineWidth(1.0f);
	// drawing the border around the circle
	glColor3f(0.2764, 0.2764, 0.2764);
	drawHollowCircle(-0.7, 0.7, .13);
	// drawing the filled circle
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(-0.7, 0.7, .129);



	glBegin(GL_QUADS);
	//big squere
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.94f, 0.1f);   // Bottom-left vertex
	glVertex2f(-0.46f, 0.1f);    // Bottom-right vertex
	glVertex2f(-0.46f, 0.5f);     // Top-right vertex
	glVertex2f(-0.94f, 0.5f);    // Top-left vertex
	//right foot 
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.6f, 0.02f);   // Bottom-left vertex
	glVertex2f(-0.5f, 0.02f);    // Bottom-right vertex
	glVertex2f(-0.5f, 0.1f);     // Top-right vertex
	glVertex2f(-0.6f, 0.1f);    // Top-left vertex
	//left foot 
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.9f, 0.02f);   // Bottom-left vertex
	glVertex2f(-0.8f, 0.02f);    // Bottom-right vertex
	glVertex2f(-0.8f, 0.1f);     // Top-right vertex
	glVertex2f(-0.9f, 0.1f);    // Top-left vertex
	//
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.8f, 0.07f);   // Bottom-left vertex
	glVertex2f(-0.6f, 0.07f);    // Bottom-right vertex
	glVertex2f(-0.6f, 0.1f);     // Top-right vertex
	glVertex2f(-0.8f, 0.1f);    // Top-left vertex
	//g
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.93f, 0.5f);   // Bottom-left vertex
	glVertex2f(-0.47f, 0.5f);    // Bottom-right vertex
	glVertex2f(-0.51f, 0.62f);     // Top-right vertex
	glVertex2f(-0.88f, 0.62f);    // Top-left vertex

	//f
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to black
	glVertex2f(-0.883f, 0.62f);   // Bottom-left vertex
	glVertex2f(-0.507f, 0.62f);    // Bottom-right vertex
	glVertex2f(-0.507f, 0.71f);     // Top-right vertex
	glVertex2f(-0.883f, 0.71f);    // Top-left vertex


	glEnd();

	glBegin(GL_LINES);
	//big squere
	// line 1
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.94f, 0.1f);
	glVertex2f(-0.46f, 0.1f);
	//2
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.46f, 0.5f);
	glVertex2f(-0.46f, 0.1f);
	//3
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.46f, 0.5f);
	glVertex2f(-0.94f, 0.5f);
	//4
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.94f, 0.1f);
	glVertex2f(-0.94f, 0.5f);

	// right foot 
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.6f, 0.02f);
	glVertex2f(-0.5f, 0.02f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.5f, 0.1f);
	glVertex2f(-0.5f, 0.02f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.6f, 0.02f);
	glVertex2f(-0.6f, 0.07f);

	// left foot 
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.9f, 0.02f);
	glVertex2f(-0.8f, 0.02f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.9f, 0.02f);
	glVertex2f(-0.9f, 0.1f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.8f, 0.02f);
	glVertex2f(-0.8f, 0.07f);
	//
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.8f, 0.07f);
	glVertex2f(-0.6f, 0.07f);
	// the inner squere
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.9f, 0.13f);
	glVertex2f(-0.5f, 0.13f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.5f, 0.4f);
	glVertex2f(-0.5f, 0.13f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.5f, 0.4f);
	glVertex2f(-0.9f, 0.4f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.9f, 0.13f);
	glVertex2f(-0.9f, 0.4f);

	//
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.86f, 0.17f);
	glVertex2f(-0.53f, 0.17f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.53f, 0.17f);
	glVertex2f(-0.565f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.565f, 0.3f);
	glVertex2f(-0.83f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.86f, 0.17f);
	glVertex2f(-0.83f, 0.3f);

	//
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.57f, 0.17f);
	glVertex2f(-0.595f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.61f, 0.17f);
	glVertex2f(-0.625f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.65f, 0.17f);
	glVertex2f(-0.655f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.69f, 0.17f);
	glVertex2f(-0.688f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.73f, 0.17f);
	glVertex2f(-0.725f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.76f, 0.17f);
	glVertex2f(-0.755f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.795f, 0.17f);
	glVertex2f(-0.785f, 0.3f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.823f, 0.17f);
	glVertex2f(-0.81f, 0.3f);

	//g
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.93f, 0.5f);
	glVertex2f(-0.88f, 0.62f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.51f, 0.62f);
	glVertex2f(-0.88f, 0.62f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.51f, 0.62f);
	glVertex2f(-0.47f, 0.5f);

	//f
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.883f, 0.62f);
	glVertex2f(-0.883f, 0.71f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.83f, 0.71f);
	glVertex2f(-0.883f, 0.71f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.507f, 0.71f);
	glVertex2f(-0.57f, 0.71f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.507f, 0.71f);
	glVertex2f(-0.507f, 0.62f);

	////clock
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.7f, 0.73f);
	glVertex2f(-0.67f, 0.76f);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.7f, 0.73f);
	glVertex2f(-0.715f, 0.749f);


	glEnd();

	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.60, 0.54, .02, 0.06);
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.60, 0.54, .01, 0.04);

	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.80, 0.54, .02, 0.06);
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.80, 0.54, .01, 0.04);

	//
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.60, 0.59, .015, 0.04);
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.60, 0.59, .008, 0.03);

	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.80, 0.59, .015, 0.04);
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle2(-0.80, 0.59, .008, 0.03);

	//clock
	// drawing the border around the circle
	glColor3f(0.2764, 0.2764, 0.2764);
	drawHollowCircle(-0.7, 0.74, 0.049);

	// drawing the border around the heart
	// drawing the border around the circle
	glColor3f(0.2764, 0.2764, 0.2764);
	drawHollowCircle(-0.693, 0.45, 0.0299);

	ovenHearts();

	glPushMatrix();
	glTranslatef(-0.09, 0.0, 0.0);
	ovenHearts();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, 0.0, 0.0);
	ovenHearts();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.26, 0.0, 0.0);
	ovenHearts();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.35, 0.0, 0.0);
	ovenHearts();
	glPopMatrix();


}
void triangleTable() {
	glBegin(GL_TRIANGLES);  // Begin drawing triangles
	glColor3f(0.66f, 0.26f, 0.46f);

	glVertex2f(-0.42f, -0.3f);   // Vertex 1
	glVertex2f(-0.48f, -0.3f);   // Vertex 2
	glVertex2f(-0.45f, -0.1f);  // Vertex 3

	glEnd();  // End drawing triangles

}
void table() {

	glBegin(GL_QUADS);

	glColor3f(0.6f, 0.29803f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.06f, -0.60f);   // Bottom-left vertex
	glVertex2f(0.0f, -0.60f);    // Bottom-right vertex
	glVertex2f(0.03f, -0.35f);     // Top-right vertex
	glVertex2f(-0.08f, -0.35f);    // Top-left vertex
	glEnd();

	glColor3f(0.6f, 0.29803f, 0.0f);
	drawFilledCircle4(-.03, -0.62, .05, .2);
	////
	glColor3f(0.7f, 0.3f, 0.5f);
	drawFilledCircle4(-.02, -0.36, .07, .16);

	glColor3f(0.7f, 0.3f, 0.5f);
	drawFilledCircle4(.33, -0.36, .07, .16);

	glColor3f(0.7f, 0.3f, 0.5f);
	drawFilledCircle4(-.37, -0.36, .07, .15);

	glColor3f(0.7f, 0.3f, 0.5f);
	drawFilledCircle4(-.63, -0.36, .04, .06);

	glColor3f(0.7f, 0.3f, 0.5f);
	drawFilledCircle4(.54, -0.36, .04, .05);
	////
	glBegin(GL_QUADS);

	glColor3f(0.7f, 0.3f, 0.5f); // Set color to black
	glVertex2f(-0.69f, -0.37f);   // Bottom-left vertex
	glVertex2f(0.60f, -0.37f);    // Bottom-right vertex
	glVertex2f(0.535f, 0.0f);     // Top-right vertex
	glVertex2f(-0.64f, 0.0f);    // Top-left vertex
	glEnd();

	glPushMatrix();
	glTranslatef(-0.095, -0.08, 0.0);
	triangleTable();
	glScalef(1.7, 5.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, -0.08, 0.0);
	triangleTable();
	glScalef(1.7, 5.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.61, -0.08, 0.0);
	triangleTable();
	glScalef(.8, 5.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.95, -0.08, 0.0);
	triangleTable();
	glScalef(.01, 5.0, 1.0);
	glPopMatrix();
	////
	glColor3f(0.79f, 0.39f, 0.59f);
	drawFilledCircle4(-.05, 0.0, .14, .59);

	/*glColor3f(.8, .8, .8);
	drawHollowCircle2(-.05, 0.0, .14, .59);*/
}
void Chef() {

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, -0.1f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(0.23f, 0.2f);
	glVertex2f(0.08f, 0.2f);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.096, 0.2f);
	glVertex2f(0.096f, -0.1f);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.14f, 0.02f);
	glVertex2f(0.18f, 0.02f);
	glVertex2f(0.18f, 0.07f);
	glVertex2f(0.14f, 0.07f);
	glEnd();

	glDisable(GL_LINE_STIPPLE);


	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(0.06f, -0.25f);
	glVertex2f(0.12f, -0.25f);
	glVertex2f(0.12f, -0.1f);
	glVertex2f(0.06f, -0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(0.18f, -0.25f);
	glVertex2f(0.25f, -0.25f);
	glVertex2f(0.25f, -0.1f);
	glVertex2f(0.18f, -0.1f);
	glEnd();

	glColor3f(1.0f, 0.9f, 0.6);
	drawFilledCircle(0.15, 0.29, 0.12);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(-0.07f, 0.02f);
	glVertex2f(-0.03f, 0.02f);
	glVertex2f(0.05f, 0.1f);
	glVertex2f(0.08f, 0.18f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, 0.04f);
	glVertex2f(-0.01f, 0.04f);
	glVertex2f(0.06f, 0.1f);
	glVertex2f(0.08f, 0.18f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(0.33f, -0.002f);
	glVertex2f(0.38f, -0.002f);
	glVertex2f(0.23f, 0.18f);
	glVertex2f(0.26f, 0.09f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.32f, 0.015f);
	glVertex2f(0.36f, 0.025f);
	glVertex2f(0.23f, 0.18f);
	glVertex2f(0.25f, 0.09f);
	glEnd();

	glColor3f(0.5f, 0.2f, 0.0f);
	drawFilledCircle3(0.15, 0.29, 0.12);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(0.05f, 0.28f);
	glVertex2f(0.1f, 0.28f);
	glVertex2f(0.09f, 0.32f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.6f);
	glVertex2f(0.09f, 0.28f);
	glVertex2f(0.25f, 0.28f);
	glVertex2f(0.15f, 0.32f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.18, 0.28, 0.02);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.12, 0.28, 0.02);

	glColor3f(0.4f, 0.6f, 0.5f);
	drawHollowCircle(0.18, 0.28, 0.01);


	glColor3f(0.4f, 0.7f, 0.7f);
	drawFilledCircle(0.12, 0.28, 0.009);

	glColor3f(0.4f, 0.7f, 0.7f);
	drawFilledCircle(0.18, 0.28, 0.009);

	glColor3f(0.4f, 0.6f, 0.5f);
	drawHollowCircle(0.12, 0.28, 0.009);

	// cheeks
	glPushMatrix();
	glScalef(0.12, 0.48, 1.0);
	glColor3f(1.0f, 0.6f, 0.5f);
	OvalFilled(0.65, 0.51, 0.02);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.12, 0.48, 1.0);
	glColor3f(1.0f, 0.6f, 0.5f);
	OvalFilled(1.8, 0.51, 0.02);
	glPopMatrix();

	// Mouse
	glPushMatrix();
	glScalef(0.12, 0.48, 1.0);
	glColor3f(1.0f, 0.3f, 0.3f);
	OvalFilled3(1.25, 0.5, 0.05);
	glPopMatrix();

	// Hat
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.09f, 0.39f);
	glVertex2f(0.22f, 0.39f);
	glVertex2f(0.22f, 0.52f);
	glVertex2f(0.09f, 0.52f);
	glEnd();

	glLineWidth(0.9f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.09, 0.42f);
	glVertex2f(0.22f, 0.42f);
	glEnd();

	glLineWidth(0.9f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, 0.52f);
	glVertex2f(0.12f, 0.42f);
	glEnd();

	glLineWidth(0.9f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.15f, 0.52f);
	glVertex2f(0.15f, 0.42f);
	glEnd();

	glLineWidth(0.9f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.19f, 0.52f);
	glVertex2f(0.19f, 0.42f);
	glEnd();

	// Hair
	glPushMatrix();
	glScalef(0.13, 0.49, 1.0);
	glColor3f(0.5f, 0.2f, 0.0f);
	OvalFilled(0.16, 0.6, 0.1);
	glPopMatrix();

	// Shose
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.6f, 0.8f);
	glVertex2f(0.06f, -0.25f);
	glVertex2f(0.12f, -0.25f);
	glVertex2f(0.12f, -0.22f);
	glVertex2f(0.06f, -0.22f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.6f, 0.8f);
	glVertex2f(0.18f, -0.25f);
	glVertex2f(0.25f, -0.25f);
	glVertex2f(0.25f, -0.22f);
	glVertex2f(0.18f, -0.22f);
	glEnd();


}
void Floor()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.7f, 0.8f);
	glVertex2f(-0.99f, -0.99f);
	glVertex2f(0.99f, -0.99f);
	glVertex2f(0.99f, -0.2f);
	glVertex2f(-0.99f, -0.2f);
	glEnd();

	glLineWidth(10.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.5, 0.6);
	glVertex2f(0.99f, -0.25f);
	glVertex2f(-0.99f, -0.25f);

	glVertex2f(0.99f, -0.50f);
	glVertex2f(-0.99f, -0.50f);

	glVertex2f(0.99f, -0.80f);
	glVertex2f(-0.99f, -0.80f);


	glVertex2f(0.0f, -0.2f);
	glVertex2f(0.0f, -0.99f);

	glVertex2f(0.50f, -0.2f);
	glVertex2f(0.50f, -0.99f);

	glVertex2f(-0.50f, -0.2f);
	glVertex2f(-0.50f, -0.99f);
	glEnd();

}
void Lamp() {

	glEnable(GL_LINE_STIPPLE);
	glLineWidth(2.0f);
	glLineStipple(2, 0xAAAA);
	glBegin(GL_LINES);
	glColor3f(0.4f, 0.4f, 0.5f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.9f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.7f, 0.5f);
	glVertex2f(-0.02f, 0.90f);
	glVertex2f(0.02f, 0.90f);
	glVertex2f(0.03f, 0.89f);
	glVertex2f(-0.03f, 0.89f);
	glEnd();


	glLineWidth(0.9f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.4f, 0.4f, 0.5f);
	glVertex2f(-0.02f, 0.90f);
	glVertex2f(0.02f, 0.90f);
	glVertex2f(0.03f, 0.89f);
	glVertex2f(-0.03f, 0.89f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.7f, 0.5f);
	glVertex2f(-0.04f, 0.89f);
	glVertex2f(0.04f, 0.89f);
	glVertex2f(0.05f, 0.83f);
	glVertex2f(-0.05f, 0.83f);
	glEnd();


	glLineWidth(0.9f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.4f, 0.4f, 0.5f);
	glVertex2f(-0.04f, 0.89f);
	glVertex2f(0.04f, 0.89f);
	glVertex2f(0.05f, 0.83f);
	glVertex2f(-0.05f, 0.83f);
	glEnd();



	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.7f, 0.5f);
	glVertex2f(-0.05f, 0.83f);
	glVertex2f(0.05f, 0.83f);
	glVertex2f(0.04f, 0.79f);
	glVertex2f(-0.04f, 0.79f);
	glEnd();

	glLineWidth(0.9f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.4f, 0.4f, 0.5f);
	glVertex2f(-0.05f, 0.83f);
	glVertex2f(0.05f, 0.83f);
	glVertex2f(0.04f, 0.79f);
	glVertex2f(-0.04f, 0.79f);
	glEnd();


	glColor3f(0.8f, 0.7f, 0.5f);
	OvalFilled2(0.01f, 0.72, 0.08f);

	glColor3f(0.4f, 0.4f, 0.5f);
	OvalHollow2(0.01f, 0.72, 0.08f);

	glColor3f(0.4f, 0.4f, 0.5f);
	OvalHollow3(0.01f, 0.73, 0.03f);


	glColor3f(1.0f, 1.0f, 0.1f);
	drawFilledCircle2(0.01f, 0.72f, 0.06f);
}

void Whisk()
{
	// drawing the filled circle
	glColor3f(0.8f, 0.6f, 0.9f);
	drawFilledCircle(0, 0, .01);

	// drawing the border around the circle
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0, 0, .01);


	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.6f, 0.9f);
	glVertex2f(0.0f, -0.01f);
	glVertex2f(0.01f, 0.0f);
	glVertex2f(0.08f, -0.12f);
	glVertex2f(0.07f, -0.13f);
	glEnd();


	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, -0.01f);
	glVertex2f(0.01f, 0.0f);
	glVertex2f(0.08f, -0.12f);
	glVertex2f(0.07f, -0.13f);
	glEnd();



	glPushMatrix();
	glTranslatef(-0.008, -0.34, 0);
	glRotatef(115, 0, 0, 1);
	glScalef(0.3, 0.2, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(0.34f, -0.9f, 0.2f);
	glPopMatrix();
	glutSwapBuffers();


	glPushMatrix();
	glTranslatef(0.045, -0.19, 0);
	glRotatef(128, 0, 0, 1);
	glScalef(0.3, 0.4, 1);
	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.08f, -0.17f, 0.05f);
	glPopMatrix();
	glutSwapBuffers();


	glLineWidth(0.9f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.075f, -0.12f);
	glVertex2f(0.15f, -0.21f);
	glEnd();
}
void bowl() {

	glBegin(GL_QUADS);
	glColor4f(0.7f, 0.9f, 1.0f, 0.5f); // Set color to blue
	glVertex2f(-0.06f, 0.0f);
	glVertex2f(-0.06f, 0.01f);
	glVertex2f(0.06f, 0.01f);
	glVertex2f(0.06f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.06f, 0.0f);
	glVertex2f(-0.06f, 0.01f);

	glVertex2f(-0.06f, 0.01f);
	glVertex2f(0.06f, 0.01f);

	glVertex2f(0.06f, 0.01f);
	glVertex2f(0.06f, 0.0f);

	glVertex2f(0.06f, 0.0f);
	glVertex2f(-0.06f, 0.0f);


	glEnd();

	glColor4f(0.7f, 0.9f, 1.0f, 0.8f); // Set color to blue
	drawFilledCircle2(0.0, 0.31, 0.3);

	glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
	drawHollowCircle4(0.0, 0.31, 0.3);

	glColor3f(0.7f, 0.9f, 1.0f); // Set color to blue
	drawFilledCircle4(0.0, 0.3, 0.1, 0.3);

	glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
	drawHollowCircle2(0.0, 0.3, 0.1, 0.3);
}

void colorB() {
	// draw Brown  
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.2f, 0.0f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.9f, 0.9f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.35f, 0.25f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.25f, 0.25f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.4f, 0.2f, 0.0f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}
void colorW() {
	// draw White  
	glBegin(GL_QUADS);
	glColor3f(0.9725f, 0.8862f, .69411f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.9f, 0.9f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.35f, 0.25f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.25f, 0.25f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.9725f, 0.8862f, .69411f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(0.3f, 0.1f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

void MixtureC() {

	glLineWidth(1.0f);

	glColor3f(0.4f, 0.4f, 0.4f);
	OvalFilled(-0.4, 0.29, 0.09);


	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.29, 0.09);

	/////
	glColor3f(0.8f, 0.8f, 0.8f);
	OvalFilled(-0.4, 0.35, 0.10);


	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.35, 0.10);

	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.30, 0.10);

	////////////////

	glColor3f(0.9725f, 0.8862f, .69411f);   // cake
	OvalFilled(-0.4, 0.34, 0.08);


}
void MixtureR() {
	glLineWidth(1.0f);

	glColor3f(0.4f, 0.4f, 0.4f);
	OvalFilled(-0.4, 0.29, 0.09);


	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.29, 0.09);

	/////
	glColor3f(0.8f, 0.8f, 0.8f);
	OvalFilled(-0.4, 0.35, 0.10);


	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.35, 0.10);

	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.30, 0.10);

	////////////////

	glColor3f(0.6f, 0.0f, 0.0f);
	OvalFilled(-0.4, 0.34, 0.08);


}

void Milk()
{
	glLineWidth(1.0f);
	glBegin(GL_QUADS);
	//Milk interface 
	glColor3f(0.8784f, 0.8784f, 0.8784f);
	glVertex2f(-0.35f, 0.0f);
	glVertex2f(-0.2f, 0.0f);
	glVertex2f(-0.2f, 0.3f);
	glVertex2f(-0.35f, 0.28f);
	//left
	glVertex2f(-0.4f, 0.03f);
	glVertex2f(-0.35f, 0.0f);
	glVertex2f(-0.35f, 0.28f);
	glVertex2f(-0.4f, 0.3f);
	//top 
	glVertex2f(-0.35f, 0.28f);
	glVertex2f(-0.2f, 0.3f);
	glVertex2f(-0.24f, 0.36f);
	glVertex2f(-0.38f, 0.35f);
	//The skinny rectangle at the top
	glVertex2f(-0.38f, 0.35f);
	glVertex2f(-0.24f, 0.35f);
	glVertex2f(-0.24f, 0.38f);
	glVertex2f(-0.38f, 0.38f);

	glEnd();

	glBegin(GL_TRIANGLES);  // Begin drawing triangles
	glColor3f(0.8984f, 0.8984f, 0.8984f);  // Set color to red (R, G, B)


	glVertex2f(-0.35f, 0.28f);   // Vertex 1
	glVertex2f(-0.4f, 0.3f);   // Vertex 2
	glVertex2f(-0.36f, 0.31f);  // Vertex 3

	glVertex2f(-0.4f, 0.3f);   // Vertex 1
	glVertex2f(-0.38f, 0.35f);   // Vertex 2
	glVertex2f(-0.36f, 0.31f);  // Vertex 3

	glEnd();  // End drawing triangles

	// drawing the border around the circle

	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle(-0.31, 0.1, .041);
	// drawing the filled circle
	glColor3f(0.7f, 0.8f, 0.9f);
	drawFilledCircle(-0.31, 0.1, .04);


	glPushMatrix();
	glTranslatef(-0.33, -0.079, 0.0);
	glRotatef(-90, 0.0f, 0.f, 1.0f);
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle3(-0.21, 0.13, .0381, .0381);
	// drawing the filled circle
	glColor3f(0.7f, 0.8f, 0.9f);
	drawFilledCircle2(-0.21, 0.13, .038);
	glPopMatrix();
	// drawing the border around the circle
	glColor3f(0.3764, 0.3764, 0.3764);
	drawHollowCircle(-0.27, 0.17, .038);
	// drawing the filled circle
	glColor3f(0.8784f, 0.8784f, 0.8784f);
	drawFilledCircle(-0.27, 0.17, .038);

	glBegin(GL_QUADS);
	glColor3f(0.8784f, 0.8784f, 0.8784f);
	glVertex2f(-0.3f, 0.14f);
	glVertex2f(-0.222f, 0.17f);
	glVertex2f(-0.24f, 0.21f);
	glVertex2f(-0.35f, 0.21f);

	glColor3f(0.7f, 0.8f, 0.9f);
	glVertex2f(-0.35f, 0.0f);
	glVertex2f(-0.2f, 0.0f);
	glVertex2f(-0.2f, 0.15f);
	glVertex2f(-0.35f, 0.1f);

	glEnd();

	glBegin(GL_LINES);


	// line 1 
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.35, 0.0);
	glVertex2f(-0.2, 0.0);
	// line 2
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.2, 0.3);
	glVertex2f(-0.2, 0.0);
	// line 3
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.2, 0.3);
	glVertex2f(-0.35, 0.29);
	//line 4
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.35, 0.28);
	glVertex2f(-0.35, 0.0);
	// line 5
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.24, 0.36);
	glVertex2f(-0.2, 0.3);
	//line 6
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.24, 0.36);
	glVertex2f(-0.38, 0.35);
	//line 7
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.35, 0.28);
	glVertex2f(-0.38, 0.35);
	//line 8
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.38, 0.38);
	glVertex2f(-0.38, 0.35);
	//line 9
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.38, 0.38);
	glVertex2f(-0.24, 0.38);
	//line 10
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.24, 0.35);
	glVertex2f(-0.24, 0.38);
	//line 11
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.4, 0.3);
	glVertex2f(-0.38, 0.35);
	//line 12
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.4, 0.3);
	glVertex2f(-0.36, 0.31);
	//line 13
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.4, 0.3);
	glVertex2f(-0.35, 0.29);
	//line 14
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.4, 0.3);
	glVertex2f(-0.4, 0.03);
	//line 15
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.35, 0.0);
	glVertex2f(-0.4, 0.03);

	//M
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.33, 0.22);
	glVertex2f(-0.33, 0.25);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.31, 0.25);
	glVertex2f(-0.33, 0.25);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.31, 0.25);
	glVertex2f(-0.31, 0.22);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.31, 0.25);
	glVertex2f(-0.29, 0.25);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.29, 0.22);
	glVertex2f(-0.29, 0.25);

	//I
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.275, 0.25);
	glVertex2f(-0.275, 0.22);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.277, 0.25);
	glVertex2f(-0.271, 0.25);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.277, 0.22);
	glVertex2f(-0.271, 0.22);

	//L
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.26, 0.25);
	glVertex2f(-0.26, 0.22);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.26, 0.22);
	glVertex2f(-0.245, 0.22);

	//K
	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.23, 0.25);
	glVertex2f(-0.23, 0.22);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.215, 0.25);
	glVertex2f(-0.23, 0.235);

	glColor3f(0.3764, 0.3764, 0.3764);
	glVertex2f(-0.212, 0.22);
	glVertex2f(-0.23, 0.237);

	glEnd();

}
void Butter()
{

	glLineWidth(1.0f);
	glBegin(GL_QUADS);
	//square
	glColor3f(1.0f, 1.0f, 0.4f); // Set color to black
	glVertex2f(-0.3f, -0.26f);   // Bottom-left vertex
	glVertex2f(-0.24f, -0.24f);    // Bottom-right vertex
	glVertex2f(-0.24f, -0.17f);     // Top-right vertex
	glVertex2f(-0.3f, -0.19f);    // Top-left vertex
	//Top rectangle
	glColor3f(1.0f, 1.0f, 0.4f); // Set color to black
	glVertex2f(-0.50f, -0.16f);   // Bottom-left vertex
	glVertex2f(-0.3f, -0.2f);    // Bottom-right vertex
	glVertex2f(-0.24f, -0.17f);     // Top-right vertex
	glVertex2f(-0.46f, -0.12f);    // Top-left vertex
	//Front rectangle
	glColor3f(1.0f, 1.0f, 0.4f); // Set color to black
	glVertex2f(-0.51f, -0.21f);   // Bottom-left vertex
	glVertex2f(-0.3f, -0.26f);    // Bottom-right vertex
	glVertex2f(-0.3f, -0.2f);     // Top-right vertex
	glVertex2f(-0.50f, -0.16f);    // Top-left vertex

	glEnd();

	glBegin(GL_LINES);
	// line 1
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.3f, -0.26f);
	glVertex2f(-0.24f, -0.24f);
	// line 2
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.24f, -0.17f);
	glVertex2f(-0.24f, -0.24f);
	// line 3
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.24f, -0.17f);
	glVertex2f(-0.3f, -0.19f);
	// line 4
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.3f, -0.26f);
	glVertex2f(-0.3f, -0.19f);
	// line 5
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.3f, -0.26f);
	glVertex2f(-0.51f, -0.21f);
	// line 6
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.49f, -0.14f);
	glVertex2f(-0.51f, -0.21f);
	// line 7
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.49f, -0.145f);
	glVertex2f(-0.3f, -0.19f);
	// line 8
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.49f, -0.14f);
	glVertex2f(-0.45f, -0.12f);
	// line 9
	glColor3f(0.7784, 0.7784, 0.7784);
	glVertex2f(-0.24f, -0.17f);
	glVertex2f(-0.45f, -0.12f);

	glEnd();


}
void Flour()
{
	glLineWidth(1.0f);
	glBegin(GL_QUADS);
	//bottom front
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.1f, 0.01f);
	glVertex2f(0.08f, 0.0f);    // Bottom-right vertex
	glVertex2f(0.08f, 0.13f);     // Top-right vertex
	glVertex2f(-0.1f, 0.14f);    // Top-left vertex
	//top front
	glVertex2f(-0.1f, 0.19f);   // Bottom-left vertex
	glVertex2f(0.08f, 0.18f);    // Bottom-right vertex
	glVertex2f(0.08f, 0.24f);     // Top-right vertex
	glVertex2f(-0.1f, 0.26f);    // Top-left vertex
	//top
	glVertex2f(-0.1f, 0.26f);   // Bottom-left vertex
	glVertex2f(0.08f, 0.24f);    // Bottom-right vertex
	glVertex2f(0.1f, 0.29f);     // Top-right vertex
	glVertex2f(-0.05f, 0.3f);    // Top-left vertex
	//bottom right
	glVertex2f(0.08f, 0.0f);   // Bottom-left vertex
	glVertex2f(0.12f, 0.02f);    // Bottom-right vertex
	glVertex2f(0.12f, 0.15f);     // Top-right vertex
	glVertex2f(0.08f, 0.13f);    // Top-left vertex
	//top right
	glVertex2f(0.08f, 0.18f);   // Bottom-left vertex
	glVertex2f(0.12f, 0.2f);    // Bottom-right vertex
	glVertex2f(0.12f, 0.28f);     // Top-right vertex
	glVertex2f(0.08f, 0.24f);    // Top-left vertex
	//Dark Rectangle
	glColor3f(0.8f, 0.9f, 1.0f);
	glVertex2f(-0.1f, 0.13f);   // Bottom-left vertex
	glVertex2f(0.08f, 0.12f);    // Bottom-right vertex
	glVertex2f(0.08f, 0.18f);     // Top-right vertex
	glVertex2f(-0.1f, 0.19f);    // Top-left vertex
	//right Dark squere
	glVertex2f(0.08f, 0.12f);   // Bottom-left vertex
	glVertex2f(0.12f, 0.14f);    // Bottom-right vertex
	glVertex2f(0.12f, 0.2f);     // Top-right vertex
	glVertex2f(0.08f, 0.18f);    // Top-left vertex


	glEnd();

	glBegin(GL_TRIANGLES);  // Begin drawing triangles

	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex2f(0.08f, 0.24f);   // Vertex 1
	glVertex2f(0.1f, 0.29f);   // Vertex 2
	glVertex2f(0.12f, 0.28f);  // Vertex 3

	glEnd();

	glBegin(GL_LINES);
	// line 1
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(-0.1f, 0.01f);
	glVertex2f(0.08f, 0.0f);
	// line 2
	glVertex2f(0.08f, 0.0f);
	glVertex2f(0.12f, 0.02f);
	// line 3
	glVertex2f(0.12f, 0.28f);
	glVertex2f(0.12f, 0.02f);
	// line 4
	glVertex2f(0.12f, 0.28f);
	glVertex2f(0.08f, 0.24f);
	// line 5
	glVertex2f(0.08f, 0.18f);
	glVertex2f(0.08f, 0.24f);
	// line 6
	glVertex2f(0.08f, 0.18f);
	glVertex2f(0.12f, 0.2f);
	// line 7
	glVertex2f(0.08f, 0.18f);
	glVertex2f(-0.1f, 0.19f);
	// line 8
	glVertex2f(-0.1f, 0.26f);
	glVertex2f(-0.1f, 0.01f);
	// line 9
	glVertex2f(-0.1f, 0.26f);
	glVertex2f(-0.05f, 0.3f);
	// line 10
	glVertex2f(0.1f, 0.29f);
	glVertex2f(-0.05f, 0.3f);
	// line 11
	glVertex2f(0.1f, 0.28f);
	glVertex2f(0.12f, 0.28f);
	// line 12
	glVertex2f(0.11f, 0.29f);
	glVertex2f(0.08f, 0.24f);
	// line 13
	glVertex2f(-0.1f, 0.25f);
	glVertex2f(0.08f, 0.24f);
	// line 14
	glVertex2f(-0.1f, 0.13f);
	glVertex2f(0.08f, 0.12f);
	// line 15
	glVertex2f(0.12f, 0.14f);
	glVertex2f(0.08f, 0.12f);
	// line 16
	glVertex2f(0.08f, 0.0f);
	glVertex2f(0.08f, 0.12f);
	//////////////////////////////////////////////////
	// F
	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(-0.07f, 0.13f);
	glVertex2f(-0.07f, 0.17f);

	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(-0.045f, 0.17f);
	glVertex2f(-0.07f, 0.17f);

	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(-0.05f, 0.15f);
	glVertex2f(-0.07f, 0.15f);

	// l
	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(-0.035f, 0.13f);
	glVertex2f(-0.035f, 0.17f);

	// u
	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(0.02f, 0.155f);
	glVertex2f(0.02f, 0.126f);

	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(0.035f, 0.126f);
	glVertex2f(0.02f, 0.126f);

	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(0.035f, 0.127f);
	glVertex2f(0.035f, 0.155f);

	//r
	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(0.045f, 0.126f);
	glVertex2f(0.045f, 0.155f);

	glColor3f(0.5784, 0.5784, 0.5784);
	glVertex2f(0.055f, 0.155f);
	glVertex2f(0.045f, 0.145f);


	glEnd();
	//o
	glColor3f(0.5784, 0.5784, 0.5784);
	drawHollowCircle(-0.01, 0.143, .015);
}
void BreakEgg() {

	glColor4f(1.0f, 1.0f, 0.9f, .8f);            // white
	drawFilledCircle(-0.02f, 0.005f, 0.1);

	glColor4f(1.0f, 1.0f, 0.0f, .8f);            // yellow
	drawFilledCircle(-0.02f, 0.0f, 0.05);

	////////////////////
	glPushMatrix();
	glRotatef(70, 0, 0, 1);
	glColor3f(1.0f, 0.8f, 0.6f);
	drawFilledCircle3(0.1, 0.1, 0.1);
	glPopMatrix();


	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex2f(-0.05f, 0.15f);
	glVertex2f(-0.06f, 0.2f);
	glVertex2f(-0.02f, 0.22f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex2f(-0.073f, 0.09f);
	glVertex2f(-0.08f, 0.16f);
	glVertex2f(-0.04f, 0.18f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.093f, 0.03f);
	glVertex2f(-0.096f, 0.1f);
	glVertex2f(-0.07f, 0.1f);
	glEnd();

	////////////

	glPushMatrix();
	glTranslatef(-0.46, -0.6, 0);
	glRotatef(-70, 0, 0, 1);
	glColor3f(1.0f, 0.8f, 0.6f);
	drawFilledCircle3(-0.5, 0.7, 0.1);
	glPopMatrix();



	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex2f(-0.01f, 0.2f);
	glVertex2f(0.02f, 0.13f);
	glVertex2f(0.04f, 0.17f);
	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex2f(0.01f, 0.15f);
	glVertex2f(0.03f, 0.09f);
	glVertex2f(0.06f, 0.11f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.034f, 0.09f);
	glVertex2f(0.05f, 0.02f);
	glVertex2f(0.07f, 0.07f);
	glEnd();


}
// brokenegg
void egg() {

	glColor3f(1.0f, 0.9f, 0.8f);
	drawFilledCircle4(0.0, 0.1, 0.05, 0.035);

	glColor3f(1.0f, 0.8f, 0.8f);
	drawHollowCircle2(0.0, 0.1, 0.05, 0.035);
}

void bowlButter()
{
	glPushMatrix();
	glScalef(0.4, 0.5, 1.0);
	glTranslatef(0.3, -0.13, 0.0);
	Butter();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowl();
	glPopMatrix();


}
void bowlEgg()
{
	bowl();
	glPushMatrix();
	glScalef(0.5, 0.6, 1.0);
	glTranslatef(0.2, 0.35, 0.0);
	Butter();
	glPopMatrix();

	glColor4f(0.9f, 0.9f, 0.9f, .8f);
	drawFilledCircle4(0.03, 0.11, 0.06, 0.12);

	glColor4f(1.0f, 1.0f, 0.6f, .8f);
	drawFilledCircle4(0.04, 0.1, 0.04, 0.04);

}
void bowlMilk()
{
	bowlEgg();

	glPushMatrix();
	glScalef(0.5, 0.6, 1.0);
	glTranslatef(0.2, 0.35, 0.0);
	Butter();
	glPopMatrix();


	glColor4f(1.0f, 1.0f, 1.0f, .7f);
	drawFilledCircle4(0.08, 0.12, 0.07, 0.12);


}
void bowlFlour()
{
	bowlMilk();
	glColor4f(0.9f, 0.9f, 0.9f, .7f);
	drawFilledCircle4(-0.05, 0.135, 0.08, 0.09);

	glColor4f(0.9f, 0.9f, 0.9f, .7f);
	drawFilledCircle4(0.11, 0.125, 0.08, 0.09);

	glColor4f(0.9f, 0.9f, 0.9f, .7f);
	drawFilledCircle4(-0.09, 0.135, 0.08, 0.09);

	glPushMatrix();
	glScalef(0.5, 0.6, 1.0);
	glTranslatef(0.3, 0.35, 0.0);
	Butter();
	glPopMatrix();

	//
	glColor4f(0.9f, 0.9f, 0.9f, .7f);
	drawFilledCircle4(0.03, 0.11, 0.07, 0.12);

	glColor4f(1.0f, 1.0f, 1.0f, .7f);
	drawFilledCircle4(0.08, 0.12, 0.07, 0.12);
	//



}


void window() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.1, 0.02); glVertex3f(0.13, 0.15, 0);
	glTexCoord2f(1.1, 0.02); glVertex3f(1.17, 0.15, 0);
	// ////.... continue the other vertices and texCoord
	glTexCoord2f(1.1, 1.0); glVertex3f(1.17, 1.2, 0);
	glTexCoord2f(0.1, 1.0); glVertex3f(0.13, 1.2, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void butterPlate() {

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle4(-0.36, -0.21, 0.09, 0.26);

	glColor3f(0.8f, 0.8f, 0.8f);
	drawHollowCircle2(-0.36, -0.21, 0.09, 0.26);
}
void BakePan() {

	glColor3f(0.4f, 0.4f, 0.4f);
	OvalFilled(-0.4, 0.29, 0.09);

	glColor3f(0.8f, 0.8f, 0.8f);
	OvalFilled(-0.4, 0.35, 0.10);

	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.35, 0.10);

	glColor3f(0.0f, 0.0f, 0.0f);
	OvalHollow(-0.4, 0.30, 0.10);
}

void BakedCakeC()
{
	//plate 
	glColor3f(0.5f, 0.5f, 0.5f);
	drawHollowCircle3(0.0, -0.07, .08, .26);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle4(0.0, -0.07, .08, .26);
	//
	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(0.0, -0.07, .05, .2);

	glColor3f(1.0f, 0.8f, 0.6f);
	drawHollowCircle3(0.0, -0.07, .05, .2);
	//
	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(0.191, 0.02, .1, .015);

	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(-0.191, 0.02, .1, .014);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.88f, 0.68f); // Set color to black
	glVertex2f(-0.18f, -0.08f);   // Bottom-left vertex
	glVertex2f(0.18f, -0.08f);    // Bottom-right vertex
	glVertex2f(0.18f, 0.1f);     // Top-right vertex
	glVertex2f(-0.18f, 0.1f);    // Top-left vertex
	glEnd();

	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(0.19, 0.02, .1, .015);

	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(-0.19, 0.02, .1, .014);


	///
	glColor3f(1.0f, 0.84f, 0.64f);
	drawFilledCircle4(0.0, 0.1, .07, .2);


	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(0.0, 0.11, .07, .2);

	glColor3f(1.0f, 0.84f, 0.64f);
	drawFilledCircle4(0.0, 0.1, .05, .2);

}
void BakedCakeR()
{
	// plate 
	glColor3f(0.5f, 0.5f, 0.5f);
	drawHollowCircle3(0.0, -0.07, .08, .26);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle4(0.0, -0.07, .08, .26);
	//
	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(0.0, -0.07, .05, .2);

	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.0, -0.07, .05, .2);
	//
	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.191, 0.02, .1, .015);

	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(-0.191, 0.02, .1, .014);

	glBegin(GL_QUADS);

	glColor3f(.506274f, 0.12764f, 0.12764f); // Set color to black
	glVertex2f(-0.18f, -0.08f);   // Bottom-left vertex
	glVertex2f(0.18f, -0.08f);    // Bottom-right vertex
	glVertex2f(0.18f, 0.1f);     // Top-right vertex
	glVertex2f(-0.18f, 0.1f);    // Top-left vertex
	glEnd();

	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(0.19, 0.02, .1, .015);

	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(-0.19, 0.02, .1, .014);


	///
	glColor3f(.46274f, 0.10764f, 0.10764f);
	drawFilledCircle4(0.0, 0.1, .07, .2);


	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.0, 0.11, .07, .2);

	glColor3f(.46274f, 0.10764f, 0.10764f);
	drawFilledCircle4(0.0, 0.1, .05, .2);
}
void BakedCakeInOvenC() {

	glPushMatrix();
	glScalef(1.13, 1.0, 1.0);
	glTranslatef(0.4, -0.34, 0.0);
	BakePan();
	glPopMatrix();

	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(0.0, -0.03, .05, .2);

	glColor3f(1.0f, 0.8f, 0.6f);
	drawHollowCircle3(0.0, -0.03, .05, .2);
	//
	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(0.191, 0.04, .08, .013);

	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(-0.191, 0.04, .08, .012);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.88f, 0.68f); // Set color to black
	glVertex2f(-0.18f, -0.05f);   // Bottom-left vertex
	glVertex2f(0.18f, -0.05f);    // Bottom-right vertex
	glVertex2f(0.18f, 0.1f);     // Top-right vertex
	glVertex2f(-0.18f, 0.1f);    // Top-left vertex
	glEnd();

	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(0.19, 0.04, .08, .013);

	glColor3f(1.0f, 0.86f, 0.66f);
	drawFilledCircle4(-0.19, 0.04, .08, .012);


	///
	glColor3f(1.0f, 0.84f, 0.64f);
	drawFilledCircle4(0.0, 0.1, .07, .2);


	glColor3f(1.0f, 0.79f, 0.59f);
	drawHollowCircle3(0.0, 0.1, .07, .2);

	glColor3f(1.0f, 0.84f, 0.64f);
	drawFilledCircle4(0.0, 0.1, .05, .2);

}
void BakedCakeInOvenR()
{
	glPushMatrix();
	glScalef(1.13, 1.0, 1.0);
	glTranslatef(0.4, -0.34, 0.0);
	BakePan();
	glPopMatrix();

	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(0.0, -0.03, .05, .2);

	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.0, -0.03, .05, .2);
	//
	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.191, 0.04, .08, .013);

	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(-0.191, 0.04, .08, .012);

	glBegin(GL_QUADS);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	glVertex2f(-0.18f, -0.05f);   // Bottom-left vertex
	glVertex2f(0.18f, -0.05f);    // Bottom-right vertex
	glVertex2f(0.18f, 0.1f);     // Top-right vertex
	glVertex2f(-0.18f, 0.1f);    // Top-left vertex
	glEnd();

	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(0.19, 0.04, .08, .013);

	glColor3f(.486274f, 0.11764f, 0.11764f);
	drawFilledCircle4(-0.19, 0.04, .08, .012);


	///
	glColor3f(.46274f, 0.10764f, 0.10764f);
	drawFilledCircle4(0.0, 0.1, .07, .2);


	glColor3f(.39274f, 0.10764f, 0.10764f);
	drawHollowCircle3(0.0, 0.1, .07, .2);

	glColor3f(.46274f, 0.10764f, 0.10764f);
	drawFilledCircle4(0.0, 0.1, .05, .2);
}

void carrot()
{
	glColor3f(0.99f, .59f, 0.0f);
	drawFilledCircle3(-.325, .09, .019);

	glBegin(GL_TRIANGLES);  // Begin drawing triangles
	glColor3f(0.99f, .59f, 0.0f);

	glVertex2f(-0.305f, 0.09f);  // Vertex 1
	glVertex2f(-0.345f, 0.09f);  // Vertex 2
	glVertex2f(-0.325f, 0.03f);  // Vertex 3
	///
	glColor3f(0.29803f, .6f, 0.0f);
	glVertex2f(-0.32f, 0.107f);  // Vertex 1
	glVertex2f(-0.345f, 0.134f);  // Vertex 2
	glVertex2f(-0.335f, 0.107f);  // Vertex 3

	glColor3f(0.29803f, .6f, 0.0f);
	glVertex2f(-0.315f, 0.107f);  // Vertex 1
	glVertex2f(-0.325f, 0.145f);  // Vertex 2
	glVertex2f(-0.33f, 0.107f);  // Vertex 3

	glColor3f(0.29803f, .6f, 0.0f);
	glVertex2f(-0.313f, 0.107f);  // Vertex 1
	glVertex2f(-0.305f, 0.134f);  // Vertex 2
	glVertex2f(-0.325f, 0.107f);  // Vertex 3

	glEnd();  // End drawing triangles

	glBegin(GL_LINES);
	//glColor3f(0.99f, .59f, 0.0f);
	glColor3f(0.88f, .48f, 0.0f);
	glVertex2f(-0.335f, 0.09f);
	glVertex2f(-0.325f, 0.09f);

	glColor3f(0.88f, .48f, 0.0f);
	glVertex2f(-0.315f, 0.08f);
	glVertex2f(-0.325f, 0.08f);

	glColor3f(0.88f, .48f, 0.0f);
	glVertex2f(-0.32f, 0.07f);
	glVertex2f(-0.333f, 0.07f);

	glColor3f(0.88f, .48f, 0.0f);
	glVertex2f(-0.322f, 0.05f);
	glVertex2f(-0.33f, 0.05f);

	glEnd();
}
void Candle()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, .834117, .834117);
	glVertex2f(0.15f, 0.1f);   // Bottom-left vertex
	glVertex2f(0.2f, 0.1f);    // Bottom-right vertex
	glVertex2f(0.2f, 0.2f);     // Top-right vertex
	glVertex2f(0.15f, 0.2f);    // Top-left vertex
	glEnd();

	glBegin(GL_LINES);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.15f, 0.1f);
	glVertex2f(0.15f, 0.195f);

	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.2f, 0.195f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	drawHollowCircle2(.175, .19, .01, .025);

	glPushMatrix();
	glScalef(.5, .5, 0.0);
	glTranslatef(0.86, -0.125, 0.0);
	ovenHearts();
	glPopMatrix();

	glPushMatrix();
	glScalef(.5, .5, 0.0);
	glTranslatef(0.89, -0.175, 0.0);
	ovenHearts();
	glPopMatrix();

	glPushMatrix();
	glScalef(.5, .5, 0.0);
	glTranslatef(0.86, -0.22, 0.0);
	ovenHearts();
	glPopMatrix();

	glBegin(GL_LINES);
	glColor3f(0.4764, 0.4764, 0.4764);
	glVertex2f(0.175f, 0.21f);
	glVertex2f(0.175f, 0.19f);
	glEnd();

	glColor4f(0.89235, .04921, .04921, .7);
	drawFilledCircle4(.175, .21, .013, .007);

	glBegin(GL_TRIANGLES);
	glColor4f(0.89235, .05921, .05921, .5);

	glVertex2f(0.1742f, 0.22f);
	glVertex2f(0.1758f, 0.22f);
	glVertex2f(0.175f, 0.3f);

	glEnd();

}

void creamCakeCW()// currot & white cream
{
	BakedCakeC();

	glBegin(GL_QUADS);

	glColor3f(0.99215f, .969019f, .89843f); // Set color to black
	glVertex2f(-0.192f, -0.02f);   // Bottom-left vertex
	glVertex2f(0.192f, -0.02f);    // Bottom-right vertex
	glVertex2f(0.192f, 0.08f);     // Top-right vertex
	glVertex2f(-0.192f, 0.08f);    // Top-left vertex
	glEnd();

	glColor3f(0.99215f, .999019f, .90843f);
	drawFilledCircle4(0.0, 0.1, .07, .205);

	glColor3f(0.98215f, .989019f, .90843f);
	drawHollowCircle3(0.0, 0.1, .07, .205);

	glColor3f(0.99215f, .999019f, .90843f);
	drawFilledCircle4(0.0, 0.1, .05, .205);
	///
	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.20, 0.03, .09, .01);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.20, 0.03, .09, .01);
	//
	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.17, -0.02, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.14, -0.02, .055, .017);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.105, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.065, -0.03, .050, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.02, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.015, -0.02, .04, .016);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.05, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.051, -0.03, .055, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.1, -0.025, .024, .024);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.14, -0.03, .055, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.18, -0.02, .015, .015);
	//
	glPushMatrix();
	glTranslatef(0.21, 0.09, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(0, 0.0f, 0.3f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.06, 0.28, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(60, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.11, 0.30, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(90, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, 0.295, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(120, 0.0f, 0.0f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.24, 0.1, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(180, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, -0.09, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(240, 0.0f, 0.0f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.14, -0.07, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(300, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.1, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(270, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();


}
void creamCakeCB()//currot & brown cream 
{
	BakedCakeC();

	glBegin(GL_QUADS);

	glColor3f(0.48627f, .305882f, 0.0f);
	glVertex2f(-0.192f, -0.02f);   // Bottom-left vertex
	glVertex2f(0.192f, -0.02f);    // Bottom-right vertex
	glVertex2f(0.192f, 0.08f);     // Top-right vertex
	glVertex2f(-0.192f, 0.08f);    // Top-left vertex
	glEnd();

	glColor3f(0.50627f, .325882f, 0.0f);
	drawFilledCircle4(0.0, 0.1, .07, .205);

	glColor3f(0.51627f, .335882f, 0.0f);
	drawHollowCircle3(0.0, 0.1, .07, .205);

	glColor3f(0.50627f, .325882f, 0.0f);
	drawFilledCircle4(0.0, 0.1, .05, .205);
	//
	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.2, 0.03, .09, .01);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.2, 0.03, .09, .01);

	//
	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.17, -0.02, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.14, -0.02, .055, .017);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.105, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.065, -0.03, .050, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(0.02, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.015, -0.02, .04, .016);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.05, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.051, -0.03, .055, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.1, -0.025, .024, .024);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.14, -0.03, .055, .018);

	glColor3f(1.0f, 0.88f, 0.68f);
	drawFilledCircle4(-0.18, -0.02, .015, .015);


	glPushMatrix();
	glTranslatef(0.21, 0.09, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(0, 0.0f, 0.3f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.06, 0.28, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(60, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.11, 0.30, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(90, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, 0.295, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(120, 0.0f, 0.0f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.24, 0.1, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(180, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, -0.09, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(240, 0.0f, 0.0f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.14, -0.07, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(300, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.1, 0.0);
	glScalef(0.7, 0.7, 1.0);
	glRotatef(270, 0.0f, 0.5f, 1.0f);
	carrot();
	glPopMatrix();

}
void creamCakeRW()//red velvet & white cream 
{
	BakedCakeR();

	glBegin(GL_QUADS);

	glColor3f(0.99215f, .969019f, .89843f); // Set color to black
	glVertex2f(-0.192f, -0.02f);   // Bottom-left vertex
	glVertex2f(0.192f, -0.02f);    // Bottom-right vertex
	glVertex2f(0.192f, 0.08f);     // Top-right vertex
	glVertex2f(-0.192f, 0.08f);    // Top-left vertex
	glEnd();

	glColor3f(0.99215f, .999019f, .90843f);
	drawFilledCircle4(0.0, 0.1, .07, .205);

	glColor3f(0.98215f, .989019f, .90843f);
	drawHollowCircle3(0.0, 0.1, .07, .205);

	glColor3f(0.99215f, .999019f, .90843f);
	drawFilledCircle4(0.0, 0.1, .05, .205);
	///
	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.20, 0.03, .09, .01);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.20, 0.03, .09, .01);
	//
	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.17, -0.02, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.14, -0.02, .055, .017);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.105, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(0.065, -0.03, .050, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.02, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.015, -0.02, .04, .016);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.05, -0.025, .018, .018);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.051, -0.03, .055, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.1, -0.025, .024, .024);

	glColor3f(0.99215f, .969019f, .89843f);
	drawFilledCircle4(-0.14, -0.03, .055, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.18, -0.02, .015, .015);


}
void creamCakeRB()  //red velvet & brown cream 
{
	BakedCakeR();

	glBegin(GL_QUADS);

	glColor3f(0.48627f, .305882f, 0.0f);
	glVertex2f(-0.192f, -0.02f);   // Bottom-left vertex
	glVertex2f(0.192f, -0.02f);    // Bottom-right vertex
	glVertex2f(0.192f, 0.08f);     // Top-right vertex
	glVertex2f(-0.192f, 0.08f);    // Top-left vertex
	glEnd();

	glColor3f(0.50627f, .325882f, 0.0f);
	drawFilledCircle4(0.0, 0.1, .07, .205);

	glColor3f(0.51627f, .335882f, 0.0f);
	drawHollowCircle3(0.0, 0.1, .07, .205);

	glColor3f(0.50627f, .325882f, 0.0f);
	drawFilledCircle4(0.0, 0.1, .05, .205);
	//
	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.2, 0.03, .09, .01);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.2, 0.03, .09, .01);

	//
	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.17, -0.02, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.14, -0.02, .055, .017);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.105, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(0.065, -0.03, .050, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(0.02, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.015, -0.02, .04, .016);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.05, -0.025, .018, .018);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.051, -0.03, .055, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.1, -0.025, .024, .024);

	glColor3f(0.48627f, .305882f, 0.0f);
	drawFilledCircle4(-0.14, -0.03, .055, .018);

	glColor3f(.506274f, 0.12764f, 0.12764f);
	drawFilledCircle4(-0.18, -0.02, .015, .015);

}


void Q1() {

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
	glVertex2f(-0.7f, -0.5f);   // Bottom-left vertex
	glVertex2f(0.7f, -0.5f);    // Bottom-right vertex
	glVertex2f(0.7f, 0.6f);     // Top-right vertex
	glVertex2f(-0.7f, 0.6f);    // Top-left vertex
	glEnd();

	glLineWidth(6.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(6, 0xAAAA);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.74, 0.64);
	glVertex2f(-.74, -.54);
	glVertex2f(0.74, -.54);
	glVertex2f(.74, .64);
	glEnd();



	glColor3f(0.7853f, 0.7853f, 0.7853f);
	glLineWidth(10.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(0.1, 0xAAAA);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.65, 0.55);
	glVertex2f(-.65, -.45);
	glVertex2f(0.65, -.45);
	glVertex2f(.65, .55);
	glEnd();

	// drawing the filled circle
	glColor3f(0.8, 0.0f, 0.0f);
	drawFilledCircle(-0.47, 0.16, .052);

	// drawing the filled circle
	glColor3f(1.0f, 0.69803f, 0.4f);
	drawFilledCircle(-0.47, -.1, .05);


	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text;
	text = "Red Velvet Cake. ";
	drawStrokeText(text.data(), text.size(), 210, 330);


	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text1;
	text1 = "Which cake do you like: ";
	drawStrokeText(text1.data(), text1.size(), 180, 380);

	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text2;
	text2 = "Carrot Cake. ";
	drawStrokeText(text2.data(), text2.size(), 210, 270);
}
void Q2() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
	glVertex2f(-0.7f, -0.5f);   // Bottom-left vertex
	glVertex2f(0.7f, -0.5f);    // Bottom-right vertex
	glVertex2f(0.7f, 0.6f);     // Top-right vertex
	glVertex2f(-0.7f, 0.6f);    // Top-left vertex
	glEnd();

	glLineWidth(6.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(6, 0xAAAA);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.74, 0.64);
	glVertex2f(-.74, -.54);
	glVertex2f(0.74, -.54);
	glVertex2f(.74, .64);
	glEnd();

	glColor3f(0.7853f, 0.7853f, 0.7853f);
	glLineWidth(10.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(0.1, 0xAAAA);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.65, 0.55);
	glVertex2f(-.65, -.45);
	glVertex2f(0.65, -.45);
	glVertex2f(.65, .55);
	glEnd();


	// drawing the filled circle
	glColor3f(1.0, 1.0f, 0.9f);
	drawFilledCircle(-0.47, 0.16, .052);

	// drawing the filled circle
	glColor3f(0.4f, 0.2f, 0.0f);
	drawFilledCircle(-0.47, -.1, .05);


	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text;
	text = " White. ";
	drawStrokeText(text.data(), text.size(), 200, 330);


	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text1;
	text1 = "Which color do you like for";
	drawStrokeText(text1.data(), text1.size(), 165, 380);

	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text3;
	text3 = " the frosting?";
	drawStrokeText(text3.data(), text3.size(), 210, 360);


	glColor3f(0.0f, 0.0f, 0.0f);
	std::string text2;
	text2 = "Brown.";
	drawStrokeText(text2.data(), text2.size(), 210, 265);
}

void Scene1Start() {

	glPushMatrix();
	glScalef(0.8, 1.0, 1.0);
	doorFrame();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 1.0, 1.0);
	doorkey();
	glPopMatrix();

	doorWriting();

	doorHeart();

	glColor3f(0.5f, 0.5f, 0.5f);
	std::string text;
	text = " Press S to start. ";
	drawStrokeText(text.data(), text.size(), 200, 120);

}
void Scene2Q1() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.1, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	Q1();

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text;
	text = " Press 'R' -> red velvet cake ";
	drawStrokeText(text.data(), text.size(), 120, 80);

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text1;
	text1 = " Press 'C' -> carrot cake ";
	drawStrokeText(text1.data(), text1.size(), 120, 50);

}

void Scene3Ing() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(0.25, -0.2, 0.0);
	bowl();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(-0.15, -0.15, 0.0);
	Flour();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(0.15, -0.15, 0.0);
	colorB();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(0.20, -0.2, 0.0);
	colorW();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.3, -0.4, 0.0);
	egg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.25, -0.4, 0.0);
	egg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(-0.05, -0.2, 0.0);
	Milk();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.8, 1.0);
	glTranslatef(0.1, -0.08, 0.0);
	butterPlate();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.8, 1.0);
	glTranslatef(0.15, -0.08, 0.0);
	Butter();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 1:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " These are all the ingredients we need:";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);


}

void Scene4Butter() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowl();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.8, 1.0);
	glTranslatef(0.75, -0.083, 0.0);
	butterPlate();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.8, 1.0);
	glTranslatef(0.7, -0.083, 0.0);
	Butter();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 2:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " Put 100g of butter";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);
}
void Scene4AfterAddButter() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.8, 1.0);
	glTranslatef(0.75, -0.083, 0.0);
	butterPlate();
	glPopMatrix();


	bowlButter();


	glPushMatrix();
	glScalef(0.7, 0.8, 1.0);
	glTranslatef(0.7, -0.083, 0.0);
	Butter();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}

void Scene5Egg() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	bowlButter();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(0.25, -0.33, 0.0);
	egg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(0.3, -0.33, 0.0);
	egg();
	glPopMatrix();


	glPushMatrix();
	glScalef(scaleValueE2, scaleValueE2, 1.0);
	glTranslatef(transValueX2, transValueY2, 0.0);
	BreakEgg();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 3:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " Put 2 egg yolks";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text5;
	text5 = " ---------";
	drawStrokeText2(text5.data(), text5.size(), 20, 470);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text4;
	text4 = " To add eggs, click the left mouse button";
	drawStrokeText2(text4.data(), text4.size(), 20, 450);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}
void Scene5AfterAddEgg() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlEgg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(0.25, -0.33, 0.0);
	egg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(0.3, -0.33, 0.0);
	egg();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}

void Scene6Milk() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlEgg();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.7, -0.3, 0.0);
	glTranslatef(transValueXM2, transValueYM2, 0.0);
	glRotatef(rotateValue, 0.0f, 0.0f, 1.0f);
	Milk();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 4:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " 70g milk";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text5;
	text5 = " ---------";
	drawStrokeText2(text5.data(), text5.size(), 20, 470);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text4;
	text4 = " To add milk, click the left mouse button";
	drawStrokeText2(text4.data(), text4.size(), 20, 450);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}
void Scene6AfterAddMilk() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlMilk();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.7, -0.3, 0.0);
	Milk();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}

void Scene7Flour() {
	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlMilk();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.30, -0.38, 0.0);
	glTranslatef(transValueXM2, transValueYM2, 0.0);
	glRotatef(rotateValue, 0.0f, 0.0f, 1.0f);
	Flour();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 5:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " 90g flour";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text5;
	text5 = " ---------";
	drawStrokeText2(text5.data(), text5.size(), 20, 470);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text4;
	text4 = " To add flour, click the left mouse button";
	drawStrokeText2(text4.data(), text4.size(), 20, 450);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}
void Scene7AfterAddFlour() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlFlour();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 1.0);
	glTranslatef(0.29, -0.38, 0.0);
	Flour();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}

void Scene8Mix() {
	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.6, 0.6, 1.0);
	glTranslatef(-0.05, -0.37, 0.0);
	bowlFlour();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step6:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = "Mixing the ingredients together.";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}
void Scene8Mix2() {

	//Whisk

	glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glScalef(0.7f, 0.7f, 0.7f);


	glPushMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glRotatef(-50, 0, 0, 1);
	glScalef(2, 1, 1);
	Whisk();
	glPopMatrix();


	glPopMatrix();
	glutSwapBuffers();

}
void Scene9CakePanToOvenR() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.62, 0.82, 1.0);
	glTranslatef(0.47, -0.55, 0.0);
	glTranslatef(transValueX, transValueY, 0.0);
	MixtureR();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 7:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " Bake in a preheated oven at 160c for 25 minutes";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text5;
	text5 = " ---------";
	drawStrokeText2(text5.data(), text5.size(), 20, 470);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text4;
	text4 = "Put the mixture in the oven using the arrow keys";
	drawStrokeText2(text4.data(), text4.size(), 20, 450);
}
void Scene9CakePanToOvenC() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.85, 1.0);
	glTranslatef(0.47, -0.55, 0.0);
	glTranslatef(transValueX, transValueY, 0.0);
	MixtureC();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text;
	text = " Step 7:";
	drawStrokeText2(text.data(), text.size(), 20, 520);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text1;
	text1 = " Bake in a preheated oven at 160c for 25 minutes";
	drawStrokeText2(text1.data(), text1.size(), 21, 490);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text5;
	text5 = " ---------";
	drawStrokeText2(text5.data(), text5.size(), 20, 470);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text4;
	text4 = "Put the mixture in the oven using the arrow keys";
	drawStrokeText2(text4.data(), text4.size(), 20, 450);


}

void Scene10CakePanDoneInR() {
	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.6, 0.7, 1.0);
	glTranslatef(-1.55, -0.29, 0.0);
	BakedCakeInOvenR();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);
}
void Scene10CakePanDoneInC() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();


	glPushMatrix();
	glScalef(0.6, 0.7, 1.0);
	glTranslatef(-1.55, -0.29, 0.0);
	BakedCakeInOvenC();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);
}
void Scene11DoneBakingR() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.038, -0.15, 0.0);
	BakedCakeR();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);

}
void Scene11DoneBakingC() {
	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.038, -0.15, 0.0);
	BakedCakeC();
	glPopMatrix();

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text2;
	text2 = " Click the right mouse button to";
	drawStrokeText2(text2.data(), text2.size(), 380, 70);

	glColor3f(0.3f, 0.3f, 0.3f);
	std::string text3;
	text3 = " move to the next step.";
	drawStrokeText2(text3.data(), text3.size(), 400, 40);
}

void Scene12QCreamColor() {

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	Q2();

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text;
	text = " Press 'W' -> White cream ";
	drawStrokeText(text.data(), text.size(), 150, 80);

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text1;
	text1 = " Press 'B' -> Brown cream";
	drawStrokeText(text1.data(), text1.size(), 170, 50);

}

void Scene13FinalRW() {

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, -0.14, 0.0);
	creamCakeRW();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(.4, 1.2, 1.0);
	glTranslatef(-0.03, -0.14, 0.0);
	Candle();
	glPopMatrix();

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text2;
	text2 = " Bon appétit";
	drawStrokeText3(text2.data(), text2.size(), 230, 450);

}
void Scene13FinalCB() {

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, -0.14, 0.0);
	creamCakeCB();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();


	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text2;
	text2 = " Bon appétit";
	drawStrokeText3(text2.data(), text2.size(), 230, 450);
}
void Scene13FinalRB() {

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, -0.14, 0.0);
	creamCakeRB();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();

	glPushMatrix();
	glScalef(.4, 1.2, 1.0);
	glTranslatef(-0.03, -0.143, 0.0);
	Candle();
	glPopMatrix();

	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text2;
	text2 = " Bon appétit..";
	drawStrokeText3(text2.data(), text2.size(), 230, 450);

}
void Scene13FinalCW() {

	glPushMatrix();
	glScalef(1.5, 2.0, 1.0);
	Floor();
	glPopMatrix();

	window();


	glPushMatrix();
	glTranslatef(-0.57, -0.1, 0.0);
	glScalef(0.9, 1.0, 1.0);
	Chef();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	glScalef(.9, 1.0, 1.0);
	table();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.17, -0.5, 0.0);
	glScalef(1.1, 1.1, 1.0);
	oven();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, -0.14, 0.0);
	creamCakeCW();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.25, 0.0);
	Lamp();
	glPopMatrix();


	glColor3f(0.2f, 0.2f, 0.2f);
	std::string text2;
	text2 = " Bon appétit..";
	drawStrokeText3(text2.data(), text2.size(), 230, 450);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
	glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	if (Scene1 == true) {
		Scene1Start();
	}
	else if (Scene2q1 == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene2Q1();
		glPopMatrix();

	}
	else if (Scene3ing == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene3Ing();
		glPopMatrix();

	}
	else if (Scene4butter == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene4Butter();
		glPopMatrix();

	}
	else if (Scene4AfterAddbutter == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene4AfterAddButter();
		glPopMatrix();
	}
	else if (Scene5egg == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene5Egg();
		glPopMatrix();
	}
	else if (Scene5AfterAddegg == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene5AfterAddEgg();
		glPopMatrix();
	}
	else if (Scene6milk == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene6Milk();
		glPopMatrix();
	}
	else if (Scene6AfterAddmilk == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene6AfterAddMilk();
		glPopMatrix();
	}
	else if (Scene7flour == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene7Flour();
		glPopMatrix();
	}
	else if (Scene7AfterAddflour == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene7AfterAddFlour();
		glPopMatrix();
	}
	else if (Scene8mix == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene8Mix();
		Scene8Mix2();
		glPopMatrix();
	}
	else if (Scene9cakePanToOvenR == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene9CakePanToOvenR();
		glPopMatrix();
		if (CakePanXU > CakePanMinX && CakePanXU < CakePanMaxX) {
			if (CakePanYU > CakePanMinY && CakePanYU < CakePanMaxY) {
				Scene9cakePanToOvenR = false;
				Scene10cakePanDoneInR = true;
			}
		}
	}
	else if (Scene9cakePanToOvenC == true) {
		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene9CakePanToOvenC();
		glPopMatrix();
		if (CakePanXU > CakePanMinX && CakePanXU < CakePanMaxX) {
			if (CakePanYU > CakePanMinY && CakePanYU < CakePanMaxY) {
				Scene9cakePanToOvenC = false;
				Scene10cakePanDoneInC = true;

			}
		}
	}
	else if (Scene10cakePanDoneInR == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene10CakePanDoneInR();
		glPopMatrix();
	}
	else if (Scene10cakePanDoneInC == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene10CakePanDoneInC();
		glPopMatrix();
	}
	else if (Scene11cakePanDoneOutR == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene11DoneBakingR();
		glPopMatrix();
	}
	else if (Scene11cakePanDoneOutC == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene11DoneBakingC();
		glPopMatrix();
	}
	else if (Scene12Q2 == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene12QCreamColor();
		glPopMatrix();
	}
	else if (Scene13RW == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene13FinalRW();
		glPopMatrix();
	}
	else if (Scene13CB == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene13FinalCB();
		glPopMatrix();
	}
	else if (Scene13RB == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene13FinalRB();
		glPopMatrix();
	}
	else if (Scene13CW == true) {

		glPushMatrix();
		glScalef(0.8, 0.8, 1.0);
		Scene13FinalCW();
		glPopMatrix();

	}
	else {
		exit(0);
	}

	glFlush();
	glutSwapBuffers();

}

void reshapeFun(GLint newWidth, GLint newHight) {
	glViewport(0, 0, newWidth, newHight);
	win_width = newWidth;
	win_hight = newHight;
}
void init()
{
	transValueX = 0.0;
	transValueY = 0.0;
	transValueZ = 2.0;
	near1 = 0.01;
	far1 = 50;

	//------- Texture ---------
	myTexture1 = LoadTexture(image1Path, 612, 459);

	if (myTexture1 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture1 << endl;

	glClearColor(1.0f, 0.9f, 0.9f, 0.0f); // Set background color
	glMatrixMode(GL_PROJECTION); // set the projection parameters

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Specify the display Mode RGB, RGBA or color // Index, single or double Buffer
	glutInitWindowSize(win_width, win_hight);     // Set the window's initial width & height
	glutInitWindowPosition(450, 50);               // Position the window's initial top-left corner

	glutCreateWindow("CG_Bakery");          // Create a window with the given title
	glutTimerFunc(25, update, 0);
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);

	glutIdleFunc(play);
	glutReshapeFunc(reshapeFun);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutMainLoop();                            // Enter the infinitely event-processing loop

	return 0;
}
