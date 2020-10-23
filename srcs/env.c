/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:07:45 by nathan            #+#    #+#             */
/*   Updated: 2020/10/24 00:36:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	ft_free_env goes through the linked list containing the environnement
**	variables and frees every node.
*/

void		ft_free_env(void)
{
	t_minishell	*minishell;
	t_list		*tmp;

	minishell = get_minishell();
	tmp = minishell->env;
	while (minishell->env != NULL)
	{
		tmp = minishell->env;
		minishell->env = minishell->env->next;
		free(((t_env_var *)(tmp->content))->key);
		free(((t_env_var *)(tmp->content))->value);
		free(tmp->content);
	}
}

/*
**	ft_free_array() frees every *char in a **char and then
**	frees the **char itself
*/

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

/*
**	new_env_var() takes a key_value **char as argument.
**
** 	It will allocates memory for a t_env_var struct and then ft_strdup()
**	the key in t_env_var->key amd the value in t_env_var->value.
**	The value part can be splitted into multiples *char when received.
**	If that is the case, those *char will be str_joined before being put
**	into the struct.
**
**	Returns a pointer to the t_env_var.
*/

t_env_var	*new_env_var(char **key_value)
{
	t_env_var	*new_var;
	char		*tmp;
	int			i;

	i = 2;
	if (!(new_var = malloc(sizeof(t_env_var))))
		return (NULL);
	new_var->key = ft_strdup(key_value[0]);
	if (key_value[1])
	{
		tmp = ft_strdup(key_value[1]);
		while (key_value[i])
		{
			tmp = ft_strjoin_delimiter(tmp, key_value[i], '=');
			i++;
		}
		new_var->value = ft_strdup(tmp);
		free(tmp);
	}
	else
		new_var->value = ""; //Should I strdup a ""?
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

/*
**	Converts the linked_list storing the environement variables to a **char.
*/

char		**env_to_array(void)
{
	t_minishell	*mish;
	t_list		*tmp;
	char		**array;
	int			i;

	mish = get_minishell();
	if (!(array = (char **)malloc(sizeof(char*) * ft_lstsize(mish->env) + 1)))
		return (0);
	tmp = mish->env;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strjoin_delimiter(((t_env_var*)(tmp->content))->key, \
									((t_env_var*)(tmp->content))->value, '=');
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
