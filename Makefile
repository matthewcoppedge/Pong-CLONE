CXX = g++ -std=c++17

CFLAGS = -O3 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

pong: main.o pong.o player.o
	$(CXX) -o pong main.o pong.o player.o $(CFLAGS)

main.o: main.cpp pong.h
	$(CXX) -c main.cpp $(CFLAGS)

pong.o: pong.cpp pong.h
	$(CXX) -c pong.cpp $(CFLAGS) 

player.o: player.cpp player.h
	$(CXX) -c player.cpp $(CFLAGS)

clean:
	rm *.o -f pong
