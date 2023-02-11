#ifndef game_hpp
#define game_hpp

#include<string>
#include<deque>
#include<SDL2/SDL.h>

class Game{
	public:
		Game();
		void run();
		~Game();
	private:
		SDL_Renderer *renderer;
		SDL_Window *window;
		bool running;
		SDL_Rect bird;
		std::deque<SDL_Rect> pipes;

		void update();
		void draw_bird();
		void draw_pipes();
		bool is_gameOver();
		void handle_pipes();
		PipePair generate_pipe_pair();
		void event_handler();
		void error_quit(std::string message);
};
#endif
