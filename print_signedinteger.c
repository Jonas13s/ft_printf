/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signedinteger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:23:41 by joivanau          #+#    #+#             */
/*   Updated: 2022/02/06 03:00:37 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_sign(t_print *tab,long long i)
{
	if (i < 0)
		ft_putchar('-');
	else if (tab->plus)
		ft_putchar('+');
	else if (tab->space)
		ft_putchar(' ');
	return (0);
}

static int	print_digits(t_print *tab, long long i)
{
	char *s;

	if(i < 0)
		i *= -1;
	if (tab->dot == 1 && tab->precision == 0 && i == 0)
		return (0);
	else
	{
		s = hex_conv(i, DIGITS);
		ft_putstr(s);
		ft_strdel(&s);
	}
	return (0);
}

static int	print_left_allign(t_print *tab,long long i)
{
	int	k;

	if (tab->precision > number_count(i))
		k = tab->precision;
	else
		k = number_count(i);
	if (i < 0 || tab->space || tab->plus)
		k++;
	if (tab->dot == 1 && tab->precision == 0 && i == 0)
		k = 0;
	if (tab->zero)
	{
		print_sign(tab, i);
		ft_print_char('0', tab->precision - number_count(i));
		ft_print_char('0', tab->width - k);
		print_digits(tab, i);
	}
	else
	{
		print_sign(tab, i);
		ft_print_char('0', (tab->precision - number_count(i)));
		print_digits(tab, i);
		ft_print_char(' ', tab->width - k);
	}
	if (tab->width > k)
		k = tab->width;
	return (k);
}

static int	print_right_allign(t_print *tab,long long i)
{
	int	k;

	if (tab->precision > number_count(i))
		k = tab->precision;
	else
		k = number_count(i);
	if (i < 0 || tab->space || tab->plus)
		k++;
	if (tab->dot == 1 && tab->precision == 0 && i == 0)
		k = 0;
	if (tab->zero)
	{
		print_sign(tab, i);
		ft_print_char('0', tab->precision - number_count(i));
		ft_print_char('0', tab->width - k);
		print_digits(tab, i);
	}
	else
	{
		ft_print_char(' ', tab->width - k);
		print_sign(tab, i);
		ft_print_char('0', (tab->precision - number_count(i)));
		print_digits(tab, i);
	}
	if (tab->width > k)
		k = tab->width;
	return (k);
}

static long long	print_read(t_print *tab, t_length *mod)
{
	long long k;

	if (mod->h == 1)
		k = (short int)va_arg(tab->args, int);
	else if (mod->h == 2)
		k = (signed char)va_arg(tab->args, int);
	else if (mod->l == 1)
		k = (long int)va_arg(tab->args, long);
	else if (mod->l == 2)
		k = (long long int)va_arg(tab->args, long long);
	else
		k = va_arg(tab->args, int);
	return (k);
}


int	print_signedint(t_print *tab, t_length *mod)
{
	unsigned long long	i;
	int			count;

	i = print_read(tab, mod);
	if ((tab->dot && tab->zero) || (tab->zero && tab->minus))
		tab->zero = 0;
	if (tab->minus)
		count = print_left_allign(tab, i);
	else
		count = print_right_allign(tab, i);
	return (count);
}
