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

SceneSkin::SceneSkin(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}

void SceneSkin::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneSkin::drawScene() {

}

