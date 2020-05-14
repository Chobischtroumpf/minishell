/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:03:16 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/14 10:26:44 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*new_str;
	char	*new_cpy;

	if (!(new_str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	new_cpy = new_str;
	while (*s1 && size--)
		*new_cpy++ = *s1++;
	*new_cpy = '\0';
	return (new_str);
}
