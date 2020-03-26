/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:55:21 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 11:48:33 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *scpy;

	if (ft_strlen(s) < start)
	{
		if (!(scpy = malloc(sizeof(char))))
			return (NULL);
		*scpy = '\0';
		return (scpy);
	}
	else if (s)
	{
		return (ft_strndup(&s[start], len));
	}
	else
		return (NULL);
}
