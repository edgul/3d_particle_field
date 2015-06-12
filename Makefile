CC=g++
GLflags= -lglut -lGL -lGLU

a2: a2.cpp 2DMathLib_Revised.cpp
	$(CC) a2.cpp 2DMathLib_Revised.cpp -o a2 $(GLflags)

clean:
	rm -f a2 
