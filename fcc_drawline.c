/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcc_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:01:00 by mbutt             #+#    #+#             */
/*   Updated: 2019/08/05 11:47:45 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

/*
** ft_swap, swaps values of a and b
*/

int ft_swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return(0);
}

/*
** ft_abs performs the same function as abs(3) function found in stdlib.h
** Converts a value into an absolute value, so a negative values becomes
** positive.
** Return Value: Returns a postive value.
*/

int ft_abs(int num)
{
	if(num < 0)
		num = -1 * num;
	return(num);
}

void calculate_delta_xy(t_mlx *mlx)
{
	mlx->dx = mlx->x1 - mlx->x0;
	mlx->dy = mlx->y1 - mlx->y0;
}

void plot_low_line(t_mlx *mlx)
{
	size_t hue;

	hue = mlx->color;
	calculate_delta_xy(mlx);
	mlx->yi = 1;
	if(mlx->dy < 0)
	{
		mlx->yi = -1;
		mlx->dy = -1 * mlx->dy;
	}
	mlx->delta_error = (2 * mlx->dy) - mlx->dx;
	while(mlx->x0 < mlx->x1)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->x0, mlx->y0, mlx->color);
//		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->x0, mlx->y0, ft_hue(mlx->y0, hue));
		if(mlx->delta_error > 0)
		{
			mlx->y0 = mlx->y0 + mlx->yi;
			mlx->delta_error = mlx->delta_error - (2 * mlx->dx);
		}
		mlx->delta_error = mlx->delta_error + (2 * mlx->dy);
		mlx->x0++;
	}
}

void plot_high_line(t_mlx *mlx)
{
	size_t hue;

	hue = mlx->color;
	calculate_delta_xy(mlx);
	mlx->xi = 1;
	if(mlx->dx < 0)
	{
		mlx->xi = -1;
		mlx->dx = -1 * mlx->dx;
	}
	mlx->delta_error = (2 * mlx->dx) - mlx->dy;
	while(mlx->y0 < mlx->y1)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->x0, mlx->y0, mlx->color);
//		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->x0, mlx->y0, ft_hue(mlx->y0, hue));
		if(mlx->delta_error > 0)
		{
			mlx->x0 = mlx->x0 + mlx->xi;
			mlx->delta_error = mlx->delta_error - (2 * mlx->dy);
		}
		mlx->delta_error = mlx->delta_error + (2 * mlx->dx);
		mlx->y0++;
	}
}

void plot_any_line(t_mlx *mlx)
{
	if(ft_abs(mlx->y1 - mlx->y0) < ft_abs(mlx->x1 - mlx->x0))
	{
		if(mlx->x0 > mlx->x1)
		{
			ft_swap(&mlx->x0, &mlx->x1);
			ft_swap(&mlx->y0, &mlx->y1);
			plot_low_line(mlx);
		}
		else
			plot_low_line(mlx);
	}
	else
	{
		if(mlx->y0 > mlx->y1)
		{
			ft_swap(&mlx->x0, &mlx->x1);
			ft_swap(&mlx->y0, &mlx->y1);
			plot_high_line(mlx);
		}
		else
			plot_high_line(mlx);
	}
}

void ft_menu(t_mlx *mlx)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	char *str5;
	char *str6;
	char *str7;

	str1 = "Menu Controls";
	str2 = "Shift: Arrow Keys: < ^ v >";
	str3 = "Rotate: I J K L";
	str4 = "Zoom: Q A";
	str5 = "Altitude: W S";
	str6 = "Reset map: E";
	str7 = "Random Colors: R";

	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0xffffff, str1);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, 0xadadad, str2);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, 0xadadad, str3);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 80, 0xadadad, str4);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 100, 0xadadad, str5);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 120, 0xadadad, str6);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 140, 0xadadad, str7);

}


void ft_render_vertical(t_mlx *mlx, t_mlx *temp)
{
	mlx->x0 = mlx->x;
	mlx->y0 = mlx->y;

	rotate_vertical_line(mlx, temp);
	if(mlx->y < temp->map_height)
		plot_any_line(mlx);
}

void ft_render_horizontal(t_mlx *mlx, t_mlx *temp)
{
	mlx->x0 = mlx->x;
	mlx->y0 = mlx->y;

	rotate_horizontal_line(mlx, temp);
	if(mlx->x < temp->map_width)
		plot_any_line(mlx);
}

