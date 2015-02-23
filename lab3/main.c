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
#include "main.h"

#define near 1.0
#define far 300.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5

// vertex array object
unsigned int vertexArrayObjID;
GLuint program;

Model *walls;
Model *roof;
Model *blade;
Model *balcony;
mat4 transWalls;
mat4 transRoof;
mat4 transBlade;
mat4 transBalcony;

mat4 lookMatrix;
vec3 cameraPos;
vec3 cameraDirection;
vec3 cameraNormal;

void init(void)
{
  cameraPos = (vec3){0.0f, 0.0f, 0.0f};
  cameraDirection = (vec3){-0.0f, -10.0f, -20.0f};
  cameraNormal = (vec3){0.0f, 1.0f, 0.0f};
  lookMatrix = lookAtv(cameraPos, cameraDirection, cameraNormal);

	dumpInfo();

	walls = LoadModelPlus("windmill/windmill-walls.obj");
	roof = LoadModelPlus("windmill/windmill-roof.obj");
	blade = LoadModelPlus("windmill/blade.obj");
	balcony = LoadModelPlus("windmill/windmill-balcony.obj");
	transWalls = T(0, -10, -20);
	transRoof = Mult(transWalls, T(0, 0, 0));
	transBalcony = Mult(transWalls, Ry(M_PI / 2));

	// Load textures
	GLuint concrete;
	LoadTGATextureSimple("conc.tga", &concrete);

	// GL inits
	glClearColor(1.0,0.0,0.0,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	program = loadShaders("lab2.vert", "lab2.frag");

	glBindTexture(GL_TEXTURE_2D, concrete);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0

	GLfloat projectionMatrix[] = {2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
                                      0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
                                      0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
                                      0.0f, 0.0f, -1.0f, 0.0f };

	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix);

}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(20, &OnTimer, value);
}

GLfloat x = 0;
GLfloat y = -0.8;
GLfloat z = -15.4;

void display(void)
{
	printError("pre display");

	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 5000;

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
	vec3 translation = moveOnKeyInput(x, y, z);
	transBlade = T(translation.x, translation.y, translation.z);
	if (keyIsDown('p'))
		printf("%f %f %f \n", translation.x, translation.y, translation.z);

	for (int i = 0; i < 4; i++){
		mat4 rotBlade = Mult(Rz(M_PI / 2 * i + t), Ry(M_PI / 2));
		mat4 transform = Mult(transBlade, rotBlade);
		drawObject(transform, blade);
	}

	glUniformMatrix4fv(glGetUniformLocation(program, "lookMatrix"), 1, GL_TRUE, lookMatrix.m);

	drawObject(transWalls, walls);
	drawObject(transRoof, roof);
	drawObject(transBalcony, balcony);

	printError("display");
	glutSwapBuffers();
}

void drawObject(mat4 transform, Model* model)
{
	glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_TRUE, transform.m);
	DrawModel(model, program, "in_Position", "in_Normal", "in_TexCoord");
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutCreateWindow ("Lab 3");
	glutDisplayFunc(display);
	initKeymapManager();
	glutPassiveMotionFunc(handleMouse);
	init ();
	glutTimerFunc(16.7, &OnTimer, 0);
	glutMainLoop();
	
}

void handleMouse(int x, int y) 
{

  cameraPos = (vec3) {cos((float)x / 400 * M_PI) * 20, sin((float)y / 400 * M_PI) * 20, cameraPos.z};
  
  lookMatrix = lookAtv(cameraPos, cameraDirection, cameraNormal);
  
}

vec3 moveOnKeyInput(GLfloat x, GLfloat y, GLfloat z)
{
  struct vec3 returnValue;
  returnValue.x = x;
  returnValue.y = y;
  returnValue.z = z;

  if(keyIsDown('w'))
    returnValue.y += 0.1;
  else if (keyIsDown('s'))
    returnValue.y -= - 0.1;
  if(keyIsDown('a'))
    returnValue.x += 0.1;
  else if(keyIsDown('d'))
    returnValue.x -= 0.1;
  if(keyIsDown('q'))
    returnValue.z += 0.1;
  else if(keyIsDown('e'))
    returnValue.z -= 0.1;

  return returnValue;
}
