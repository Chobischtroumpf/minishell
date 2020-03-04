/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:05:37 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/28 11:42:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (s1 == 0)
		return (NULL);
	if (s1 == s2)
		return (s1);
	if (s1 == NULL && s2 == NULL)
		return (s1);
	i = 0;
	while (i < n)
	{
		((char*)s1)[i] = ((char*)s2)[i];
		i++;
	}
	return (s1);
}
