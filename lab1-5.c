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
#include <math.h>

// Globals
// Data would normally be read from files
GLfloat vertices[] = {
	-0.3f,-0.3f,-0.3f,
	-0.3f,-0.3f, 0.3f,
	-0.3f, 0.3f, 0.3f,
	0.3f, 0.3f,-0.3f,
	-0.3f,-0.3f,-0.3f,
	-0.3f, 0.3f,-0.3f,
	0.3f,-0.3f, 0.3f,
	-0.3f,-0.3f,-0.3f,
	0.3f,-0.3f,-0.3f,
	0.3f, 0.3f,-0.3f,
	0.3f,-0.3f,-0.3f,
	-0.3f,-0.3f,-0.3f,
	-0.3f,-0.3f,-0.3f,
	-0.3f, 0.3f, 0.3f,
	-0.3f, 0.3f,-0.3f,
	0.3f,-0.3f, 0.3f,
	-0.3f,-0.3f, 0.3f,
	-0.3f,-0.3f,-0.3f,
	-0.3f, 0.3f, 0.3f,
	-0.3f,-0.3f, 0.3f,
	0.3f,-0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f,-0.3f,-0.3f,
	0.3f, 0.3f,-0.3f,
	0.3f,-0.3f,-0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f,-0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f,-0.3f,
	-0.3f, 0.3f,-0.3f,
	0.3f, 0.3f, 0.3f,
	-0.3f, 0.3f,-0.3f,
	-0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	-0.3f, 0.3f, 0.3f,
	0.3f,-0.3f, 0.3f
};
GLfloat colors[] =
{
	0.383f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.369f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.397f,  0.770f,  0.761f,
	0.359f,  0.436f,  0.730f,
	0.359f,  0.383f,  0.152f,
	0.483f,  0.396f,  0.789f,
	0.359f,  0.861f,  0.639f,
	0.195f,  0.348f,  0.859f,
	0.014f,  0.184f,  0.376f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.372f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.313f,  0.064f,
	0.945f,  0.719f,  0.392f,
	0.343f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.305f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.305f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.387f,  0.040f,
	0.317f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};



GLfloat translation[] = {    1.0f, 0.0f, 0.0f, -0.3f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f };

// vertex array object
unsigned int vertexArrayObjID;
GLuint program;
void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int vertexBufferObjID;
	// Reference to shader program

	dumpInfo();

	// GL inits
	glClearColor(1.0,0.0,0.0,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Load and compile shader
	program = loadShaders("lab1-5.vert", "lab1-5.frag");
	printError("init shader");

	// Upload geometry to the GPU:

	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);
	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);

	// VBO for vertex datarotation
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 9*12*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	// End of upload of geometry
	glGenBuffers(1, &vertexBufferObjID);

	// VBO for vertex datarotation
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 9*12*sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "blaha"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "blaha"));
	printError("init arrays");
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

	glBindVertexArray(vertexArrayObjID);	// Select VAO
	glDrawArrays(GL_TRIANGLES, 0, 3*12);	// draw object

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
