/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:42:56 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/17 11:08:39 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (s)
	{
		str = ft_strdup((const char *)s);
		if (str == NULL)
			return (NULL);
		i = 0;
		while (str[i] != 0)
		{
			str[i] = f((unsigned int)i, str[i]);
			i++;
		}
		return (str);
	}
	else
		return (NULL);
}
