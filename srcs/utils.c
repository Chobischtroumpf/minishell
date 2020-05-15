/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/14 15:01:28 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_hasnchar(const char *s, char *c)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				count_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

t_cmd			*ft_last_cmd(t_cmd *cmd)
{
	t_cmd	*last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}
