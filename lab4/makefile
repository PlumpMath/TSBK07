
all : lab4

lab4: lab4.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c
	gcc -Wall -std=c99 -o lab4 -DGL_GLEXT_PROTOTYPES lab4.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c  -lGL -lglut -lm

clean :
	rm lab4
