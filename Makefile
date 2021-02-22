
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17

__start__: ./dron_podwodny
	./dron_podwodny


./dron_podwodny: obj obj/main.o obj/surface.o obj/obiekt.o obj/stage.o obj/lacze_do_gnuplota.o obj/hexagon.o obj/dron.o
	g++ -Wall -pedantic -o dron_podwodny obj/main.o obj/stage.o obj/surface.o obj/obiekt.o obj/lacze_do_gnuplota.o\
				obj/hexagon.o obj/dron.o

obj:
	mkdir -p obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/surface.o: inc/surface.hh src/surface.cpp
	g++ -c ${CXXFLAGS} -o obj/surface.o src/surface.cpp

obj/obiekt.o: inc/obiekt.hh inc/TVector.hh inc/surface.hh src/obiekt.cpp
	g++ -c ${CXXFLAGS} -o obj/obiekt.o src/obiekt.cpp

obj/hexagon.o: inc/hexagon.hh src/hexagon.cpp inc/surface.hh
	g++ -c ${CXXFLAGS} -o obj/hexagon.o src/hexagon.cpp

obj/dron.o: inc/dron.hh src/dron.cpp inc/hexagon.hh inc/obiekt.hh
	g++ -c ${CXXFLAGS} -o obj/dron.o src/dron.cpp

obj/stage.o: inc/stage.hh inc/obiekt.hh inc/lacze_do_gnuplota.hh src/stage.cpp
	g++ -c ${CXXFLAGS} -o obj/stage.o src/stage.cpp

obj/main.o: inc/stage.hh src/main.cpp
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -rf obj
