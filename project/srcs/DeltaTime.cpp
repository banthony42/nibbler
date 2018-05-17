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
double DeltaTime::maxFps = -1;
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

void DeltaTime::setMaxFps(int maxFps) {
	if (maxFps > 0) {
		DeltaTime::maxFps = maxFps;
	}
}

// SDL = it works
// SFML = it works with some 100 fps drop very very quick
// OPENGL = it doesn't change anything and the fps is still up to 60
void DeltaTime::limitFps() {
	static double limitFps = 0;
	static int count = 0;
	static useconds_t latency = 0;

	if (DeltaTime::maxFps > 0) {
		limitFps = DeltaTime::elapsedTime * maxFps;
		if (limitFps < 1000 && count == 0) {
			latency = static_cast<useconds_t>(((1000 - limitFps) * 1000) / maxFps);
			count = static_cast<int>(maxFps);
		} else if (count) {
			usleep(latency);
			if (count-- == 0) {
				count = 0;
				limitFps = 0;
			}
		}
	}
}


void DeltaTime::startDelta() {
	gettimeofday(&DeltaTime::t1, NULL);
}

void DeltaTime::endDelta() {
	gettimeofday(&DeltaTime::t2, NULL);
	DeltaTime::elapsedTime = (DeltaTime::t2.tv_sec - DeltaTime::t1.tv_sec) * 1000;
	DeltaTime::elapsedTime += (DeltaTime::t2.tv_usec - DeltaTime::t1.tv_usec) / 1000;
	DeltaTime::deltaTime = DeltaTime::elapsedTime / 1000;
	DeltaTime::fps = 1 / DeltaTime::deltaTime;
}