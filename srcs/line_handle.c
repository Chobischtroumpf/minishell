/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:38:47 by alessandro        #+#    #+#             */
/*   Updated: 2020/10/27 12:00:20 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexing(t_minishell *minishell)
{
	int			nbr_tokens;
	char		*tmp;
	int			x;

	x = -1;
	if ((nbr_tokens = ft_tokens_count(minishell->line)) == -1)
	{
		ft_printf("you need to close the brackets\n");
		return (0);
	}
	if (!(minishell->tokens = malloc(sizeof(char*) * (nbr_tokens + 1))))
		exit(ft_free_cmd() && 0);
	while (++x < nbr_tokens)
	{
		tmp = ft_tokens_split(minishell->line, x + 1);
		minishell->tokens[x] = ft_strtrim(tmp, " \t\n\v\f\r");
		free(tmp);
	}
	minishell->tokens[x] = NULL;
	return (1);
}

int ft_line_handle(void)
{
	int			ret;
	char		*line;
	t_cmd		*tmp2;
	t_minishell	*minishell;

	minishell = get_minishell();
	if ((ret = get_next_line(1, &line)) < 0)
		ft_exit_error();
	minishell->line = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (ret == 0 && ft_strlen(minishell->line))
	{
		ft_putstr("  \b\b");
		return (0);
	}
	else if (ret == 0 && !ft_strlen(minishell->line))
	{
		ft_putstr("  \b\b");
		ft_exit_error();
	}
	if (ret == 1 && ft_strncmp(minishell->line, "\0", 1))
	{
		if (!lexing(minishell))
			return (0);
		if (!ft_cmd_parse(minishell->tokens))
			return (0);
		tmp2 = minishell->cmd;
		// print_lst();
		while (tmp2)
		{
			ft_exec_cmd();
			tmp2 = tmp2->next;
		}
	}
	return(1);
}