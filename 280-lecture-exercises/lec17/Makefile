tests.exe: Book.cpp Library.cpp tests.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g Book.cpp Library.cpp tests.cpp -o tests.exe

tests_asan.exe: Book.cpp Library.cpp tests.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g Book.cpp Library.cpp tests.cpp -o tests_asan.exe
