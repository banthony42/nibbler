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
    this->_cursor = REPLAY;
    this->_inputName[BEST_SCORE] = "Best Score:" + std::to_string(1542); //TODO put here the variable of the best score for the session
    this->_inputName[REPLAY] = "Replay";
    this->_inputName[BACK_TO_MENU] = "Menu";
    t_coordi pos = {};
    pos.x = PERCENTAGE(62, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(59, Nibbler::getWindowHeight());
    this->_input[BEST_SCORE] = pos;
    pos.x += PERCENTAGE(3, Nibbler::getWindowWidth());
    pos.y += FONT_NEWLINE(SIZE_FONT_GAME_END) * 2;
    this->_input[REPLAY] = pos;
    pos.x += ((this->_inputName[REPLAY].length() - this->_inputName[BACK_TO_MENU].length()) / 2) *
             GET_SIZEFONT_X(SIZE_FONT_GAME_END);
    pos.y += FONT_NEWLINE(SIZE_FONT_GAME_END);
    this->_input[BACK_TO_MENU] = pos;
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
        } else if (event == UP && this->_cursor > REPLAY) {
            this->_cursor--;
        } else if (event == DOWN && this->_cursor < BACK_TO_MENU) {
            this->_cursor++;
        } else if (event == ENTER) {
            if (this->_cursor == REPLAY) {
                Nibbler::setCurrentScene(GAME);
            } else if (this->_cursor == BACK_TO_MENU) {
                Nibbler::setCurrentScene(MENU);
            }
            this->_cursor = REPLAY;
        }
    }
}

void SceneGameEnd::drawScene() {
//	// GAME END preview
    (*this->_aGraphics)->clear();

    (*this->_aGraphics)->putTexture(SCORE_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
    (*this->_aGraphics)->putStrScreen(this->_inputName[BEST_SCORE], this->_input[BEST_SCORE].x,
                                      this->_input[BEST_SCORE].y + 20, SIZE_FONT_GAME_END);
    (*this->_aGraphics)->putStrScreen(this->_inputName[REPLAY], this->_input[REPLAY].x, this->_input[REPLAY].y,
                                      SIZE_FONT_GAME_END);
    (*this->_aGraphics)->putStrScreen(this->_inputName[BACK_TO_MENU], this->_input[BACK_TO_MENU].x,
                                      this->_input[BACK_TO_MENU].y, SIZE_FONT_GAME_END);

    // Draw Cursor
    eEndGame curs = static_cast<eEndGame >(this->_cursor);
    t_coordi posCurs = {};

    posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_GAME_END));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_GAME_END);
    posCurs.x = static_cast<int>(this->_input[curs].x +
                                 ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_GAME_END)));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_GAME_END);

    (*this->_aGraphics)->display();
}

