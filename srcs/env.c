/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:07:45 by nathan            #+#    #+#             */
/*   Updated: 2020/10/23 00:49:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_exec_env()
{
	t_minishell	*minishell;
	t_list		*tmp;
	
	minishell = get_minishell();
	tmp =  minishell->env;
	while (tmp)
	{
		printf("%s=%s\n", ((t_env_var*)(tmp->content))->key, ((t_env_var*)(tmp->content))->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void		ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

t_env_var	*new_env_var(char **key_value)
{
	t_env_var	*new_var;

	if (!(new_var = malloc(sizeof(t_env_var))))
		return (NULL);
	new_var->key = ft_strdup(key_value[0]);
	if (key_value[1])
	{
		new_var->value = ft_strdup(key_value[1]);
		// Need to ft_strjoin in case the key_value array is bigger than 2 chars
		// That can happen if a var value contains an "=" sign
	}
	else
		new_var->value = "";
	return (new_var);
}

/*
** Allocate memory for a **char and store the environement
** variables inside.
*/

void		ft_init_env(t_minishell *minishell, char **envv)
{
	int			i;
	char		**key_value;
	t_env_var	*new_node;

	i = 0;
	while (envv[i])
	{
		key_value = ft_split(envv[i], '=');
		if (!(new_node = new_env_var(key_value)))
		{
			ft_free_array(key_value);
		}
		ft_lstadd_back(&minishell->env, ft_lstnew(new_node));
		ft_free_array(key_value);
		i++;
	}
}
