/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:00:20 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/10 15:25:50 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char const *src)
{
	char *tmp;

	tmp = dest;
	while (*src != '\0')
	{
		*tmp = *src;
		tmp++;
		src++;
	}
	*tmp = '\0';
	return (dest);
}
