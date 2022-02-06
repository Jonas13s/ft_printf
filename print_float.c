/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:00:24 by joivanau          #+#    #+#             */
/*   Updated: 2022/02/05 21:02:53 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_sign(long double number, t_print *tab)
{
	int	count;

	count = 0;
	if (tab->plus && number >= 0)
	{
		count++;
		ft_putchar('+');
	}
	else if (tab->space && number >= 0)
	{
		ft_putchar(' ');
		count++;
	}
	return (count);
}

static int	print_right_allign(long double number, char *string, t_print *tab)
{
	int	count;

	count = ft_strlen(string);
	if (number < 0)
		count++;
	if ((tab->space && number >= 0) || (tab->plus && number >= 0))
		count++;
	if (tab->zero)
	{
		if (number < 0)
			ft_putchar('-');
		ft_print_char('0', tab->width - count);
		print_sign(number, tab);
		ft_putstr(string);
	}
	else
	{
		if (!tab->minus)
			ft_print_char(' ', tab->width - count);
		if (number < 0)
			ft_putchar('-');
		print_sign(number, tab);
		ft_putstr(string);
		if (tab->minus)
			ft_print_char(' ', tab->width - count);
	}
	if (tab->width > count)
		count = tab->width;
	return (count);
}

int	ft_isnan(long double x)
{
	return (x != x);
}

int print_float(t_print *tab, t_length *mod)
{
	long double	number;
	char		*string;
	int			count;

	if (mod->L == 1)
		number = va_arg(tab->args, long double);
	else
		number = va_arg(tab->args, double);
	if(number == -1.0 / 0.0)
		return(write(1, "-inf", 4));
	if (number == 1.0 / 0.0)
		return (write(1, "inf", 3));
	if (ft_isnan(number))
		return (write(1, "-nan", 4));
	if (tab->dot == 0)
	{
		tab->dot = 1;
		tab->precision = 6;
	}
	string = ftoa(number, tab);
	count = print_right_allign(number, string, tab);
	ft_strdel(&string);
	return (count);
}