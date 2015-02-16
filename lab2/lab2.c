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
#include "LoadTGA.h"
#include "VectorUtils3.h"

#define near 1.0
#define far 30.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5

GLfloat projectionMatrix[] = {2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
															0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
															0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
															0.0f, 0.0f, -1.0f, 0.0f };

GLfloat translation[] = { 1.0f, 0.0f, 0.0f, -0.3f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, -10.0f,
                          0.0f, 0.0f, 0.0f, 1.0f };

// vertex array object
unsigned int vertexArrayObjID;
GLuint program;

Model *kanin;
Model *tekanna;
mat4 transKanin;
mat4 transTekanna;

void init(void)
{
	kanin = LoadModelPlus("bunnyplus.obj");
	transKanin = T(0, 0, -3);
	tekanna = LoadModelPlus("teapot.obj");
	transTekanna = T(0, 0, -20);
	dumpInfo();

	// Load textures
	GLuint myTex;
	LoadTGATextureSimple("maskros512.tga", &myTex);

	// GL inits
	glClearColor(1.0,0.0,0.0,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	program = loadShaders("lab2.vert", "lab2.frag");

	glBindTexture(GL_TEXTURE_2D, myTex);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0
}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(20, &OnTimer, value);
}

void display(void)
{
	mat4 lookMatrix = lookAt(0.0f, 0.0f, 0.0f,
													 -0.3f, -0.0f, -3.0f,
													 0.0f, 1.0f, 0.0f);
	printError("pre display");

	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 5000;

	mat4 rotationZ = Rz(t);
	mat4 rotationX = Rx(t);
	mat4 totalKanin = Mult(rotationZ, rotationX);
	totalKanin = Mult(transKanin, totalKanin);
	rotationZ = Rz(-t * 2);
	rotationX = Rx(t / 2);
	mat4 totalTekanna = Mult(rotationZ, rotationX);
	totalTekanna = Mult(transTekanna, totalTekanna);


	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "lookMatrix"), 1, GL_TRUE, lookMatrix.m);

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_TRUE, totalKanin.m);
	DrawModel(kanin, program, "in_Position", "in_Normal", "inTexCoord");
	glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_TRUE, totalTekanna.m);
	DrawModel(tekanna, program, "in_Position", "in_Normal", "inTexCoord");

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
