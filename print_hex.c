/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:53:12 by joivanau          #+#    #+#             */
/*   Updated: 2022/01/31 14:10:32 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printing_hex(char *s, t_print *tab)
{
	ssize_t	k;

	if (tab->dot == 1 && tab->precision == 0 && tab->null)
		return (0);
	k = 0;
	while(s[k] != '\0')
	{
		ft_putchar(s[k]);
		k++;
	}

	return (0);
}

static int	print_start(t_print *tab, int mode)
{
	if (tab->hash && mode == 1 && tab->null == 0)
		ft_putstr("0x");
	if (tab->hash && mode == 0 && tab->null == 0)
		ft_putstr("0X");
	return (0);
}

static int	int_content_size(t_print *tab, char *s)
{
	int	k;
	int	length;

	length = ft_strlen(s);
	k = 0;
	if (tab->precision > length)
		k = tab->precision;
	else
		k = length;
	if (tab->hash && tab->null == 0)
		k += 2;
	if (tab->dot == 1 && tab->precision == 0 && tab->null)
		k = 0;
	tab->content_size = k;
	return (length);
}

static int	print_left_allign(t_print *tab, char *s, int mode)
{
	int	length;

	length = int_content_size(tab, s);
	if (tab->zero)
	{
		print_start(tab, mode);
		ft_print_char('0', tab->precision - length);
		ft_print_char('0', tab->width - tab->content_size);
		printing_hex(s, tab);
	}
	else
	{
		print_start(tab, mode);
		ft_print_char('0', tab->precision - length);
		printing_hex(s, tab);
		ft_print_char(' ', tab->width - tab->content_size);
	}
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (tab->content_size);
}

static int	print_right_allign(t_print *tab, char *s, int mode)
{
	int	length;

	length = int_content_size(tab, s);
	if (tab->zero)
	{
		print_start(tab, mode);
		ft_print_char('0', tab->precision - length);
		ft_print_char('0', tab->width - tab->content_size);
		printing_hex(s, tab);
	}
	else
	{
		ft_print_char(' ', tab->width - tab->content_size);
		print_start(tab, mode);
		ft_print_char('0', tab->precision - length);
		printing_hex(s, tab);
	}
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (tab->content_size);
}

static long long	hex_read(t_print *tab, t_length *mod)
{
	long long k;

	if (mod->h == 1)
		k = va_arg(tab->args, int);
	else if (mod->h == 2)
		k = va_arg(tab->args, int);
	else if (mod->l == 1)
		k = va_arg(tab->args, long);
	else if (mod->l == 2)
		k = va_arg(tab->args, long long);
	else
		k = va_arg(tab->args, unsigned int);
	return (k);
}

int	print_hex(t_print *tab, char *base, t_length *mod)
{
	int				count;
	long long		k;
	char			*string;
	int				mode;

	if (ft_strcmp(base, "0123456789ABCDEF") == 0)
		mode = 0;
	else
		mode = 1;
	k = hex_read(tab, mod);
	if ((tab->dot && tab->zero) || (tab->zero && tab->minus))
		tab->zero = 0;
	if (k != 0)
		string = hex_conv(k, base);
	else
	{
		tab->null = 1;
		string = ft_strdup("0");
	}
	if (tab->minus)
		count = print_left_allign(tab, string, mode);
	else
		count = print_right_allign(tab, string, mode);
	ft_strdel(&string);
	return (count);
}
