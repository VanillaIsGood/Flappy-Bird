all:
	g++ -Iinclude -Iinclude/sdl -Iheaders -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf