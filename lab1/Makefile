
all: lab1-1 lab1-2 lab1-3 lab1-4 lab1-5 lab1-6

lab1-1:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-1.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-1.c -o lab1-1 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

lab1-2:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-2.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-2.c -o lab1-2 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

lab1-4:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-4.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-4.c -o lab1-4 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

lab1-5:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-5.c
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-5.c -o lab1-5 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

lab1-6:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-6.c loadobj.o
	gcc -std=c99 -Wall GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c lab1-6.c -o lab1-6 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

loadobj.o: loadobj.h
	gcc -w -c loadobj.c

MicroGlut.o: MicroGlut.h
	gcc -w -c MicroGlut.c

clean :
	rm lab1-1 lab1-2 lab1-6
