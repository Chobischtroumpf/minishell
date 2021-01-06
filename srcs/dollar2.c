/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:40:22 by nathan            #+#    #+#             */
/*   Updated: 2021/01/05 23:07:01 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_out_array(char **pointertoarray)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (pointertoarray[count])
		count++;
	while (i < count)
	{
		printf("ARGS[%i] >%s< \n", i, pointertoarray[i]);
		i++;
	}
}

char	**ft_split_args(char **args, int i)
{
	char	**splitted;
	char	**new_args;
	int		j;
	int		k;

	j = 0;
	k = 0;
	splitted = ft_split_skip(args[i], ' ', "'\"");
	new_args = malloc(sizeof(char*) * (ft_count_arg(args) + \
										ft_count_arg(splitted) + 2));
	while (j < i)
	{
		new_args[j] = ft_strdup(args[j]);
		j++;
	}
	while (splitted[k])
	{
		new_args[j] = ft_strdup(splitted[k]);
		j++;
		k++;
	}
	i++;
	while (args[i])
	{
		new_args[j] = ft_strdup(args[i]);
		i++;
		j++;
	}
	ft_free_array(splitted);
	new_args[j] = NULL;
	return (new_args);
}

int		ft_is_split(char *str)
{
	char	*tmp;
	int		i;
	int		count;

	count = 0;
	tmp = ft_strtrim(str, " ");
	i = 0;
	while (str[i++])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (ft_isspace(str[i]) && i != 0)
		{
			count++;
			while (ft_isspace(str[i]))
				i++;
			continue ;
		}
	}
	if (str[i - 1] == ' ')
		count--;
	free(tmp);
	return (count);
}
