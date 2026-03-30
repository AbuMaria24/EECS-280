tests.exe: DiceCounter.cpp LectureVector.cpp tests.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g DiceCounter.cpp LectureVector.cpp tests.cpp -o tests.exe

tests_asan.exe: DiceCounter.cpp LectureVector.cpp tests.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g DiceCounter.cpp LectureVector.cpp tests.cpp -o tests_asan.exe
