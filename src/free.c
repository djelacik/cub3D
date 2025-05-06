/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:15:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/24 15:16:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_and_exit(void)
{
	gc_free_all();
	exit(EXIT_FAILURE);
}

void	free_and_exit_with(int exit_code)
{
	gc_free_all();
	exit(exit_code);
}

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	gc_free_all();
	exit(EXIT_FAILURE);
}