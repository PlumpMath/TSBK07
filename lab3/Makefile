
all: lab2

lab2:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab2.c LoadTGA.o
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o LoadTGA.o loadobj.c VectorUtils3.c lab2.c -o lab2 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

loadobj.o: loadobj.h
	gcc -w -c loadobj.c

MicroGlut.o: MicroGlut.h
	gcc -w -c MicroGlut.c

LoadTGA.o: LoadTGA.h
	gcc -w -c LoadTGA.c

clean :
	rm lab2
