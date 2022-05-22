/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:49 by joivanau          #+#    #+#             */
/*   Updated: 2022/05/23 00:28:53 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf2(const char *format, t_print *tab, t_length *mod, ssize_t len)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			init_struct(tab);
			init_fstruct(mod);
			++format;
			if (*format == '\0')
			{
				len = -1;
				break ;
			}
			format += ft_convert_args(format, tab, mod);
			len += tab->content_size;
		}
		else if (*format == '{' && is_color(format))
			format += change_color(format);
		else if (*format != '%')
		{
			len += write(1, format, 1);
			++format;
		}
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	t_print		*tab;
	t_length	*mod;
	ssize_t		len;

	tab = (t_print *) malloc(sizeof(t_print));
	mod = (t_length *) malloc(sizeof(t_length));
	if (!mod || !tab)
		return (-1);
	len = 0;
	init_struct(tab);
	va_start(tab->args, format);
	len = ft_printf2(format, tab, mod, len);
	va_end(tab->args);
	free (tab);
	free (mod);
	return (len);
}
