
all : lab4-1

lab4-1: lab4-1.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c
	gcc -Wall -std=c99 -o lab4-1 -DGL_GLEXT_PROTOTYPES lab4-1.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c  -lGL -lglut -lm

clean :
	rm lab4-1
