/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphics.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:37:21 by cchameyr          #+#    #+#             */
/*   Updated: 2018/05/18 16:37:21 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/AGraphics.hpp"

std::vector<eEvent> AGraphics::_eventList;

void AGraphics::addEvent(eEvent event) {
	AGraphics::_eventList.push_back(event);
}

void AGraphics::clearEvent() {
	AGraphics::_eventList.clear();
}

int AGraphics::centerTextX(std::string str, float size, int w) {
	int rest = 0;
	if (size <= 0) {
		size = 1;
	}
	if (str.length() % 2)
		rest = static_cast<int>(GET_SIZEFONT_X(size) / 2);
	return ((w / 2) - static_cast<int>(((str.length() / 2) * GET_SIZEFONT_X(size)) + rest));
}