
all: lab2

lab2:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab2.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab2.c -o lab2 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

loadobj.o: loadobj.h
	gcc -w -c loadobj.c

MicroGlut.o: MicroGlut.h
	gcc -w -c MicroGlut.c

clean :
	rm lab2
