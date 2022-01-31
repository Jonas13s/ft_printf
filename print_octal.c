/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:10:56 by joivanau          #+#    #+#             */
/*   Updated: 2022/01/31 14:11:52 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int content_size(t_print *tab, char *s)
{
	int	len;
	int	k;
	
	len = ft_strlen(s);
	if (tab->precision > len)
		k = tab->precision;
	else
		k = len;
	if(tab->hash && tab->precision <= len && !tab->null)
	{
		tab->precision = len + 1;
		k++;
	}
	tab->content_size = k;
	return (len);
}

static int	printing_octal(char *s)
{
	ssize_t k;

	k = 0;
	while (s[k] != '\0')
	{
		ft_putchar(s[k]);
		k++;
	}
	return (0);
}

static int	printf_left_allign(t_print *tab, char *s)
{
	int	len;

	len = content_size(tab, s);
	if(tab->zero && !tab->dot && !tab->minus)
	{
		ft_print_char('0', tab->precision - len);
		ft_print_char('0', tab->width - tab->content_size);
		printing_octal(s);
	}
	else
	{
		ft_print_char('0', tab->precision - len);
		printing_octal(s);
		ft_print_char(' ', tab->width - tab->content_size);
	}
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (tab->content_size);
}

static int	printf_right_allign(t_print *tab, char *s)
{
	int	len;

	len = content_size(tab, s);
	if(tab->zero && !tab->dot && !tab->minus)
	{
		ft_print_char('0', tab->precision - len);
		ft_print_char('0', tab->width - tab->content_size);
		printing_octal(s);
	}
	else
	{
		ft_print_char(' ', tab->width - tab->content_size);
		ft_print_char('0', tab->precision - len);
		printing_octal(s);
	}
	if (tab->width > tab->content_size)
		tab->content_size = tab->width;
	return (tab->content_size);
}

int	print_octal(t_print *tab)
{
	int	count;
	char	*s;
	unsigned long long	k;

	k = va_arg(tab->args, unsigned int);
	if (k == 0)
	{
		if (tab->dot && !tab->precision)
			s = ft_strdup("");
		else
		{
			s = ft_strdup("0");
			tab->null = 1;
		}
	}
	else
		s = hex_conv(k, OCTAL);
	if (tab->minus)
		count = printf_left_allign(tab, s);
	else
		count = printf_right_allign(tab, s);
	return (count);
}