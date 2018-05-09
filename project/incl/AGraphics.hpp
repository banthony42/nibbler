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

#include <string>
#include <vector>
#include <cmath>

// TODO du fait de la var _eventList en static => singleton ? sinon -> _eventList[NB_STATE]

// Nombre de caracteres par ligne sur la texture
#define NB_CHAR 16

// Taille de la case pouvant contenir tout les caracteres
#define CHAR_SIZE_X 32
#define CHAR_SIZE_Y 47

typedef struct {
	double x;
	double y;
} t_coordd;

typedef struct {
	int x;
	int y;
} t_coordi;	// TODO verifier dans les Graphics si on peut remplacer

enum eEvent {
	EVENT_VOID,
	ECHAP,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ENTER,
	NB_EVENT
};

// TODO add the name of the lib on the screen


class AGraphics {

public:

	virtual int init(int windowWidth, int windowHeight, std::string windowName) = 0;
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

	int centerTextX(std::string str, float size) {
		float s = size;
		if (s <= 0)
			s = 1;
		return ((this->windowWidth / 2) - static_cast<int>((str.length() / 2) * round((CHAR_SIZE_X / 2.5) * s)));
	}

protected:
	static std::vector<eEvent> _eventList; //TODO t_coord sizeFont
	int windowWidth;
	int windowHeight;

};

#endif //NIBBLER_IGRAPHICS_HPP
