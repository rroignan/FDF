/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 18:14:44 by rroignan          #+#    #+#             */
/*   Updated: 2015/05/20 17:25:13 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 53)
		exit(0);
	return (0);
}

char	***parseur(char ***tab, char *str)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tab[i] = ft_strsplit(line, ' ');
		i++;
	}
	tab[i] = NULL;
	close(fd);
	return (tab);
}

void	ft_draw(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
{

	int		x;
	int		y;

	x = x1;
	y = y1;
	if ((x2 - x1) > (y2 - y1))
	{
		while (x <= x2)
		{
			mlx_pixel_put(mlx, win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1), color);
			x++;
		}
	}
	else
	{
		while (y <= y2)
		{
			mlx_pixel_put(mlx, win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y, color);
			y++;
		}
	}
}

int		main(int ac, char **av)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	***tab;
	t_env	e;

	i = 0;
	j = 0;
	x = 50;
	y = 50;
	if (ac != 2)
		return (0);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1000, 1000, "42");
	if ((tab = (char ***)malloc(sizeof(char **) * 400)) == NULL)
		return (0);
	tab = parseur(tab, av[1]);
	while (tab[i + 1])
	{
		j = 0;
		x = 50;
		while (tab[i][j + 1])
		{
			if (ft_atoi(tab[i][j]) != 0 && ft_atoi(tab[i][j + 1]) != 0)
				ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), (x + 50), y + ft_atoi(tab[i][j + 1]), 0xFF0000);
			else
				ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), (x + 50), y + ft_atoi(tab[i][j + 1]), 0x0000FF);
			if (ft_atoi(tab[i][j]) != 0 && ft_atoi(tab[i + 1][j]) != 0)
				ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), x, (y + 50) + ft_atoi(tab[i + 1][j]), 0xFF0000);
			else
				ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), x, (y + 50) + ft_atoi(tab[i + 1][j]), 0x0000FF);
			j++;
			x += 50;
		}
		ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), x, (y + 50) + ft_atoi(tab[i + 1][j]), 0x0000FF);
		i++;
		y += 50;
	}
	j = 0;
	x = 50;
	while (tab[i][j + 1])
	{
		ft_draw(e.mlx, e.win, x, y + ft_atoi(tab[i][j]), (x + 50), y + ft_atoi(tab[i][j + 1]), 0x0000FF);
		j++;
		x += 50;
	}
	/*while (tab[i][j + 1])
	{
		if (ft_atoi(tab[i][j]) != 0 && ft_atoi(tab[i][j + 1]) != 0)
			ft_draw(e.mlx, e.win, j*50 + 10, i*50, (j + 1) + 10, i*50, 0xFF0000);
		else
			ft_draw(e.mlx, e.win, j*50 + 10, i*50, (j + 1)*50 + 10, i*50, 0x0000FF);
		j++;
	}*/
	mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
