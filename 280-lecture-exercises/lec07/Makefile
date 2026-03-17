test: driver.exe tests.exe
	./tests.exe
	./driver.exe mat1.txt mat2.txt actual.txt
	diff -Z expected.txt actual.txt

driver.exe: driver.cpp Matrix.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g driver.cpp Matrix.cpp -o driver.exe

tests.exe: tests.cpp Matrix.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g tests.cpp Matrix.cpp -o tests.exe

