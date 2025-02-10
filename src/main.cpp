#include "WindowRenderer.hpp"
#include "Texture_generator.hpp"
#include <SDL.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

//FIXME: MAKE SURE THE BACKGROUND IS SHOWN AND MAKE A PLAY SCREEN

//Define problem
//I want to make something that uses structs to create an array of blocks that represent the snake
//The struct will hvae a property on color, position

//The struct or characteristics of the box
struct box {
	SDL_Rect atr;
	short r,g,b,a;
	bool flip;
};

//The storage for the box
std::vector<box> boxes;

//A function that can add boxes
void make_box(short r, short g, short b, short a, int x = 100, int y = 100, int w = 50, int h = 50, bool flips = false){
	box _temp_box;
	_temp_box.r = r;
	_temp_box.g = g;
	_temp_box.b = b;
	_temp_box.a = a;

	_temp_box.atr.w = w;
	_temp_box.atr.h = h;
	_temp_box.atr.x = x;
	_temp_box.atr.y = y;
	_temp_box.flip = flips;
	boxes.push_back(_temp_box);
}

using namespace std;

int main(int argc, char *argv[]) {

	//This variable holds the function to loop the game, turning it false will result in termination of the program
	bool running = true;
	//This is the Width value of the window, changing this will result in the window changing in size aswell
	int W_WIDTH = 580;
	//This is the Height value of the window, changing this will result in the window changing in size aswell
	int W_HEIGHT = 580;

	//A variable that controls the bird
	int limit = 7;
	int gravity = limit;
	SDL_Rect window_rect;
	window_rect.w = W_WIDTH;
	window_rect.h = W_HEIGHT;
	window_rect.x = window_rect.y = 0;

	//Textures

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cerr << "IMG_Init Error" << IMG_GetError << std::endl;
		return 1;
	}
	//BIrd
	make_box(255,0,255,255, 100,400, 20, 20);
	//Pillars
	
	//Initializes the time sicne the program started
	Uint32 start_time = SDL_GetTicks();	
	const Uint32 interval = 2500;

	// classes iniialization bing chilling
	RenderWindow screen("Project x", W_WIDTH, W_HEIGHT);

	//Loaded images
	SDL_Texture *pipe = generate_texture::load_texture("../res/gfx/pipe.png");
	SDL_Texture *bg = generate_texture::load_texture("../res/gfx/background-day.png");
	SDL_Texture *bird = generate_texture::load_texture("../res/gfx/yellowbird-midflap.png");
	

	const Uint8* KeyboardState = SDL_GetKeyboardState(nullptr);
	SDL_Event event;
 	while (running) {
    	while (SDL_PollEvent(&event)) {
    		switch (event.type) {
    		case SDL_QUIT:
    			running = false;
      		  	break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym){
					// KEY SYSTEM HERE
					case SDLK_ESCAPE:
						running = false;
						break;
					case SDLK_SPACE:
						gravity = -10;
						std::cout << "jumped\n";
						break;
					case SDLK_a:
						break;
					case SDLK_d:
						break;
					default:
						break;
					}
				}
			case SDL_KEYUP:
				break;
			default:
				break;
		}
	}

	if (KeyboardState[SDL_SCANCODE_D]){
	} else if (KeyboardState[SDL_SCANCODE_A]){
	} else if (KeyboardState[SDL_SCANCODE_W]){
	} else if (KeyboardState[SDL_SCANCODE_S]){
	}
    // FPS (35)
    const int frameDelay = 1000 / 60;
    int frameStart = SDL_GetTicks();

	//Boundary
	// if (rect.x < 0){
	// 	rect.x = 0;
	// } else if (rect.x + rect.w > W_WIDTH){
	// 	rect.x = W_WIDTH - rect.w;
	// } else if (rect.y + rect.h > W_HEIGHT){
	// 	rect.y = W_HEIGHT - rect.h;
	// } else if (rect.y < 0){
	// 	rect.y = 0;
	// }

	
	
	if (gravity >= limit){
		gravity = limit;
	} else {
		gravity++;
	}

	Uint32 current_time = SDL_GetTicks();
	if (current_time - start_time >= interval){
		int random = (rand() % 200) + 100;
		int gap = 100;
		//short r, short g, short b, short a, short x = 100, short y = 100, int w = 50, int h = 50
		make_box(255,0,255,255, W_WIDTH,0, 50,random, true);
		make_box(0,0,0,255, W_WIDTH,random+gap, 50,W_HEIGHT-(random+gap));
		
		std::cout << "a second has passed\n";
		start_time = current_time;
	}

	//This writes sets the color of the whole screen
    // SDL_SetRenderDrawColor(RenderWindow::getRenderer(), 255, 255, 255, 255);
	
    screen.clear();
	SDL_RenderCopy(RenderWindow::getRenderer(), bg, NULL, &window_rect);

	//This renders the pillars
	for (int i = 1; i <= boxes.size() - 1; i++){
		// SDL_SetRenderDrawColor(RenderWindow::getRenderer(), boxes[i].r, boxes[i].g, boxes[i].b, boxes[i].a);
		if (!boxes[i].flip){
			SDL_RenderCopy(RenderWindow::getRenderer(), pipe, NULL, &boxes[i].atr);
		} else {
			SDL_RenderCopyEx(RenderWindow::getRenderer(), pipe, NULL, &boxes[i].atr, 0.0, NULL, SDL_FLIP_VERTICAL);
		}
		// SDL_RenderFillRect(RenderWindow::getRenderer(), &boxes[i].atr);
		//Constantly checks for the rects if it's outside the screen which will delete the rect if true
		if (boxes[i].atr.x <= -100){
			boxes.erase(boxes.begin() + i);
			printf("Pillar deleted because out of bounds.\n");
		}
		//This line below makes all the rects from 1 to ? move to the left by 1 pixel each iteration
		boxes[i].atr.x += -1;
		//Bottom detect top											//Top detect bottom									//Right detect left										//Left detect right
		if (boxes[0].atr.y + boxes[0].atr.h >= boxes[i].atr.y && boxes[0].atr.y <= boxes[i].atr.y + boxes[i].atr.h && boxes[0].atr.x + boxes[0].atr.w >= boxes[i].atr.x && boxes[0].atr.x <= boxes[i].atr.x + boxes[i].atr.w){
			printf("Collision detected\n");
			running = false;
		}
	}
	//Bird rendering
	// SDL_SetRenderDrawColor(RenderWindow::getRenderer(), boxes[0].r, boxes[0].g, boxes[0].b, boxes[0].a);
	// SDL_RenderFillRect(RenderWindow::getRenderer(), &boxes[0].atr);
	SDL_RenderCopy(RenderWindow::getRenderer(), bird, NULL, &boxes[0].atr);
	boxes[0].atr.y += gravity;
	//This keeps the 
	if (boxes[0].atr.y + boxes[0].atr.h >= W_HEIGHT){
		boxes[0].atr.y = W_HEIGHT - boxes[0].atr.h;
	}
	//This presents the screen
    screen.present();

	//FPS LIMITTER
	int frameTime = SDL_GetTicks() - frameStart;  // Correct elapsed time
	if (frameDelay > frameTime) {
    	SDL_Delay(frameDelay - frameTime);
}
  }
  screen.clean();
  return 0;
}