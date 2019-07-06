
LIBS = -lglut -lGL -lGLU

p4.out: main.o fileHandling.o lineAlgorithms.o curves.o boundingBox.o menuOperations.o
	g++ -g -o p4.out main.o fileHandling.o lineAlgorithms.o curves.o boundingBox.o menuOperations.o $(LIBS)

main.o: main.cpp PixelBuffer.h fileHandling.h lineAlgorithms.h boundingBox.h menuOperations.h
	g++ -g $(LIBS) -c main.cpp

fileHandling.o: fileHandling.cpp fileHandling.h curves.h
	g++ -g $(LIBS) -c fileHandling.cpp

lineAlgorithms.o: lineAlgorithms.cpp lineAlgorithms.h
	g++ -g $(LIBS) -c lineAlgorithms.cpp

curves.o: curves.cpp curves.h
	g++ -g $(LIBS) -c curves.cpp

boundingBox.o: boundingBox.cpp boundingBox.h
	g++ -g $(LIBS) -c boundingBox.cpp

menuOperations.o: menuOperations.cpp menuOperations.o
	g++ -g $(LIBS) -c menuOperations.cpp

clean:
	rm -f main.o fileHandling.o lineAlgorithms.o curves.o boundingBox.o menuOperations.o
