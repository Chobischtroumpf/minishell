/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:02:38 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/07 17:45:33 by nathan           ###   ########.fr       */
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

char	*ft_last_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (arg[i - 1]);
}
