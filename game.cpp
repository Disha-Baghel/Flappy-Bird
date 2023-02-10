#include<iostream>
#include<cstdlib>
#include<SDL2/SDL.h>
#include"game.hpp"

#define WINDOW_TITLE "Title"
#define WINDOW_X 20
#define WINDOW_Y 20

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define BIRD_H 20
#define BIRD_W 20
#define BIRD_FALL 1
#define BIRD_JUMP 30

#define PIPE_W 30
Game::Game(){
	window = NULL;
	renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;
	}
	else{
		window = SDL_CreateWindow("Flappy Bird", WINDOW_X, WINDOW_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if(window == NULL){
			std::cout<<"Window could not be createe! SDL_Error: "<<SDL_GetError()<<std::endl;
			error_quit("window init");
		}
		else{

