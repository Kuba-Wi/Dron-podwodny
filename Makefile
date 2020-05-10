
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17

__start__: ./dron_podwodny
	./dron_podwodny


./dron_podwodny: obj obj/main.o obj/powierzchnia.o obj/obiekt.o obj/scena.o obj/lacze_do_gnuplota.o
	g++ -Wall -pedantic -o dron_podwodny obj/main.o obj/scena.o obj/powierzchnia.o obj/obiekt.o obj/lacze_do_gnuplota.o

obj:
	mkdir -p obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/powierzchnia.o: inc/powierzchnia.hh src/powierzchnia.cpp
	g++ -c ${CXXFLAGS} -o obj/powierzchnia.o src/powierzchnia.cpp

obj/obiekt.o: inc/obiekt.hh inc/SWektor.hh inc/powierzchnia.hh src/obiekt.cpp
	g++ -c ${CXXFLAGS} -o obj/obiekt.o src/obiekt.cpp

obj/scena.o: inc/scena.hh inc/obiekt.hh inc/lacze_do_gnuplota.hh src/scena.cpp
	g++ -c ${CXXFLAGS} -o obj/scena.o src/scena.cpp

obj/main.o: inc/scena.hh src/main.cpp
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -rf obj
