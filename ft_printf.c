/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalgar <isalgar@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:38:33 by isalgar           #+#    #+#             */
/*   Updated: 2022/02/21 10:45:16 by isalgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putall(unsigned long nbr, char *base, int chk_p, int base_len)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	if (chk_p == 3)
	{
		if (!base)
			return (write(1, "(null)", 6));
		else
			while (base[++i])
				len += write(1, &base[i], 1);
		return (len);
	}
	if (chk_p == 1)
		len += write(1, "0x", 2);
	if ((int)nbr < 0 && chk_p == 2)
	{
		len += write(1, "-", 1);
		nbr = nbr * -1;
	}
	if (nbr / base_len != 0)
		len += ft_putall(nbr / base_len, base, 0, base_len);
	len += write(1, &base[nbr % base_len], 1);
	return (len);
}

int	ft_control(char c, va_list a)
{
	int	chr;

	if (c == 'c')
	{
		chr = va_arg(a, int);
		return (write(1, &chr, 1));
	}
	else if (c == 's')
		return (ft_putall(0, va_arg(a, char *), 3, 0));
	else if (c == 'p')
		return (ft_putall(va_arg(a, unsigned long), "0123456789abcdef", 1, 16));
	else if (c == 'd' || c == 'i')
		return (ft_putall(va_arg(a, int), "0123456789", 2, 10));
	else if (c == 'u')
		return (ft_putall(va_arg(a, unsigned), "0123456789", 0, 10));
	else if (c == 'x')
		return (ft_putall(va_arg(a, unsigned), "0123456789abcdef", 0, 16));
	else if (c == 'X')
		return (ft_putall(va_arg(a, unsigned), "0123456789ABCDEF", 0, 16));
	else if (c == '%')
		return (write(1, &c, 1));
	else
		return (write(1, &c, 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	a;

	va_start(a, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			while (str[++i] == ' ')
				;
			len += ft_control(str[i], a);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(a);
	return (len);
}
/*
#include <stdio.h>
int main()
{
	ft_printf("%d",ft_printf("%      Penguen", 42));
	printf("%d",printf("%    Penguen", 42));
}*/
