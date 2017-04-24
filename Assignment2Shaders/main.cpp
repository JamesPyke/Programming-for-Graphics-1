#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glut.h>

GLint giXRes = 600;
GLint giYRes = 600;
GLint window1ID;
GLuint sID;
GLuint vbo = 0; // Used to store the vertex buffer object
GLuint vao = 0; // Used to store the vertex array object
GLuint vaoHandle;
GLfloat rotateSpeed = 0.05f;
GLfloat rotate = 0.785398f;

float positionData[] =
{
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,

	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,

	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f

};

float colourData[] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
};

char *vs = nullptr;	// Pointer to a Charcter array for the vertext shader
char *fs = nullptr;	// Pointer to a character array for the fragment shader

//////////////////////////////////////////////////////////////////////////////
// shaderCompilerCheck()
//
// Function to check the shader has been compiled correctly
// Outputs any compile errors in the shader to the command line window
//////////////////////////////////////////////////////////////////////////////
void shaderCompilerCheck(GLuint ID)
{
	GLint comp;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);  // Return the compile status from the shader

	if (comp == GL_FALSE) {		// If shader failed to compile, print the error message
		printf("Shader Compilation FAILED");
		GLchar messages[256];
		glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// shaderLinkCheck()																//
//																					//
// Function to check the shader has been linked to the main application correctly	//
// Outputs any compile errors in the shader to the command line window				//	
//////////////////////////////////////////////////////////////////////////////////////
void shaderLinkCheck(GLuint ID)
{
	GLint linkStatus, validateStatus;
	glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus); // Return the linker status from the shader

	if (linkStatus == GL_FALSE)
	{	// If shader failed to link, print the error message
		printf("Shader Linking FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}

	glValidateProgram(ID);	// Check to see if the application can be executed.

	glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus); // Return the result of the validation process.

	if (validateStatus == GL_FALSE)
	{	// If application failed to validate, print the error message
		printf("Shader Validation FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

//////////////////////////////////////////////////////////////////////////////
// shaders()
//
// Function to create the vertex and fragment shaders
//////////////////////////////////////////////////////////////////////////////
void shaders()
{

	const char* vertex_shader =
		"#version 430\n"
		"uniform float angle;"
		"in vec3 VertexPosition;"
		"in vec3 VertexColour;"
		"out vec3 Color;"
		"void main() {"
		" Color = VertexColour;"

		" mat4 rotateX = mat4(1.5);"
		" rotateX[0][0] = 1.0;"
		" rotateX[1][1] = cos(angle);"
		" rotateX[2][1] = -sin(angle);"
		" rotateX[1][2] = sin(angle);"
		" rotateX[2][2] = cos(angle);"

		" mat4 rotateY = mat4(1.5); "
		" rotateY[0][0] = cos(angle);"
		" rotateY[1][1] = 1.0;"
		" rotateY[0][2] = -sin(angle);"
		" rotateY[2][0] = sin(angle);"
		" rotateY[2][2] = cos(angle);"

		" mat4 rotateZ = mat4(1.5); "
		" rotateZ[0][0] = cos(angle);"
		" rotateZ[1][1] = cos(angle);"
		" rotateZ[1][0] = -sin(angle);"
		" rotateZ[0][1] = sin(angle);"
		" rotateZ[2][2] = 1.0;"

		"mat4 rotate = (rotateZ)*(rotateY)*(rotateX);"
		" gl_Position = rotate * vec4(VertexPosition, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 430\n"
		"in vec3 Color;"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = vec4(Color, 1.0 );"
		"}";

	sID = glCreateProgram();	// Create the main program

	glBindAttribLocation(sID, 0, "VertexPosition");
	glBindAttribLocation(sID, 1, "VertexColour");

	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colourBufferHandle = vboHandles[1];

	// Populate the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), positionData,
		GL_STATIC_DRAW);

	// Populate the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), colourData,
		GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	// Enable the vertex attribute arrays
	glEnableVertexAttribArray(0); // Vertex position
	glEnableVertexAttribArray(1); // Vertex color
								  // Map index 0 to the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
		static_cast<GLubyte *>(nullptr));
	// Map index 1 to the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,
		static_cast<GLubyte *>(nullptr));

	GLuint vID = glCreateShader(GL_VERTEX_SHADER);	// Create an empty vertex shader program
	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);// Create an empty fragment shader program

	glShaderSource(vID, 1, &vertex_shader, nullptr);
	glShaderSource(fID, 1, &fragment_shader, nullptr);

	glCompileShader(vID);	// Compile the vertex shader
	glCompileShader(fID);	// Compile the fragment shader

	shaderCompilerCheck(vID);	// Check for compile errors in the vertext shader
	shaderCompilerCheck(fID);	// Check for compile errors in the fragment shader

	glAttachShader(sID, vID);	// Attached the vertex shader to the main program
	glAttachShader(sID, fID);	// Attached the fragment shader to the main program

	glLinkProgram(sID);	// Send the vertex shader program to the GPU vertex processor, and the fragment shader program to the GPU fragment processor

	shaderLinkCheck(sID);	// Check for Linker errors
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 1.0, 0.0, 1.0, -100.0, 100.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(sID);	// Use shader program which has already been setup in main()
	GLint rotationUniform = glGetUniformLocation(sID, "angle");
	glBindVertexArray(vaoHandle);
	rotate = rotate + rotateSpeed;
	glUniform1f(rotationUniform, rotate);
	glDrawArrays(GL_QUADS, 0, 24);	// Use the first 3 vertices from position 0 to draw a triangle
	glUseProgram(0);	//Unbind the shader program
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(300, 50);
	glutInitWindowSize(giXRes, giYRes);
	glutCreateWindow("Shading a Cube");
	initGL();
	glewInit();
	// Check if OpenGL Shading Language is available
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else
	{
		printf("No GLSL support\n");
		exit(1);
	}
	shaders();	// Create the shader programs
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
