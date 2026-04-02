test: iterator_test.exe functor_test.exe
	./iterator_test.exe
	./functor_test.exe

iterator_test.exe: iterator_test.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g iterator_test.cpp -o iterator_test.exe

iterator_test_asan.exe: iterator_test.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g iterator_test.cpp -o iterator_test_asan.exe

functor_test.exe: functor_test.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g functor_test.cpp -o functor_test.exe

functor_test_asan.exe: functor_test.cpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g functor_test.cpp -o functor_test_asan.exe

all_asan: iterator_test_asan.exe functor_test_asan.exe