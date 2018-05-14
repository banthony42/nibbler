/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeltaTime.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:07:04 by cchameyr          #+#    #+#             */
/*   Updated: 2018/05/14 14:07:04 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_DELTATIME_HPP
#define PROJECT_DELTATIME_HPP

#include <sys/time.h>

class DeltaTime {

public:
	static double deltaTime;
	static int fps;

	static void startDelta();
	static void endDelta();

private:
	DeltaTime(); // Canonical
	DeltaTime(DeltaTime const &copy); // Canonical
	~DeltaTime(); // Canonical
	DeltaTime &operator=(DeltaTime const &copy); // Canonical

	static double elapsedTime;
	static struct timeval t1;
	static struct timeval t2;

};


#endif //PROJECT_DELTATIME_HPP