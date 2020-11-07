/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:30:07 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/07 12:06:14 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void    *tmp;
	size_t	i;

	i = 0;
	if (!ptr)
	{
		if (!(tmp = malloc(size)))
			return(NULL);
		return (tmp);
	}
	if (!(tmp = malloc(size)))
		return(NULL);
	while(((char*)ptr)[i] && size-- != 0)
	{
		((char*)tmp)[i] = ((char*)ptr)[i];
		i++;
	}
	free(ptr);
	return(tmp);
}