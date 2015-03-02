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
Model *ground;
Model *bunny;
Model *teapot;
Model *skybox;
mat4 transWalls;
mat4 transRoof;
mat4 transBlade;
mat4 transBalcony;
mat4 transGround;
mat4 transBunny;
mat4 transTeapot;

GLuint concrete;
GLuint grass;

mat4 lookMatrix;
vec3 cameraPos;
vec3 cameraDirection;
vec3 cameraNormal;
vec3 bladePos;
/*
vec3 objectpos = {0,0,0};
	objectpos = moveOnKeyInput(objectpos.x, objectpos.y, objectpos.z);
	if (keyIsDown('p'))
		printf("%f %f %f \n", objectpos.x, objectpos.y, objectpos.z);
*/

void init(void)
{
  bladePos = (vec3){0, 9, 4.5};
  cameraPos = (vec3){10.5f, 13.6f, 23.0f};
  cameraDirection = (vec3){-10.0f, -10.0f, -10.0f};
  cameraNormal = (vec3){0.0f, 1.0f, 0.0f};
  lookMatrix = lookAtv(cameraPos, cameraDirection, cameraNormal);

	dumpInfo();

	walls = LoadModelPlus("windmill/windmill-walls.obj");
	roof = LoadModelPlus("windmill/windmill-roof.obj");
	blade = LoadModelPlus("windmill/blade.obj");
	balcony = LoadModelPlus("windmill/windmill-balcony.obj");
	ground = LoadModelPlus("ground.obj");
	bunny = LoadModelPlus("bunnyplus.obj");
	teapot = LoadModelPlus("teapot.obj");
	skybox = LoadModelPlus("skybox.obj");
	transWalls = T(0, 0, 0);
	transRoof = Mult(transWalls, T(0, 0, 0));
	transBalcony = Mult(transWalls, Ry(M_PI / 2));
	transGround = Mult(T(-5.3,1.8,-1.5), Rz(M_PI/2));	
	transBunny = T(-2.2, -2.3, 10.2);
	transTeapot = T(34.4, 6.4, -30.4);




	// Load textures

	LoadTGATextureSimple("conc.tga", &concrete);
	LoadTGATextureSimple("grass.tga", &grass);

	// GL inits
	glClearColor(1.0,0.0,0.0,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	program = loadShaders("lab2.vert", "lab2.frag");



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

void display(void)
{
	printError("pre display");

	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 5000;

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
	transBlade = T(bladePos.x, bladePos.y, bladePos.z);
	for (int i = 0; i < 4; i++){
		mat4 rotBlade = Mult(Rz(M_PI / 2 * i + t), Ry(M_PI / 2));
		mat4 transform = Mult(transBlade, rotBlade);
		drawObject(transform, blade);
	}

        cameraPos = moveOnKeyInput(cameraPos.x, cameraPos.y, cameraPos.z);
	lookMatrix = lookAtv(cameraPos, cameraDirection, cameraNormal);
	glUniformMatrix4fv(glGetUniformLocation(program, "lookMatrix"), 1, GL_TRUE, lookMatrix.m);

	glDisable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, concrete);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0

	drawObject(transWalls, walls);
	drawObject(transRoof, roof);
	drawObject(transBalcony, balcony);

	glBindTexture(GL_TEXTURE_2D, grass);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0
	drawObject(transGround,ground);
	drawObject(transTeapot,teapot);
	drawObject(transBunny,bunny);


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

    printf("%f %f %f \n  %f  %f \n", cameraPos.x, cameraPos.y, cameraPos.z, (float)x/400, (float)y/400);
  cameraDirection = (vec3) {cos((float)x / 400 * M_PI * 2) * 20,
                      cos((float)y / 400 * M_PI * 2) * 20,
                      sin((float)x / 400 * M_PI * 2) * 20};
  
  lookMatrix = lookAtv(cameraPos, cameraDirection, cameraNormal);
}

vec3 moveOnKeyInput(GLfloat x, GLfloat y, GLfloat z)
{
  struct vec3 returnValue;
  returnValue.x = x;
  returnValue.y = y;
  returnValue.z = z;

  if(keyIsDown('w'))
    returnValue.y += 1;
  else if (keyIsDown('s'))
    returnValue.y -= 1;
  if(keyIsDown('a'))
    returnValue.x += 1;
  else if(keyIsDown('d'))
    returnValue.x -= 1;
  if(keyIsDown('q'))
    returnValue.z += 1;
  else if(keyIsDown('e'))
    returnValue.z -= 1;

  return returnValue;
}
/*
vec3 moveOnKeyInputRelativeCamera(vec3 in)
{
  if(keyIsDown('w'))
    in.y += 0.1 * cameraDirection
;
  else if (keyIsDown('s'))
    in.y -= 0.1;
  if(keyIsDown('a'))
    in.x += 0.1;
  else if(keyIsDown('d'))
    in.x -= 0.1;
  if(keyIsDown('q'))
    in.z += 0.1;
  else if(keyIsDown('e'))
    in.z -= 0.1;

  return in;
}
*/
