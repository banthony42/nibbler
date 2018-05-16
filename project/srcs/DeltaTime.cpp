/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeltaTime.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:05:28 by cchameyr          #+#    #+#             */
/*   Updated: 2018/05/14 14:05:28 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/DeltaTime.hpp"

double DeltaTime::deltaTime = 1;
double DeltaTime::elapsedTime = 0;
int DeltaTime::fps = 0;
struct timeval DeltaTime::t1 = {0};
struct timeval DeltaTime::t2 = {0};

DeltaTime::DeltaTime() {

}

DeltaTime::DeltaTime(DeltaTime const &copy) {
	*this = copy;
}

DeltaTime::~DeltaTime() {

}

DeltaTime &DeltaTime::operator=(DeltaTime const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void DeltaTime::startDelta() {
	gettimeofday(&DeltaTime::t1, NULL);
}

void DeltaTime::endDelta() {
	gettimeofday(&DeltaTime::t2, NULL);
	DeltaTime::elapsedTime = (DeltaTime::t2.tv_sec - DeltaTime::t1.tv_sec) * 1000;
	DeltaTime::elapsedTime += (DeltaTime::t2.tv_usec - DeltaTime::t1.tv_usec) / 1000;
	DeltaTime::deltaTime = DeltaTime::elapsedTime / 1000;
	double calculatedFps = 1 / DeltaTime::deltaTime;
	if (calculatedFps < DeltaTime::fps + 500 && calculatedFps > DeltaTime::fps - 500) {
		DeltaTime::fps = 1 / DeltaTime::deltaTime;
	}
}