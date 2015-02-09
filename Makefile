
all: lab1-1 lab1-4

lab1-1:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-1.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-1.c -o lab1-1 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

lab1-4:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-4.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-4.c -o lab1-4 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

MicroGlut.o: MicroGlut.h
	gcc -w -c MicroGlut.c

clean :
	rm lab1-1
