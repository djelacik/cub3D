/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:00:08 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/09 21:00:10 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	simple_shading(uint32_t color, double distance)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	double		factor;

	factor = 1 / (1 + distance * 0.2);
	if (factor < 0.2)
		factor = 0.2;

	r = (uint8_t)(get_r(color) * factor);
	g = (uint8_t)(get_g(color) * factor);
	b = (uint8_t)(get_b(color) * factor);

	return (get_rgba(r, g, b, 0xFF));
}
