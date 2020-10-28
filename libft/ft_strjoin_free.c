/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 21:56:36 by nathan            #+#    #+#             */
/*   Updated: 2020/10/27 21:59:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char		*dest;

	if (s1 && s2)
	{
		if (!(dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcpy(dest, s1);
		ft_strcat(dest, s2);
		free(s1);
		return (dest);
	}
	else
		return (NULL);
}
