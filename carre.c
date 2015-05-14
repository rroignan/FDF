/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 16:00:29 by rroignan          #+#    #+#             */
/*   Updated: 2015/05/14 19:52:58 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(void *mlx, void *win)
{
	int		x;
	int		y;
	
	y = 100;
	while (y != 200)
	{
		x = 100;
		while (x < 200)
		{
			mlx_pixel_put(mlx, win, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

int		key_hook(int keycode, t_env *e)
{
	(void)e;
	printf("key: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	e;

	e.mlx = mlx_init();
	(void)ac;
	(void)av;
	e.win = mlx_new_window(e.mlx, 500, 500, "42");
	draw(e.mlx, e.win);
	mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
