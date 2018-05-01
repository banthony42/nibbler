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

// TODO du fait de la var _eventList en static => singleton ? sinon -> _eventList[NB_STATE]

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


class AGraphics {

public:

	virtual int init(int windowWidth, int windowHeight) = 0;
	virtual int loopUpdate() = 0;
	virtual void updateScreen() = 0;
	virtual void putStrScreen(std::string str) = 0;
	virtual void loadTexture(std::string path, int key) = 0;
	virtual void cleanUp() = 0;
	virtual void closeWindow() = 0;
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

protected:
	 static std::vector<eEvent> _eventList;
    int windowHeigth;
    int windowLenght;

};

#endif //NIBBLER_IGRAPHICS_HPP
