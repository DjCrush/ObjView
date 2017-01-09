all:
	# stof() in <string> is C++11 standard
	g++ -std=c++11 -o ObjView mygraphicslib.cpp object.cpp Source.cpp `sdl-config --cflags --libs`
