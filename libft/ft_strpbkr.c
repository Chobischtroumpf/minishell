/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbkr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:42:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/05 17:22:08 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpbkr(const char *s, const char *s2)
{
	char	*ptr;
	char	*ptr2;
	int		index_min;
	int		i;
	int		j;

	index_min = INT_MAX;
	if (!s || !s2)
		return (0);
	ptr = (char *)s;
	ptr2 = (char *)s2;
	i = -1;
	while (ptr2[++i])
	{
		j = -1;
		while (ptr[++j])
			if (ptr[j] == ptr2[i])
				if (j <= index_min)
					index_min = j;
	}
	if (index_min < INT_MAX)
		return (index_min);
	return (0);
}
