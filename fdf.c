/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 18:14:44 by rroignan          #+#    #+#             */
/*   Updated: 2015/05/30 17:43:47 by rroignan         ###   ########.fr       */
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

char	***parse(char ***tab, char *str)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line))
		i++;
	if ((tab = (char ***)malloc(sizeof(char **) * (i + 1))) == NULL)
		return (0);
	i = 0;
	close(fd);
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

void	ft_drawy(void *mlx, void *win, int x1, int	y1, int x2, int y2, int color)
{
	int		y;

	y = y1;
	while (y < y2)
	{
		mlx_pixel_put(mlx, win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y, color);
		y++;
	}
}

void	ft_drawx(void *mlx, void *win, int x1, int	y1, int x2, int y2, int color)
{
	int		x;

	x = x1;

	while (x < x2)
	{
		mlx_pixel_put(mlx, win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1), color);
		x++;
	}
}

void	ft_draw(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
{
	int		lenx;
	int		leny;

	if (x1 > x2)
		lenx = x1 - x2;
	else
		lenx = x2 - x1;
	if (y1 > y2)
		leny = y1 - y2;
	else
		leny = y2 - y1;
	if (lenx > leny)
	{
		if (x1 > x2)
			ft_drawx(mlx, win, x2, y2, x1, y1, color);
		else
			ft_drawx(mlx, win, x1, y1, x2, y2, color);
	}
	else
	{
		if (y1 > y2)
			ft_drawy(mlx, win, x2, y2, x1, y1, color);
		else
			ft_drawy(mlx, win, x1, y1, x2, y2, color);
	}
	/*if ((x2 - x1) > (y2 - y1))
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
	  }*/
}

int		ft_strlen2(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_show(char ***tab, t_env *e)
{
	size_t	i;
	int		boolie;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	while (tab[i + 1])
	{
		j = 0;
		boolie = 1;
		x = 900 - (i * XSIZE);
		y = 200 + (i * YSIZE);
		while (tab[i][j + 1])
		{
			if ((ft_atoi(tab[i][j]) != 0 || ft_atoi(tab[i][j + 1]) != 0))
				ft_draw(e->mlx, e->win, x, y - (ft_atoi(tab[i][j]) * H), x + XSIZE, y -
						(ft_atoi(tab[i][j + 1]) * H) + YSIZE, 0xFF0000);
			else if (ft_atoi(tab[i][j]) == 0 && ft_atoi(tab[i][j + 1]) == 0)
				ft_draw(e->mlx, e->win, x, y - (ft_atoi(tab[i][j]) * H), x + XSIZE, y -
						(ft_atoi(tab[i][j + 1]) * H) + YSIZE, 0x0000FF);
			if (!tab[i + 1][j])
				boolie = 0;
			if (boolie)
			{
				if (tab[i + 1][j] && (ft_atoi(tab[i][j]) != 0 || ft_atoi(tab[i + 1][j]) != 0))
					ft_draw(e->mlx, e->win, x, y - (ft_atoi(tab[i][j]) * H), x - XSIZE, y -
							(ft_atoi(tab[i + 1][j]) * H) + YSIZE, 0xFF0000);
				else if (tab[i + 1][j] && ft_atoi(tab[i][j]) == 0 && ft_atoi(tab[i + 1][j]) == 0)
				{
					ft_draw(e->mlx, e->win, x, y - ft_atoi(tab[i][j]) * H, x - XSIZE, y -
							ft_atoi(tab[i + 1][j]) * H + YSIZE, 0x0000FF);
				}
			}
			j++;
			y += YSIZE;
			x += XSIZE;
		}
		if (ft_strlen2(tab[i]) <= ft_strlen2(tab[i + 1]))
			ft_draw(e->mlx, e->win, x, y - (ft_atoi(tab[i][j]) * H), x - XSIZE, y -
					ft_atoi(tab[i + 1][j]) * H + YSIZE, 0x0000FF);
		i++;
	}
	x = 900 - (i * XSIZE);
	y = 200 + i * YSIZE;
	j = 0;
	(void)e;
	while (tab[i][j + 1])
	{
		ft_draw(e->mlx, e->win, x, y - (ft_atoi(tab[i][j]) * H), x + XSIZE, y - (ft_atoi(tab[i][j + 1]) * H) + YSIZE, 0x0000FF);
		j++;
		x += XSIZE;
		y += YSIZE;
	}
}

int		main(int ac, char **av)
{
	char	***tab;
	t_env	*e;

	tab = NULL;
	e = malloc(sizeof(t_env));
	ft_bzero(e, sizeof(t_env));
	if (ac != 2)
		return (0);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, 2200, 2200, "42");
	//if ((tab = (char ***)malloc(sizeof(char **) * 400)) == NULL)
	//	return (0);
	tab = parse(tab, av[1]);

	ft_show(tab, e);
	mlx_hook(e->win, KEY_PRESS, KEY_PRESS_MASK, key_hook, &e);
	mlx_loop(e->mlx);
	return (0);
}
