/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:03:16 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/11 15:04:01 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while ((unsigned long)i < size && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

