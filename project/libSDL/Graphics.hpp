#ifndef LIBSDL_GRAPHICS_HPP
#define LIBSDL_GRAPHICS_HPP

#include "../incl/AGraphics.hpp"
#include <iostream>
#include <SDL2/SDL.h>

class Graphics : public AGraphics {

public:
	Graphics(); // Canonical
	Graphics(Graphics const &copy); // Canonical
	~Graphics(); // Canonical

	Graphics &operator=(Graphics const &copy);
	int init(int windowWidth, int windowHeight);
	int loopUpdate();
	void display();
	void clear();
	void putStrScreen(std::string str, int posX, int posY, float size);
	void loadTexture(std::string path, int key);
	void putTexture(int key, int posX, int posY, int sizeX, int sizeY);
	void cleanUp();
	void closeWindow();
	std::vector<eEvent> &getEvent();
	unsigned char getChar();

private:
	bool _windowTerminated;
	SDL_Window *_win;
	SDL_Surface *_img;

};

extern "C" {
Graphics *createGraphics();
void deleteGraphics(Graphics *graphics);
}

#endif //LIBSDL_GRAPHICS_HPP