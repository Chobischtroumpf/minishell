/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:14:36 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/15 10:33:06 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dest;
	const char	*source;
	size_t		i;
	size_t		dlen;

	dest = dst;
	source = src;
	i = size;
	while (i-- != 0 && *dest)
		dest++;
	dlen = dest - dst;
	i = size - dlen;
	if (i == 0)
		return (dlen + ft_strlen(source));
	while (*source)
	{
		if (i != 1)
		{
			*dest++ = *source;
			i--;
		}
		source++;
	}
	*dest = '\0';
	return (dlen + (source - src));
}
