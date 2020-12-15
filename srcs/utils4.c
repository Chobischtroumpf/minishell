/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:02:38 by alessandro        #+#    #+#             */
/*   Updated: 2020/12/11 15:03:51 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chardup(char c)
{
	char *dup;

	if (!(dup = (char*)ft_calloc(2, sizeof(char))))
	{
		ft_exit_error();
		return (NULL);
	}
	dup[0] = c;
	return (dup);
}
