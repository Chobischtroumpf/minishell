/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/13 16:03:06 by adorigo          ###   ########.fr       */
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

char		*ft_backslash_remover(char *arg)
{
	int		i;
	int		nbr_bkslsh;
	char	*new_arg;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			i = ft_brackets(arg, i);
		if (arg[i] == '\\' && (nbr_bkslsh = 1))
		{
			while (arg[i] == '\\')
			{
				if (nbr_bkslsh % 2)
					arg[i++] = 3;
				nbr_bkslsh += 1;
			}
			if (!(new_arg = ft_strtrim_integral(arg, (char)3)))
			{
				// printf("failed\n");
				return (NULL);
			}
		}
		i++;
	}
	return(new_arg);
}

char		*ft_arg_cleaner(char *arg)
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
	if (!(new_arg = ft_strtrim_integral(arg, (char)3)))
		return ((char*)ft_exit_error());
	return(new_arg);
}

int			ft_bracket_removal(t_cmd **cmd)
{
	char	**new_argv;
	char	*tmp;
	int		i;

	i = 0;
	while((*cmd)->argv[i])
		i++;
	if (!(new_argv = malloc(sizeof(char *) * (i + 1))))
		return(-1);
	i = 0;
	while((*cmd)->argv[i])
	{
		if (!(tmp = ft_arg_cleaner((*cmd)->argv[i])))
		{
			ft_free_array(new_argv);
			return ((int)ft_exit_error());
		}
		printf("before backslash_remover\n");
		if (!(new_argv[i] = ft_backslash_remover(tmp)))
		{
			ft_free_array(new_argv);
			return ((int)ft_exit_error());
		}
		printf("after\n");
		// free(tmp);
		i++;
	}
	new_argv[i] = NULL;
	ft_free_array((*cmd)->argv);
	(*cmd)->argv = new_argv;
	return (1);
}
