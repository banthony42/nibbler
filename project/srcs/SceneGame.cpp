/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGame.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:47 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:47 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneGame.hpp"

SceneGame::SceneGame() {

}

SceneGame::SceneGame(SceneGame const &copy) {
    *this = copy;
}

SceneGame::~SceneGame() {

}

SceneGame &SceneGame::operator=(SceneGame const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneGame::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneGame::drawScene() {
    (void)this->_food;
    (void)this->_snake;
}

SceneGame::SceneGame(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}

void SceneGame::moveSnake() {

}
