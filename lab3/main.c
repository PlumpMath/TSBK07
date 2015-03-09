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
GLuint skyboxProgram;

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
GLuint skyTexture;
GLuint maskrosTexture;

mat4 lookMatrix;
vec3 cameraPos;
vec3 cameraTarget;
vec3 cameraNormal;
vec3 cameraDirection;
vec3 bladePos;


void init(void)
{
  bladePos = (vec3){0, 9, 4.5};
  cameraPos = (vec3){10.5f, 13.6f, 23.0f};
  cameraTarget = (vec3){-10.0f, -10.0f, -10.0f};
  cameraNormal = (vec3){0.0f, 1.0f, 0.0f};
  lookMatrix = lookAtv(cameraPos, cameraTarget, cameraNormal);

	dumpInfo();

	walls = LoadModelPlus("windmill/windmill-walls.obj");
	roof = LoadModelPlus("windmill/windmill-roof.obj");
	blade = LoadModelPlus("windmill/blade.obj");
	balcony = LoadModelPlus("windmill/windmill-balcony.obj");
	ground = LoadModelPlus("models/LittleNell/Tree/ground.obj");
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
	LoadTGATextureSimple("SkyBox512.tga", &skyTexture);
	LoadTGATextureSimple("maskros512.tga", &maskrosTexture);

	// GL inits
	printError("GL inits");
	glClearColor(1.0,0.0,0.0,0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	skyboxProgram = loadShaders("skybox.vert", "skybox.frag");
	program = loadShaders("lab2.vert", "lab2.frag");

	GLfloat projectionMatrix[] = {2.0f*near/(right-left), 0.0f,
                                (right+left)/(right-left), 0.0f,
                                0.0f, 2.0f*near/(top-bottom),
                                (top+bottom)/(top-bottom), 0.0f,
                                0.0f, 0.0f, -(far + near)/(far - near),
                                -2*far*near/(far - near),
                                0.0f, 0.0f, -1.0f, 0.0f };

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, maskrosTexture);
	glUniform1i(glGetUniformLocation(program, "maskrosen"), 1);
	printError("init(): Multitexturing");
	glActiveTexture(GL_TEXTURE0);

  Point3D lightSourcesColorsArr[] = { {1.0f, 0.0f, 0.0f},   // Red light
                                      {0.0f, 1.0f, 0.0f},   // Green light
                                      {0.0f, 0.0f, 1.0f},   // Blue light
                                      {1.0f, 1.0f, 1.0f} }; // White light
	printError("init(): After lightSourcescolorsarr");
	GLfloat specularExponent[] = {10.0, 20.0, 60.0, 5.0};
	GLint isDirectional[] = {0,0,1,1};
	Point3D lightSourcesDirectionsPositions[] = { {10.0f, 5.0f, 0.0f}, // Red light, positional
																								{0.0f, 5.0f, 10.0f}, // Green light, positional
																								{-1.0f, 0.0f, 0.0f}, // Blue light along X
																								{0.0f, 0.0f, -1.0f} }; // White light along Z
	glUniform3fv(glGetUniformLocation(program, "lightSourcesDirPosArr"),
							 4, &lightSourcesDirectionsPositions[0].x);
	glUniform3fv(glGetUniformLocation(program, "lightSourcesColorArr"),
							 4, &lightSourcesColorsArr[0].x);
	glUniform1fv(glGetUniformLocation(program, "specularExponent"),
							 4, specularExponent);
	glUniform1iv(glGetUniformLocation(program, "isDirectional"),
							 4, isDirectional);
	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0

	glUseProgram(skyboxProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProgram, "texUnit"), 0); // Texture unit 0
	glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "projectionMatrix"), 1, GL_TRUE, projectionMatrix);

	printError("init(): End");
}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(20, &OnTimer, value);
	printError("OnTimer()");
}

void display(void)
{
	printError("pre display");
	cameraPos = moveOnKeyInputRelativeCamera(cameraPos);
	lookMatrix = lookAtv(cameraPos, cameraTarget, cameraNormal);

	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 5000;
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(skyboxProgram);
	glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "lookMatrix"), 1, GL_TRUE, lookMatrix.m);
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glDisable(GL_DEPTH_TEST);

	glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "transform"), 1, GL_TRUE, T(cameraPos.x, cameraPos.y, cameraPos.z).m);
	DrawModel(skybox, skyboxProgram, "in_Position", NULL, "in_TexCoord");

	glEnable(GL_DEPTH_TEST);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "lookMatrix"), 1, GL_TRUE, lookMatrix.m);
	glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, &cameraPos);
	transBlade = T(bladePos.x, bladePos.y, bladePos.z);
	for (int i = 0; i < 4; i++){
		mat4 rotBlade = Mult(Rz(M_PI / 2 * i + t), Ry(M_PI / 2));
		mat4 transform = Mult(transBlade, rotBlade);
		drawObject(transform, blade, program);
	}

	glBindTexture(GL_TEXTURE_2D, concrete);
	drawObject(transWalls, walls, program);
	drawObject(transRoof, roof, program);
	drawObject(transBalcony, balcony, program);

	glBindTexture(GL_TEXTURE_2D, grass);
	drawObject(transGround,ground, program);
	drawObject(transTeapot,teapot, program);
	drawObject(transBunny,bunny, program);

	glutSwapBuffers();
}

void drawObject(mat4 transform, Model* model, GLuint p)
{
	glUniformMatrix4fv(glGetUniformLocation(p, "transform"), 1, GL_TRUE, transform.m);
	DrawModel(model, p, "in_Position", "in_Normal", "in_TexCoord");
	printError("drawObject()");
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
  cameraTarget = (vec3) {cos((float)x / 400 * M_PI * 2) * 20,
												 cos((float)y / 400 * M_PI * 2) * 20,
												 sin((float)x / 400 * M_PI * 2) * 20};
	cameraTarget = VectorAdd(cameraTarget, cameraPos);

  lookMatrix = lookAtv(cameraPos, cameraTarget, cameraNormal);
	cameraDirection = Normalize(VectorSub(cameraTarget, cameraPos));
	printError("handleMouse()");
}



vec3 moveOnKeyInputRelativeCamera(vec3 in)
{
	vec3 forward;
	vec3 leftV;
	forward = ScalarMult(cameraDirection, 0.5f);
	leftV = ScalarMult(CrossProduct(cameraDirection, cameraNormal), 0.5f);

  if(keyIsDown('w')) {
    in.x += forward.x;
    in.y += forward.y;
    in.z += forward.z;
	}
  else if (keyIsDown('s')) {
    in.x -= forward.x;
    in.y -= forward.y;
    in.z -= forward.z;
	}

  if(keyIsDown('a')){
		in.x -= leftV.x;
    in.y -= leftV.y;
    in.z -= leftV.z;
	}
  else if(keyIsDown('d')){
		in.x += leftV.x;
    in.y += leftV.y;
    in.z += leftV.z;
	}

  if(keyIsDown('q'))
    in.z += 0.1;
  else if(keyIsDown('e'))
    in.z -= 0.1;


	printError("moveonkeyinputrelativecamera()");
  return in;
}
