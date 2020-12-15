/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_doublefree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:29:40 by alessandro        #+#    #+#             */
/*   Updated: 2020/12/13 13:23:51 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_doublefree(char *s1, char *s2)
{
	char		*dest;

	if (!(dest = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	free(s2);
	return (dest);
	return (NULL);
}
