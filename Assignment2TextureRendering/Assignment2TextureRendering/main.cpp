#include <glut.h>
#include <IL/ilut.h> // Adds functionality to load textures

GLint giXRes = 800;
GLint giYRes = 800;
GLfloat zRotate = 45;
GLfloat rotateSpeed = 1.0f;
GLuint myImage; // Varaible to hold the name of the texture to load
GLuint myImage2;
GLuint myImage3;
GLuint myImage4;
GLuint myImage5;
GLuint myImage6;

void InitTextures(void)
{
	// Define wrapping behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Define texture Filtering behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Load an image and apply it to the variable myImage
	myImage = ilutGLLoadImage("one.bmp");
	myImage2 = ilutGLLoadImage("two.bmp");
	myImage3 = ilutGLLoadImage("three.bmp");
	myImage4 = ilutGLLoadImage("four.bmp");
	myImage5 = ilutGLLoadImage("five.bmp");
	myImage6 = ilutGLLoadImage("six.bmp");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Define how material is sent further down the rendering pipeline
}
void drawSquare() 
{
	glEnable(GL_TEXTURE_2D); // Switch on 2D texture mapping, this will overiride any glColor()
	glBindTexture(GL_TEXTURE_2D, myImage);// Use the suplied 2D texture with any primitive shapes cfeated from this point onwards

	glBegin(GL_POLYGON);

	// Define vertices in counter-clockwise direction

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage2);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage3);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage4);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage5);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage6);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0f, 0.0f, -5.0f);
	zRotate = zRotate + rotateSpeed;
	glPushMatrix();
	glRotatef(zRotate, zRotate, zRotate, 0.0);
	drawSquare();
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void initGL() 
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(giXRes, giYRes);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Texture Rendering");
	/////////////////////////////////////////////
	// Functions to setup the OpenILUT renderer
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
						 /////////////////////////////////////////////
	glFrontFace(GL_CW); // When defining primitives, the FRONT side is assumed to be created from vertices which are listed in
						//a clockwise direction
	glCullFace(GL_BACK); // Specify if front or back faces should be culled. only takes effect if glEnable(GL_CULL_FACE) is executed
						 // glEnable(GL_CULL_FACE); // Uncomment this line to stop the back face of the QUAD being displayed
	glEnable(GL_DEPTH_TEST);
	InitTextures(); // Custom function to configure the textures
	initGL();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}