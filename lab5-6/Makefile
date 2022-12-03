all: libs

libs: headers
	g++ -Wall -Werror -Wextra main.o -o lab5 -L ../SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=../SFML-2.5.1/lib && ./lab5

headers:
	g++ -Wall -Werror -Wextra -c main.cpp -I ../SFML-2.5.1/include

clean:
	rm -rf *.o lab5


