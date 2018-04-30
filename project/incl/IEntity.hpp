/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 17:01:54 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 17:01:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "AGraphics.hpp"

class IEntity {

public:
	typedef struct {
		double x;
		double y;
	}	t_coord;

	t_coord		_pos;
	eTexture	_skin;
};

#endif //NIBBLER_IENTITY_HPP
