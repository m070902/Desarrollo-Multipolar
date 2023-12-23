
final.exe: main.o
	g++ main.o -g -o final.exe

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o final.exe

debug:
	gdb ./final.exe
