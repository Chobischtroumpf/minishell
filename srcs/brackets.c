/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/12 16:27:53 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_backslash_counter(char *str, int i)
{
    int counter;

    counter = 0;
    i--;
    while(i >= 0 && str[i] == '\\')
    {
        counter++;
        i--;
    }
    return (counter);
}

int			quote_removal(char *c)
{
	if (*c == '"' || *c == '\'')
	{
		*c = 3;
		return(1);
	}
	return(0);
}
static char	*arg_cleaner(char *arg)
{
	int		j;
	int		previous_j;
	char	*new_arg;

	j = 0;
	while(arg[j])
	{
		if (arg[j] == '\"' || arg[j] == '\'')
		{
			if (!(ft_backslash_counter(arg, j) % 2))
			{
				previous_j = j;
				j = ft_brackets(arg, j);
				quote_removal(&(arg[previous_j]));
				quote_removal(&(arg[j]));
			}
		}
		j++;
	}
	if (!(new_arg = ft_strtrim_integral(arg, 3)))
		return ((char*)ft_exit_error());
	return(new_arg);
}


int			ft_bracket_removal(t_cmd **cmd)
{
	char	**new_argv;
	int		i;

	i = 0;
	while((*cmd)->argv[i])
		i++;
	if (!(new_argv = malloc(sizeof(char *) * i + 1)))
		return(-1);
	i = 0;
	while((*cmd)->argv[i])
	{
		if (!(new_argv[i] = arg_cleaner((*cmd)->argv[i])))
		{
			ft_free_array(new_argv);
			return ((int)ft_exit_error());
		}
		i++;
	}
	new_argv[i] = NULL;
	ft_free_array((*cmd)->argv);
	(*cmd)->argv = new_argv;
	return (1);
}
