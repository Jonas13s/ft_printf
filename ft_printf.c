/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:49 by joivanau          #+#    #+#             */
/*   Updated: 2022/01/31 15:01:16 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf2(const char *format, t_print *tab, t_length *mod)
{
	size_t	len;
	int		i;

	i = ft_strlen(format);
	len = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			init_struct(tab);
			init_fstruct(mod);
			++format;
			ft_convert_args(format, tab, mod);
			format += tab->total_length;
			len += tab->content_size;
			if (tab->total_length >= i)
				break ;
		}
		else
		{
			len += write(1, format, 1);
			++format;
		}
	}
	return (len);
}

void	print_struc(t_print *tab, t_length *mod)
{
	printf("plus: %d\nminus %d\nzero %d\nhash %d\npercent %d\n space %d\ndot %d\nwidth %d\nprecision %d\ncontent_size %d\nlength %d\n h %d\n l %d\nL %d", \
	tab->plus, tab->minus, tab->zero, tab->hash, tab->percent,\
	tab->space, tab->dot, tab->width, tab->precision, tab->content_size, tab->total_length, mod->h, mod->l, mod->L);
}

int	ft_printf(const char *format, ...)
{
	t_print		*tab;
	t_length	*mod;
	size_t		length;

	tab = (t_print *) malloc(sizeof(t_print));
	mod = (t_length *) malloc(sizeof(t_length));
	if (!mod || !tab)
		return (-1);
	init_struct(tab);
	va_start(tab->args, format);
	length = ft_printf2(format, tab, mod);
	//print_struc(tab, mod);
	va_end(tab->args);
	free (tab);
	free (mod);
	return (length);
}
/*
int	main(void)
{
	//ft_printf("%s\n", "");
	int o = 5;
	//static char *s_hidden = "hi low\0don't print me lol\0";
	int k, l;
	k = printf("og:% ZBLABAB\n", 123);
	l = ft_printf("ft:% ZBLABAB\n", 123);
	printf("og: %d ft: %d\n",k, l);
	//printf("\n%d\n", k);
}
*/