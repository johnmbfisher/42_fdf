/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcc_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:01:00 by mbutt             #+#    #+#             */
/*   Updated: 2019/08/05 19:06:40 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	ft_menu1(t_mlx *mlx)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;

	str1 = "Menu Controls";
	str2 = "Shift: Arrow Keys: < ^ v >";
	str3 = "Rotate: I J K L";
	str4 = "Zoom: Q A";
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0xffffff, str1);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, 0xadadad, str2);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, 0xadadad, str3);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 80, 0xadadad, str4);
}

void	ft_menu2(t_mlx *mlx)
{
	char *str5;
	char *str6;
	char *str7;

	str5 = "Altitude: W S";
	str6 = "Reset map: E";
	str7 = "Random Colors: R";
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 100, 0xadadad, str5);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 120, 0xadadad, str6);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 140, 0xadadad, str7);
}

void	ft_menu(t_mlx *mlx)
{
	ft_menu1(mlx);
	ft_menu2(mlx);
}
