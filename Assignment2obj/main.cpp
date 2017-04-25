#define _CRT_SECURE_NO_WARNINGS

#include <glut.h>
#include <cstdio>
#include <string>
#include <vector>

/*
*POSSIBLE OBJ FILES TO LOAD
*
*cube.obj
*cow.obj
*teapot.obj
*teddy.obj
*bmw.obj
*batman.obj
*elephant.obj
*
*/

//Variables for reading in the OBJ file
char ch = '1';
FILE *fp;
int read;
GLfloat x, y, z;
char const* fname = "elephant.obj";

//Variables for OBJ settings
float zoom;
float pointSize = 2.0f;

//Variables for movement
float angle = 0.0;
float lx = 0.0f, lz = -1.0f;
float px = 0.0f, pz = 5.0f;



//Declaring the variables for the x, y and z vertices
struct Vertex
{
	float x;
	float y;
	float z;
};

//Vector list of vertices
std::vector<Vertex> vertices;

//Checks the file and changes the zoom settings accordingly
void checkFile()
{
	if (fname == "teddy.obj")
	{
		zoom = 7;
	}
	else if (fname == "teapot.obj")
	{
		zoom = 1;
	}
	else if (fname == "cube.obj")
	{
		zoom = 1;
	}
	else if (fname == "cow.obj")
	{
		zoom = 2;
	}
	else if (fname == "batman.obj")
	{
		zoom = 1;
	}
	else if (fname == "bmw.obj")
	{
		zoom = 13;
	}
	else if (fname == "elephant.obj")
	{
		zoom = 200;
	}
	else
		zoom = 1;
}

//Reads in the model from the OBJ file 
void readCube()
{
	//Calls the OpenGL file open function and call it with read only mode
	fp = fopen(fname, "r");
	//After the file is read in, check the file
	checkFile();
	//If the file can not open print error and exit the application
	if (!fp)
	{
		printf("Could not open file %s\n", fname);
		exit(1);
	}

	while (!feof(fp))
	{
		read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
		if (read == 4 && ch == 'v')
		{
			Vertex vertex;

			vertex.x = x;
			vertex.y = y;
			vertex.z = z;

			vertices.push_back(vertex);
		}
	}
}

void drawCube()
{
	glPointSize(pointSize);

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (auto & vertex : vertices)
	{
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Add perspective view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0 * zoom, 4.0 * zoom, -4.0 * zoom, 4.0 * zoom, -100.0, 100.0);
	gluLookAt(px, 1.0f, pz, px + lx, 1.0f, pz + lz, 0.0f, 1.0f, 0.0f);
	// moving the camera and target the same relative distance, creates a pan

	// Switch back to Model view
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(0.0f, -0.6f, -1.0f);
	drawCube();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyPresses(int key, int xx, int yy)
{
	float fraction = 0.5f;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		px += lx * fraction;
		pz += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		px -= lx * fraction;
		pz -= lz * fraction;
		break;
	default:
		break;
	}
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	readCube();
}


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(600, 0);
	glutCreateWindow("Reading in a cube");
	glOrtho(-4.0 * zoom, 4.0 * zoom, -4.0  * zoom, 4.0 * zoom, -100.0, 100.0);
	glutSpecialFunc(keyPresses);
	glutDisplayFunc(display);
	initGL();
	glutMainLoop();
}