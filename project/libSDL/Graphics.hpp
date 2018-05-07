/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:11:52 by banthony          #+#    #+#             */
/*   Updated: 2018/05/07 18:11:52 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "../incl/AGraphics.hpp"
#include "../incl/Nibbler.hpp"

// Calcul de la position en pixel dans la texture pour le caracatere c
#define FONT_START_X(c) (CHAR_SIZE_X * ((c - '!') % NB_CHAR))
#define FONT_START_Y(c) (CHAR_SIZE_Y * ((c - '!') / NB_CHAR))

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
	std::map<int, SDL_Surface *> _textureList;

	void putCharScreen(char const c, t_coord pos, t_coord sizeText, t_coord sizeFont);

};

extern "C" {
Graphics *createGraphics();
void deleteGraphics(Graphics *graphics);
}

#endif //LIBSDL_GRAPHICS_HPP