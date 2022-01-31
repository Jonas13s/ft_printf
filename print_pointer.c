/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:54:47 by joivanau          #+#    #+#             */
/*   Updated: 2022/01/31 14:13:02 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	content_size(t_print *tab, char *s)
{
	int	len;
	int	k;

	len = ft_strlen(s);
	if (tab->null)
	{
		tab->content_size = len;
		tab->precision = 0;
		return (len);
	}
	k = 2;
	if (tab->precision > len)
		k += tab->precision;
	else
		k += len;
	if (tab->plus || tab->space)
		k++;
	tab->content_size = k;
	return (len);
}

static int	print_start(t_print *tab)
{
	if (tab->null)
		return (0);
	if (tab->plus)
		write(1, "+", 1);
	else if (tab->space)
		write(1, " ", 1);
	write(1, "0x", 2);
	return (0);
}

static int	printing_hex(char *s, t_print *tab)
{
	ssize_t	k;

	k = 0;
	if (tab->null)
	{
		write(1, s, ft_strlen(s));
		return (ft_strlen(s));
	}
	while (s[k] != '\0')
	{
		ft_putchar(s[k]);
		k++;
	}
	return (k);
}

static int	printf_right_allign(t_print *tab, char *s)
{
	int	len;

	len = content_size(tab, s);
	ft_print_char(' ', tab->width - tab->content_size);
	print_start(tab);
	ft_print_char('0', tab->precision - len);
	printing_hex(s, tab);
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (0);
}

static int	printf_left_allign(t_print *tab, char *s)
{
	int	len;

	len = content_size(tab, s);
	print_start(tab);
	ft_print_char('0', tab->precision - len);
	printing_hex(s, tab);
	ft_print_char(' ', tab->width - tab->content_size);
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (0);
}

int	print_pointer(t_print *tab)
{
	unsigned long long	p;
	char				*s;

	p = va_arg(tab->args, unsigned long long);
	if (p == 0)
	{
		s = ft_strdup("(nil)");
		tab->null = 1;
	}
	else
		s = hex_conv(p, HEXALOW);
	if (tab->minus)
		printf_left_allign(tab, s);
	else
		printf_right_allign(tab, s);
	return (tab->content_size);
}
