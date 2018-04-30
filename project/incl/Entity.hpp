/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 17:12:12 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 17:12:12 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

//	TODO Clem ok? Un fichier pour chaque Entity car elles s'apparentent à des structures

class Snake : public IEntity {
public:
	t_coord		_tailPos;
	t_coord		_vec;		//	TODO Clem ok? utilisation de la struct t_coord pour vecteur direction
	int 		_size;
};

class Food : public IEntity {
public:
	t_coord		_vec;		// TODO pas utile pour les entity food je crois (pas de mouvements)
	int 		_energy;	// TODO définir l'utilité
};

#endif //NIBBLER_ENTITY_HPP
