/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:59 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneMenu.hpp"

SceneMenu::SceneMenu() {

}

SceneMenu::SceneMenu(SceneMenu const &copy) {
	*this = copy;
}

SceneMenu::~SceneMenu() {

}

SceneMenu::SceneMenu(AGraphics *aGraphics) {
	this->_aGraphics = aGraphics;
}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
	for (size_t j = 0; j < eventList.size(); j++) {
		if (eventList.at(j) == ECHAP) {
			Nibbler::_aGraphics->closeWindow();
		}
	}
}


void SceneMenu::drawScene() {
	this->_aGraphics->clear();

	// Preview des Scenes
	// Déso j'avais plus trop le temps les positions sont hard codé parfois, pour un ecran de 1200 x 900

	// MENU preview
	this->_aGraphics->putTexture(MENU_BCKG, 0, 0, Nibbler::WINDOW_WIDTH / 2, Nibbler::WINDOW_HEIGHT / 2);
	this->_aGraphics->putStrScreen("< Game >", (Nibbler::WINDOW_WIDTH / 4) - (4 * 32), 150, 2);
	this->_aGraphics->putStrScreen("Options", (Nibbler::WINDOW_WIDTH / 4) - (3 * 32), 200, 2);
	this->_aGraphics->putStrScreen("Exit", (Nibbler::WINDOW_WIDTH / 4) - (2 * 32), 250, 2);

	// GAME preview
	this->_aGraphics->putTexture(GAME_BCKG, (Nibbler::WINDOW_WIDTH / 2) + 25, 25, (Nibbler::WINDOW_WIDTH / 2) - 50, (Nibbler::WINDOW_HEIGHT / 2) - 50);
	this->_aGraphics->putTexture(GAME_BORDER, Nibbler::WINDOW_WIDTH / 2, 0, Nibbler::WINDOW_WIDTH / 2, Nibbler::WINDOW_HEIGHT / 2);
	this->_aGraphics->putTexture(SNAKE_H_SMB, 850, 200, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 850 - 24, 200, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 850 - 48, 200, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 850 - 72, 200, 24, 24);
	this->_aGraphics->putTexture(FOOD, 900, 200, 24, 24);

	// SKIN selection preview
	this->_aGraphics->putTexture(SKIN_FRAME, 0, Nibbler::WINDOW_HEIGHT / 2, Nibbler::WINDOW_WIDTH / 2, Nibbler::WINDOW_HEIGHT / 2);
	this->_aGraphics->putStrScreen("<               >", 330 - (8 * 32), 490, 2);
	this->_aGraphics->putTexture(SNAKE_H_SMB, 330, 500, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 330 - 24, 500, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 330 - 48, 500, 24, 24);
	this->_aGraphics->putTexture(SNAKE_B_SMB, 330 - 72, 500, 24, 24);

	// GAME END preview
	this->_aGraphics->putTexture(SCORE_BCKG, Nibbler::WINDOW_WIDTH / 2, Nibbler::WINDOW_HEIGHT / 2, Nibbler::WINDOW_WIDTH / 2, Nibbler::WINDOW_HEIGHT / 2);
	this->_aGraphics->putStrScreen("GAME OVER", (900) - (4 * 32), 550, 2);
	this->_aGraphics->putStrScreen("Score: 1542", (900) - (5 * 32), 600, 2);
	this->_aGraphics->putStrScreen("< Replay >", (900) - (5 * 32), 700, 2);
	this->_aGraphics->putStrScreen("Menu", (900) - (3 * 32), 750, 2);

	// GAME Fullscreen preview, dé-commenté pour un apercu du jeu sur tout l'ecran
//	this->_aGraphics->clear();
//	this->_aGraphics->putTexture(GAME_BCKG, 50, 50, Nibbler::WINDOW_WIDTH - 100, Nibbler::WINDOW_HEIGHT - 100);
//	this->_aGraphics->putTexture(BORDER, 0, 0, Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT);

	this->_aGraphics->display();
}




















