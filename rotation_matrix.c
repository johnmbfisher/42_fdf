/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:55:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/08/05 11:00:18 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_min(t_mlx *mlx)
{
	int height;
	int width;

	height = P_HEIGHT / mlx->map_height;
	width = P_WIDTH / mlx->map_width;

	if(height < width)
		return(height);
	else if(width <= height)
		return(width);
	return(0);
}

double degree_to_radian(double degrees)
{
	double radian;

	radian = degrees * (M_PI/180);
	return(radian);
}


void rotation_matrix(t_mlx *mlx, int *x, int *y, int z)
{
	int temp_x;
	int temp_y;
	double radian;

	
	temp_x = *x;
	temp_y = *y;
	if(mlx->camera == 0)
		mlx->degree_angle = 30;
	else if(mlx->camera == 1)
		mlx->degree_angle = 15;
	radian = degree_to_radian(mlx->degree_angle);
	*x = (temp_x - temp_y) * cos(radian);
	*y = -z + (temp_x + temp_y) * sin(radian);

}

void	copy_mlx_x0y0x1y1_to_temp_x0y0x1y1(t_mlx *mlx, t_mlx *temp)
{
	temp->x0 = mlx->x0;
	temp->x1 = mlx->x1;
	temp->y0 = mlx->y0;
	temp->y1 = mlx->y1;
}

void rotate_vertical_line(t_mlx *mlx, t_mlx *temp)
{
	int min;

	min = ft_min(mlx);
	if(mlx->y < temp->map_height)
	{
	mlx->z0 = mlx->int_data[mlx->y][mlx->x] * mlx->z_zoom * min; // Added z value
	mlx->z1 = mlx->int_data[mlx->y + 1][mlx->x] * mlx->z_zoom * min; // Added z value
	}
	mlx->x1 = mlx->x0;
	mlx->y1 = mlx->y0 + 1;


	mlx->x0 = mlx->x0 * mlx->xy_zoom * min;
	mlx->x1 = mlx->x1 * mlx->xy_zoom * min;
	mlx->y0 = mlx->y0 * mlx->xy_zoom * min;
	mlx->y1 = mlx->y1 * mlx->xy_zoom * min;

	
	rotate_x_axis(mlx, &mlx->y0, &mlx->z0, mlx->x_axis);
	rotate_x_axis(mlx, &mlx->y1, &mlx->z1, mlx->x_axis);
	rotate_y_axis(mlx, &mlx->x0, &mlx->y0, mlx->y_axis);
	rotate_y_axis(mlx, &mlx->x1, &mlx->y1, mlx->y_axis);
	rotate_z_axis(mlx, &mlx->x0, &mlx->y0, mlx->z_axis);
	rotate_z_axis(mlx, &mlx->x1, &mlx->y1, mlx->z_axis);



	rotation_matrix(mlx, &mlx->x0, &mlx->y0, mlx->z0);
	rotation_matrix(mlx, &mlx->x1, &mlx->y1, mlx->z1);

	mlx->x0 = mlx->x0 + mlx->x_shift + (P_WIDTH/2.5);
	mlx->x1 = mlx->x1 + mlx->x_shift + (P_WIDTH/2.5);
	mlx->y0 = mlx->y0 + mlx->y_shift + (P_HEIGHT/4);
	mlx->y1 = mlx->y1 + mlx->y_shift + (P_HEIGHT/4);
}

void rotate_horizontal_line(t_mlx *mlx, t_mlx *temp)
{
	int min;
	
	min = ft_min(mlx);
	if(mlx->x < temp->map_width)
	{
	mlx->z0 = mlx->int_data[mlx->y][mlx->x] * mlx->z_zoom * min;   //Added z value 
	mlx->z1 = mlx->int_data[mlx->y][mlx->x + 1] * mlx->z_zoom * min; //Added z value
	}
	mlx->x1 = mlx->x0 + 1;
	mlx->y1 = mlx->y0;

	mlx->x0 = mlx->x0 * mlx->xy_zoom * min;
	mlx->x1 = mlx->x1 * mlx->xy_zoom * min;
	mlx->y0 = mlx->y0 * mlx->xy_zoom * min;
	mlx->y1 = mlx->y1 * mlx->xy_zoom * min;
	

	rotate_x_axis(mlx, &mlx->y0, &mlx->z0, mlx->x_axis);
	rotate_x_axis(mlx, &mlx->y1, &mlx->z1, mlx->x_axis);
	rotate_y_axis(mlx, &mlx->x0, &mlx->y0, mlx->y_axis);
	rotate_y_axis(mlx, &mlx->x1, &mlx->y1, mlx->y_axis);
	rotate_z_axis(mlx, &mlx->x0, &mlx->y0, mlx->z_axis);
	rotate_z_axis(mlx, &mlx->x1, &mlx->y1, mlx->z_axis);


	rotation_matrix(mlx, &mlx->x0, &mlx->y0, mlx->z0);
	rotation_matrix(mlx, &mlx->x1, &mlx->y1, mlx->z1);

	mlx->x0 = mlx->x0 + mlx->x_shift + (P_WIDTH/2.5);
	mlx->x1 = mlx->x1 + mlx->x_shift + (P_WIDTH/2.5);
	mlx->y0 = mlx->y0 + mlx->y_shift + (P_HEIGHT/4);
	mlx->y1 = mlx->y1 + mlx->y_shift + (P_HEIGHT/4);
}


void rotate_x_axis(t_mlx *mlx, int *y, int *z, double x_axis)
{
	int temp_y;
	int temp_z;

	temp_y = (*y * cos(x_axis)) - (*z * sin(x_axis));
	temp_z = (*y * sin(x_axis)) + (*z * cos(x_axis));

	*y = temp_y;
	*z = temp_z;
}

void rotate_y_axis(t_mlx *mlx, int *x, int *z, double y_axis)
{
	int temp_x;
	int temp_z;

	temp_x = (*x * cos(y_axis)) - (*z * sin(y_axis));
	temp_z = (*x * sin(y_axis)) + (*z * cos(y_axis));

	*x = temp_x;
	*z = temp_z;
}

void rotate_z_axis( t_mlx *mlx, int *x, int *y, double z_axis)
{
	int temp_x;
	int temp_y;

	temp_x = (*x * cos(z_axis)) - (*y * sin(z_axis));
	temp_y = (*x * sin(z_axis)) + (*y * cos(z_axis));

	*x = temp_x;
	*y = temp_y;
}
