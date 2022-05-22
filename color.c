/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:03:38 by joivanau          #+#    #+#             */
/*   Updated: 2022/05/23 00:22:58 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	change_color(const char *format)
{
	int	i;

	i = 0;
	while (format[i] != '}')
		i++;
	if (ft_memcmp(format, "{cyan}", 6) == 0)
		write(1, CYAN, ft_strlen(CYAN));
	if (ft_memcmp(format, "{eoc}", 5) == 0)
		write(1, EOC, ft_strlen(EOC));
	if (ft_memcmp(format, "{red}", 5) == 0)
		write(1, RED, ft_strlen(RED));
	if (ft_memcmp(format, "{black}", 7) == 0)
		write(1, BLACK, ft_strlen(BLACK));
	if (ft_memcmp(format, "{green}", 7) == 0)
		write(1, GREEN, ft_strlen(GREEN));
	if (ft_memcmp(format, "{yellow}", 8) == 0)
		write(1, YELLOW, ft_strlen(YELLOW));
	if (ft_memcmp(format, "{blue}", 6) == 0)
		write(1, BLUE, ft_strlen(BLUE));
	if (ft_memcmp(format, "{purple}", 8) == 0)
		write(1, PURPLE, ft_strlen(PURPLE));
	if (ft_memcmp(format, "{white}", 7) == 0)
		write(1, WHITE, ft_strlen(WHITE));
	return (i + 1);
}

int	is_color(const char *format)
{
	if (ft_memcmp(format, "{cyan}", 6) == 0)
		return (1);
	if (ft_memcmp(format, "{eoc}", 5) == 0)
		return (1);
	if (ft_memcmp(format, "{red}", 5) == 0)
		return (1);
	if (ft_memcmp(format, "{black}", 7) == 0)
		return (1);
	if (ft_memcmp(format, "{green}", 7) == 0)
		return (1);
	if (ft_memcmp(format, "{yellow}", 8) == 0)
		return (1);
	if (ft_memcmp(format, "{blue}", 6) == 0)
		return (1);
	if (ft_memcmp(format, "{purple}", 8) == 0)
		return (1);
	if (ft_memcmp(format, "{white}", 7) == 0)
		return (1);
	return (0);
}
