/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 17:31:02 by rroignan          #+#    #+#             */
/*   Updated: 2015/05/14 19:53:05 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# define KEY_PRESS	2
# define KEY_PRESS_MASK	(1L << 0)
typedef struct	s_env
{
	void	*mlx;
	void	*win;
}				t_env;

#endif
