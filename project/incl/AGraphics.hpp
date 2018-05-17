/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphics.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:06:02 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 18:06:02 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AGRAPHICS_HPP
#define AGRAPHICS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Nombre de caracteres par ligne sur la texture
#define NB_CHAR 16

// Taille de la case pouvant contenir tout les caracteres
#define CHAR_SIZE_X 32
#define CHAR_SIZE_Y 47

#define GET_SIZEFONT_X(s) ((CHAR_SIZE_X / 2.5) * s)
#define GET_SIZEFONT_Y(s) ((CHAR_SIZE_Y / 2.5) * s)
#define FONT_NEWLINE(x) x * 20

typedef struct {
	double x;
	double y;
} t_coordd;

typedef struct {
	int x;
	int y;
} t_coordi;

enum eEvent {
	EVENT_VOID,
	ECHAP,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ENTER,
    F1,
    F2,
    F3,
	NB_EVENT
};

class AGraphics {

public:

	virtual void init(int windowWidth, int windowHeight, std::string windowName) = 0;
	virtual int loopUpdate() = 0;
	virtual void display() = 0;
	virtual void clear() = 0;
	virtual void putCharScreen(char const c, t_coordd pos, t_coordd sizeFont) = 0;
	virtual void putStrScreen(std::string str, int posX, int posY, float size) = 0;
	virtual void loadFontTexture(std::string path) = 0;
	virtual void loadTexture(std::string path, int key) = 0;
	virtual void putTexture(int key, int posX, int posY, int sizeX, int sizeY) = 0;
	virtual void cleanUp() = 0;
	virtual std::vector<eEvent> &getEvent() = 0;
	virtual unsigned char getChar() = 0;

	/*
	 * Permet la modification de _eventList dans la fonction
	 * de callback en dehors d'une classe Graphics
	 */
	static void addEvent(eEvent event) {
		AGraphics::_eventList.push_back(event);
	}

	static void clearEvent() {
		AGraphics::_eventList.clear();
	}

	static int centerTextX(std::string str, float size, int w) {
        int rest = 0;
		if (size <= 0) {
			size = 1;
		}
        if (str.length() % 2)
            rest = static_cast<int>(GET_SIZEFONT_X(size) / 2);
		return ((w / 2) - static_cast<int>(((str.length() / 2) * GET_SIZEFONT_X(size)) + rest));
	}

protected:
	static std::vector<eEvent> _eventList;
	int windowWidth;
	int windowHeight;
};

#endif //NIBBLER_IGRAPHICS_HPP
