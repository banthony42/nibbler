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
	this->aGraphics = aGraphics;
}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
	(void) eventList;
}

void SceneMenu::drawScene() {

}
