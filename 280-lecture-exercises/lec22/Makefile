test.exe: test.cpp ForwardList.hpp
	bash check_recursion.sh ForwardList.hpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -g test.cpp -o test.exe

test_asan.exe: test.cpp ForwardList.hpp
	bash check_recursion.sh ForwardList.hpp
	g++ -g -Wall -Werror -pedantic -std=c++11 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g test.cpp -o test_asan.exe

all_asan: test_asan.exe
