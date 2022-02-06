/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:10:56 by joivanau          #+#    #+#             */
/*   Updated: 2022/02/05 20:26:36 by joivanau         ###   ########.fr       */
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

static long long	octal_read(t_print *tab, t_length *mod)
{
	long long k;

	if (mod->h == 1)
		k = (unsigned short int)va_arg(tab->args, int);
	else if (mod->h == 2)
		k = (unsigned char)va_arg(tab->args, int);
	else if (mod->l == 1)
		k = (unsigned long int)va_arg(tab->args, long);
	else if (mod->l == 2)
		k = (unsigned long long int)va_arg(tab->args, long long);
	else
		k = va_arg(tab->args,unsigned int);
	return (k);
}

int	print_octal(t_print *tab, t_length *mod)
{
	int	count;
	char	*s;
	unsigned long long	k;

	k = octal_read(tab, mod);
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
	ft_strdel(&s);
	return (count);
}