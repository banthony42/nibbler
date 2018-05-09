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
    (void)eventList;
}

void SceneGameEnd::drawScene() {

}

