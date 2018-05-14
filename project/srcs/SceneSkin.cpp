/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneSkin.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:49:05 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:49:05 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneSkin.hpp"
#include "../incl/Nibbler.hpp"
#include "../incl/AGraphics.hpp"

SceneSkin::SceneSkin() {
	
}

SceneSkin::SceneSkin(SceneSkin const &copy) {
    *this = copy;
}

SceneSkin::~SceneSkin() {

}

SceneSkin &SceneSkin::operator=(SceneSkin const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

SceneSkin::SceneSkin(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_cursor = SNAKE_H_PCM;

    t_coordi pos = { SKIN_START_X(50), SKIN_START_Y(17) };
    this->_input[SNAKE_H_PCM] = pos;

    pos.y = SKIN_START_Y(48.5);
    this->_input[SNAKE_H_SMB] = pos;

    pos.y = SKIN_START_Y(79);
    this->_input[SNAKE_H_HK] = pos;
}

void SceneSkin::eventHandler(std::vector<eEvent> eventList) {
	for (auto &event : eventList) {
		if (event == ECHAP) {
			Nibbler::setCurrentScene(MENU);
		}
        else if (event == UP && this->_cursor > SNAKE_H_PCM) {
            this->_cursor--;
        }
        else if (event == DOWN && this->_cursor < SNAKE_H_HK) {
            this->_cursor++;
        }
        else if (event == ENTER) {
            SceneGame::_selectedHeadSkin = static_cast<eTexture >(this->_cursor);
            SceneGame::_selectedBodySkin = static_cast<eTexture >(this->_cursor + NB_SKIN);
            Nibbler::setCurrentScene(GAME);
        }
	}
}

void SceneSkin::drawScene() {
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(SKIN_FRAME, FRAME_START_X, FRAME_START_Y, FRAME_WIDTH, FRAME_HEIGHT);

    (*this->_aGraphics)->putTexture(SNAKE_H_PCM, this->_input[SNAKE_H_PCM].x, this->_input[SNAKE_H_PCM].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_PCM, SKIN_B_START_X(this->_input[SNAKE_H_PCM].x, 1), this->_input[SNAKE_H_PCM].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_PCM, SKIN_B_START_X(this->_input[SNAKE_H_PCM].x, 2), this->_input[SNAKE_H_PCM].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_PCM, SKIN_B_START_X(this->_input[SNAKE_H_PCM].x, 3), this->_input[SNAKE_H_PCM].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);

    (*this->_aGraphics)->putTexture(SNAKE_H_SMB, this->_input[SNAKE_H_SMB].x, this->_input[SNAKE_H_SMB].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_SMB, SKIN_B_START_X(this->_input[SNAKE_H_SMB].x, 1), this->_input[SNAKE_H_SMB].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_SMB, SKIN_B_START_X(this->_input[SNAKE_H_SMB].x, 2), this->_input[SNAKE_H_SMB].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_SMB, SKIN_B_START_X(this->_input[SNAKE_H_SMB].x, 3), this->_input[SNAKE_H_SMB].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);

    (*this->_aGraphics)->putTexture(SNAKE_H_HK, this->_input[SNAKE_H_HK].x, this->_input[SNAKE_H_HK].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_HK, SKIN_B_START_X(this->_input[SNAKE_H_HK].x, 1), this->_input[SNAKE_H_HK].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_HK, SKIN_B_START_X(this->_input[SNAKE_H_HK].x, 2), this->_input[SNAKE_H_HK].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);
    (*this->_aGraphics)->putTexture(SNAKE_B_HK, SKIN_B_START_X(this->_input[SNAKE_H_HK].x, 3), this->_input[SNAKE_H_HK].y, SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);

    // Draw Cursor
    eTexture curs = static_cast<eTexture>(this->_cursor);
    t_coordi posCurs = {};

    posCurs.x = static_cast<int>((PERCENTAGE(50, Nibbler::getWindowWidth())) - (SELECTOR_SIZE / 2));
    posCurs.y = this->_input[curs].y - (SECTOR_DEFAULT_SIZE / 2);
    (*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_MENU);

    posCurs.x += SELECTOR_SIZE;
    (*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_MENU);

	(*this->_aGraphics)->display();
}

























