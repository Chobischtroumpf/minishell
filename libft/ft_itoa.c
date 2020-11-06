/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:09:03 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/05 12:31:41 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_len(int nbr)
{
	int				count;
	unsigned int	unbr;

	if (nbr == 0)
		return (1);
	count = 0;
	unbr = nbr;
	if (nbr < 0)
	{
		count++;
		unbr = -unbr;
	}
	while (unbr > 0)
	{
		unbr /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(long n)
{
	char			*str;
	int				len;
	int				is_negative;
	unsigned long	unbr;

	len = count_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	is_negative = 0;
	unbr = n;
	if (n < 0)
	{
		is_negative = 1;
		str[0] = '-';
		unbr = -n;
	}
	len--;
	while (len >= is_negative)
	{
		str[len] = unbr % 10 + '0';
		unbr /= 10;
		len--;
	}
	return (str);
}
