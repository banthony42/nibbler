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

#ifndef NIBBLER_IGRAPHICS_HPP
#define NIBBLER_IGRAPHICS_HPP

#include <string>
#include <vector>

// TODO add the define for the window size en PUBLIC STATIC
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

	virtual int init() = 0;
	virtual int loopUpdate() = 0;
	virtual void updateScreen() = 0;
	virtual void putStrScreen(std::string str) = 0;
	virtual void loadTexture(std::string path) = 0;
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

};

#endif //NIBBLER_IGRAPHICS_HPP
