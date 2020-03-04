/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:07:45 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/17 10:49:33 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *i;

	if (b == 0)
		return (NULL);
	if (len == 0)
		return (b);
	i = b;
	while (len--)
	{
		*i = (unsigned char)c;
		if (len)
			i++;
	}
	return (b);
}
