all: libs

libs: headers
	g++ -Wall -Werror -Wextra main.o -o lab3 -L ../SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

headers:
	g++ -Wall -Werror -Wextra -c main.cpp -I ../SFML-2.5.1/include

clean:
	rm -rf *.o lab3


