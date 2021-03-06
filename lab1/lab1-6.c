// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

// Should work as is on Linux and Mac. MS Windows needs GLEW or glee.
// See separate Visual Studio version of my demos.
#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "GL_utilities.h"
#include "loadobj.h"
#include <math.h>

GLfloat translation[] = {    1.0f, 0.0f, 0.0f, -0.3f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f };

// vertex array object
unsigned int vertexArrayObjID;
GLuint program;

unsigned int bunnyVertexArrayObjID;
unsigned int bunnyVertexBufferObjID;
unsigned int bunnyIndexBufferObjID;
unsigned int bunnyNormalBufferObjID;
Model *m;

void init(void)
{
	m = LoadModel("bunny.obj");

	dumpInfo();

	// GL inits
	glClearColor(1.0,0.0,0.0,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	program = loadShaders("lab1-6.vert", "lab1-6.frag");
	printError("init shader");

	// Upload geometry to the GPU:
	glGenVertexArrays(1, &bunnyVertexArrayObjID);
	glGenBuffers(1, &bunnyVertexBufferObjID);
	glGenBuffers(1, &bunnyIndexBufferObjID);
	glGenBuffers(1, &bunnyNormalBufferObjID);
	printError("glGenBuffers");

	glBindVertexArray(bunnyVertexArrayObjID);

	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, bunnyVertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->vertexArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));
	printError("Glasskiosk");

	// VBO for normal data
	glBindBuffer(GL_ARRAY_BUFFER, bunnyNormalBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->normalArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	printError("Något annat");
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIndexBufferObjID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->numIndices*sizeof(GLuint), m->indexArray, GL_STATIC_DRAW);
	printError("Hemskt mycke hej");
}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(20, &OnTimer, value);
}

void display(void)
{
	printError("pre display");
	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000;
	GLfloat rotationZ[16] = {
		     cos(t), -sin(t), 0.0f, 0.0f,
		     sin(t), cos(t), 0.0f, 0.0f,
		     0.0f, 0.0f,  1.0f, 0.0f,
		     0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat rotationX[16] = {
		     1.0f, 0.0f, 0.0f, 0.0f,
		     0.0f, cos(t), -sin(t), 0.0f,
		     0.0f, sin(t),  cos(t), 0.0f,
		     0.0f, 0.0f, 0.0f, 1.0f };
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationZ"), 1, GL_TRUE, rotationZ);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationX"), 1, GL_TRUE, rotationX);
	glUniformMatrix4fv(glGetUniformLocation(program, "translation"), 1, GL_TRUE, translation);
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(bunnyVertexArrayObjID);	// Select VAO
	glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);	// draw object

	printError("display");

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutCreateWindow ("GL3 white triangle example");
	glutDisplayFunc(display);
	init ();
	glutTimerFunc(16.7, &OnTimer, 0);
	glutMainLoop();

}
