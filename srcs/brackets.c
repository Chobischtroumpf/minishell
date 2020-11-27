/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/27 01:30:31 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*char_swap(int nbr_bckslsh, int previous_j, int j, char *arg)
{
	char	*arg_cpy;

	if (!(arg_cpy = ft_strdup(arg)))
		return (NULL);
	while (previous_j < j)
	{
		nbr_bckslsh = 0;
		while (arg_cpy[previous_j] == '\\' &&
			ft_isascii_except(arg_cpy[previous_j + 1]))
		{
			nbr_bckslsh += 1;
			if (nbr_bckslsh % 2)
				arg_cpy[previous_j] = 2;
			previous_j++;
		}
		previous_j++;
	}
	free(arg);
	return (arg_cpy);
}

char		*ft_bckslsh_outside_quotes(char *arg, int i, int *nbr_bkslsh)
{
	char	*new_arg;

	new_arg = NULL;
	if (arg[i] == '\\')
	{
		while (arg[i] == '\\')
		{
			*nbr_bkslsh += 1;
			if (*nbr_bkslsh % 2)
				arg[i] = 2;
			i++;
		}
		if (!(new_arg = ft_strtrim_integral(arg, (char)2)))
			return (NULL);
	}
	if (!new_arg)
		if (!(new_arg = ft_strdup(arg)))
			return (NULL);
	free(arg);
	return (new_arg);
}

char		*ft_backslash_remover(int j, int nbr_bckslsh, char *arg)
{
	int		previous_j;
	char	*arg_cpy;

	if (!(arg_cpy = ft_strdup(arg)))
		return (NULL);
	if (arg_cpy[j] == '"' && !(nbr_bckslsh % 2))
	{
		previous_j = j;
		j = ft_brackets(arg_cpy, j);
		arg_cpy[previous_j] = 2;
		arg_cpy[j] = 2;
		if (!(arg_cpy = char_swap(nbr_bckslsh, previous_j, j, arg_cpy)))
		{
			free(arg);
			return (NULL);
		}
	}
	else if (arg_cpy[j] == '\'' && !(nbr_bckslsh % 2))
	{
		previous_j = j;
		j = ft_brackets(arg_cpy, j);
		arg_cpy[j] = 2;
		arg_cpy[previous_j] = 2;
	}
	free(arg);
	return (arg_cpy);
}

char		*ft_arg_cleaner(char *arg)
{
	int		j;
	int		nbr_bckslsh;
	char	*new_arg;
	char	*arg_cpy;

	j = 0;
	if (!(arg_cpy = strdup(arg)))
		return (NULL);
	while (arg_cpy[j])
	{
		nbr_bckslsh = 0;
		if (!(arg_cpy = ft_bckslsh_outside_quotes(arg_cpy, j, &nbr_bckslsh)))
			return (NULL);
		if ((arg_cpy[j] == '"' || arg_cpy[j] == '\'') && !(nbr_bckslsh % 2))
			if (!(arg_cpy = ft_backslash_remover(j, nbr_bckslsh, arg_cpy)))
				return (NULL);
		j++;
	}
	if (!(new_arg = ft_strtrim_integral(arg_cpy, (char)2)))
		return (NULL);
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
