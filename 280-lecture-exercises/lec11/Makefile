array_puzzles_test.exe: array_puzzles_test.cpp array_puzzles.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g array_puzzles_test.cpp array_puzzles.cpp -o array_puzzles_test.exe

array_puzzles_test_asan.exe: array_puzzles_test.cpp array_puzzles.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g array_puzzles_test.cpp array_puzzles.cpp -o array_puzzles_test_asan.exe
