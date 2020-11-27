/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 23:06:59 by nathan            #+#    #+#             */
/*   Updated: 2020/11/27 12:00:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}

int		ft_skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}

void	ft_free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

char	*ft_strtrim_integral(char const *s1, char const set)
{
	char	**tab;
	char	*str_finale;
	int		i;

	i = 0;
	tab = ft_split(s1, set);
	str_finale = ft_strdup("");
	while (tab[i])
	{
		if (!(str_finale = ft_strjoin_free(str_finale, tab[i])))
		{
			ft_free_array(tab);
			return (NULL);
		}
		i++;
	}
	ft_free_array(tab);
	return (str_finale);
}

int		ft_backslash_counter(char *str, int i)
{
	int counter;

	counter = 0;
	while (i >= 0 && str[i] == '\\')
	{
		counter++;
		i--;
	}
	return (counter % 2);
}
