#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "game.hpp"

#define WINDOW_TITLE "Flappy Bird"
#define WINDOW_X 20
#define WINDOW_Y 20

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define BIRD_H 20
#define BIRD_W 20
#define BIRD_FALL 1
#define BIRD_JUMP 30

#define PIPE_W 30
Game::Game()
{
	window = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		error_quit("init");
	}

	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		error_quit("window init");
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		std::cout << "Renderer not found! SDL_Error: " << SDL_GetError() << std::endl;
		error_quit("renderer init");
	}
	running = true;
	for (int i = 0; i < 640 + 50; i += 50)
	{
		PipePair ppair = generate_pipe_pair();
		ppair.first.x = i;
		ppair.second.y = i;
		pipes.push_back(ppair.first);
		pipes.push_back(ppair.second);
	}
	bird.h = BIRD_H;
	bird.w = BIRD_W;
	bird.x = 0;
	bird.y = pipes.front().h + 10;
}

void Game::run()
{
	while (running)
	{
		SDL_Delay(10);
		event_handler();
		update();
		if (is_gameOver())
		{
			running = false;
		}
	}
}

Game::~Game()
{
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	if (SDL_WasInit(SDL_INIT_VIDEO))
	{
		SDL_Quit();
	}
}

void Game::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 135, 251, 1);
	SDL_RenderClear(renderer);
	handle_pipes();
	draw_pipes();
	draw_bird();
	bird.y += BIRD_FALL;
	for (std::deque<SDL_Rect>::iterator it = pipes.begin(); it != pipes.end(); it++)
	{
		it->x -= 1;
	}
	SDL_RenderPresent(renderer);
}

void Game::draw_bird()
{
	SDL_SetRenderDrawColor(renderer, 179, 211, 23, 1);
	SDL_RenderFillRect(renderer, &bird);
}

void Game::draw_pipes()
{
	SDL_SetRenderDrawColor(renderer, 0, 180, 0, 1);
	for (SDL_Rect p : pipes)
	{
		SDL_RenderFillRect(renderer, &p);
	}
}

bool Game::is_gameOver()
{
	for (SDL_Rect p : pipes)
	{
		if (SDL_HasIntersection(&p, &bird) == SDL_TRUE)
		{
			return true;
		}
	}
	if (bird.y + bird.w >= 480)
	{
		return true;
	}
	return false;
}

void Game::handle_pipes()
{
	if (pipes.front().x + pipes.front().w > 0)
	{
		return;
	}
	pipes.pop_front();
	pipes.pop_front();
	PipePair pipe_pair = generate_pipe_pair();
	pipes.push_back(pipe_pair.first);
	pipes.push_back(pipe_pair.second);
}

#define PIPE_GAP 200
PipePair Game::generate_pipe_pair()
{
	PipePair ppair;

	ppair.first.h = rand() % 150;
	ppair.second.y = ppair.first.h + PIPE_GAP;

	ppair.first.x = 610;
	ppair.first.y = 0;
	ppair.first.w = PIPE_W;
	ppair.second.x = 610;
	ppair.second.w = PIPE_W;
	ppair.second.h = 490 - ppair.second.y;
	return ppair;
}

void Game::event_handler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym){
			case SDLK_UP:
				if (bird.y + bird.h > 0)
				{
					bird.y -= BIRD_JUMP;
				}
				break;
			}
			break;
		}
	}
}

void Game::error_quit(std::string msg){
	std::cerr << "ERROR: "<<msg <<std::endl;
	exit(1);
}