/*
** ft_render_horizontal_vertical calls onto ft_render_horizontal and
** ft_render_vertical to render lines. Not including the second if statement
** would produce lines as shown below:
**  _ _ _ _ _ _ _
** |_|_|_|_|_|_|_
** |_|_|_|_|_|_|_
** | | | | | | |
** 
** But that is fixed when the second if statement if(mlx->y < temp->map_height)
** is included, which places the vertical line as long as y is less than height
** the map. Below is how the map will render now:
**  _ _ _ _ _ _ _
** |_|_|_|_|_|_|_|
** |_|_|_|_|_|_|_|
** |_|_|_|_|_|_|_|
*/

void	ft_render_vertical_horizontal(t_mlx *mlx, t_mlx *temp)
{
	if(mlx->camera == 0 || mlx->camera == 1)
	{
		if(mlx->y < temp->map_height)	
			ft_render_vertical(mlx, temp);
		ft_render_horizontal(mlx, temp);
	}
}

void struct_copy(t_mlx *source, t_mlx *dest)
{
	dest->map_height = source->map_height;
	dest->map_width = source->map_width;
	dest->map_height--;
	dest->map_width--;
	dest->x0 = source->x0;
	dest->y0 = source->y0;
	dest->x1 = source->x1;
	dest->y1 = source->y1;
}

void get_struct_values(t_mlx *mlx)
{
	t_mlx temp;
	size_t hue;
	mlx->size = 15;
	mlx->x = 0;
	mlx->y = 0;
	mlx->x0 = 0;
	mlx->y0 = 0;
	mlx->camera = 0;
	mlx->x_shift = 0;
	mlx->y_shift = 0;
//	mlx->x0 = (P_WIDTH / 2); //- (P_WIDTH/160 * mlx->map_width);   //Works - Put it back on after
//	mlx->y0 = (P_HEIGHT / 2);// - (P_HEIGHT/95 * mlx->map_height); //Works - Put it back on after
	mlx->x1 = mlx->x0;
	mlx->y1 = mlx->y0;
	mlx->camera = 0;
//	mlx->angle_y = 0.5;
//	mlx->angle_z = 0.25;
	mlx->degree_angle = 30;
	mlx->xy_zoom = 0.5;
	mlx->z_zoom = 0.03;
	mlx->x_axis = 0;
	mlx->y_axis = 0;
	mlx->z_axis = 0;
	mlx->color = 0xff000;
}

/*
** reset_y0y1 is used in ft_render to reset values for y0, and y1. Because
** y0 and y1 get changed in the while loop. It is important to reset y0 and y1
** back to their original values if we want to integrate keyboard into the
** program allowing us to shift the program in any direction and change zoom.
*/

void reset_x0x1_y0y1(t_mlx *mlx, t_mlx *temp_reset)
{
	mlx->x0 = temp_reset->x0;
	mlx->x1 = temp_reset->x1;
	mlx->x = 0;
	mlx->y0 = temp_reset->y0;
	mlx->y1 = temp_reset->y1;
	mlx->y = 0;
}

void ft_render(t_mlx *mlx)
{
	t_mlx temp;
	t_mlx temp_reset;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	ft_print_data(mlx);
	ft_menu(mlx);
	struct_copy(mlx, &temp);
	copy_mlx_x0y0x1y1_to_temp_x0y0x1y1(mlx, &temp_reset);
	while(mlx->y <= temp.map_height)
	{
		while(mlx->x <= temp.map_width)
		{
			ft_render_vertical_horizontal(mlx, &temp);
			mlx->x++;
		}
		mlx->x = 0;
		mlx->y++;
	}
	reset_x0x1_y0y1(mlx, &temp_reset);
}

/*
** ft_print_data prints the data that is stored in t_mlx struct inside int_data.
*/
void ft_print_data(t_mlx *mlx)
{
	int i;
	int j;
	int width;
	int height;

	i = 0;
	j = 0;
	width = mlx->map_width;
	height = mlx->map_height;
	while(height)
	{
		while(j < width)
		{
			ft_putnbr(mlx->int_data[i][j]);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
		j = 0;
		i++;
		height--;
	}
}

