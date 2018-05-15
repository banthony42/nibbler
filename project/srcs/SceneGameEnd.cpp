/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGameEnd.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:54 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneGameEnd.hpp"

SceneGameEnd::SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(SceneGameEnd const &copy) {
    *this = copy;
}

SceneGameEnd::~SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
}

SceneGameEnd &SceneGameEnd::operator=(SceneGameEnd const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneGameEnd::eventHandler(std::vector<eEvent> eventList) {
    for (auto &event : eventList) {
        if (event == ECHAP) {
            Nibbler::setCurrentScene(MENU);
        }
        else if (event == ENTER) {
            Nibbler::setCurrentScene(GAME);
        }
    }
}

void SceneGameEnd::drawScene() {
//	// GAME END preview
    (*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(SCORE_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	(*this->_aGraphics)->putStrScreen("BEST SCORE: 2500", (900) - (4 * 32), 550, 2);
	(*this->_aGraphics)->putStrScreen("< Replay >", (900) - (5 * 32), 700, 2);
	(*this->_aGraphics)->putStrScreen("Menu", (900) - (3 * 32), 750, 2);

    (*this->_aGraphics)->display();
}

