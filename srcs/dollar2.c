/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:40:22 by nathan            #+#    #+#             */
/*   Updated: 2020/12/15 12:32:17 by ncolin           ###   ########.fr       */
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
	splitted = ft_split(args[i], ' ');
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
	int count;

	count = 0;
	tmp = ft_strtrim(str, " ");
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			count++;
			while (ft_isspace(str[++i]))
				;
		}
		i++;
	}
	free(tmp);
	return (count);
}

// void	check_dollar(t_cmd *cmd)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = cmd->argv;
// 	while (args[i])
// 	{
// 		while (has_dollar(args[i]))
// 		{
// 			args[i] = dollar_to_env(args[i]);
// 			if (ft_is_split(args[i]))
// 				cmd->argv = ft_gros_bordel(args, i);
// 		}
// 		i++;
// 	}
// }
