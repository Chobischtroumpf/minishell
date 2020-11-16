/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/16 15:57:28 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			quote_removal(char *c)
{
	if (*c == '"' || *c == '\'')
	{
		*c = 2;
		return (1);
	}
	return (0);
}

char		*ft_backslash_remover(char *arg, int *i, int *nbr_bkslsh)
{
	char	*new_arg;

	new_arg = NULL;
	if (arg[*i] == '\\')
	{
		*nbr_bkslsh = 1;
		while (arg[*i] == '\\')
		{
			if (*nbr_bkslsh % 2)
				arg[*i] = 2;
			*nbr_bkslsh += 1;
			(*i)++;
		}
		if (!(new_arg = ft_strtrim_integral(arg, (char)2)))
			return (NULL);
	}
	if (!new_arg)
		new_arg = ft_strdup(arg);
	free(arg);
	return (new_arg);
}

char		*ft_arg_cleaner(char *arg)
{
	int		j;
	int		previous_j;
	int		nbr_bckslsh;
	char	*new_arg;
	char	*arg_cpy;

	j = 0;
	arg_cpy = strdup(arg);
	nbr_bckslsh = 0;
	while (arg_cpy[j])
	{
		arg_cpy = ft_backslash_remover(arg_cpy, &j, &nbr_bckslsh);
		if (arg_cpy[j] == '"' && !(nbr_bckslsh % 2))
		{
			previous_j = j;
			j = ft_brackets(arg_cpy, j);
			quote_removal(&arg_cpy[previous_j]);
			quote_removal(&arg_cpy[j]);
			while (previous_j < j)
			{
				nbr_bckslsh = 0;
				while (arg_cpy[previous_j] == '\\' && ft_isascii_except(arg[previous_j + 1]))
				{
					nbr_bckslsh += 1;
					if (nbr_bckslsh % 2)
						arg_cpy[previous_j] = 2;
					previous_j++;
				}
				previous_j++;
			}
		}
		else if (arg_cpy[j] == '\'' && !(nbr_bckslsh % 2))
		{
			previous_j = j;
			j = ft_brackets(arg_cpy, j);
			quote_removal(&arg_cpy[j]);
			quote_removal(&arg_cpy[previous_j]);
		}
		j++;
	}
	if (!(new_arg = ft_strtrim_integral(arg_cpy, (char)2)))
		return ((char*)ft_exit_error());
	free(arg_cpy);
	return (new_arg);
}

int			ft_bracket_removal(t_cmd **cmd)
{
	char	**new_argv;
	int		i;

	i = 0;
	while ((*cmd)->argv[i])
		i++;
	if (!(new_argv = malloc(sizeof(char *) * (i + 1))))
		return (-1);
	i = 0;
	while ((*cmd)->argv[i])
	{
		if (!(new_argv[i] = ft_arg_cleaner((*cmd)->argv[i])))
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
