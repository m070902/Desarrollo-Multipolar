
executable: main.o
	g++ main.o -o executable

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o executable
