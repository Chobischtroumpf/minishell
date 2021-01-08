/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:38:47 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/08 12:59:58 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_lexing(void)
{
	t_minishell *minishell;
	int nbr_tokens;
	char *tmp;

	int x;
	x = -1;
	minishell = get_minishell();
	tmp = minishell->line;
	minishell->line = ft_strtrim(tmp, "\t\r\v\f");
	free(tmp);
	if ((nbr_tokens = ft_tokens_count(minishell->line)) < 0)
		return (ft_get_exit_code(NO_STATUS, ft_eof_error(nbr_tokens, 2)));
	if (!(minishell->tokens = malloc(sizeof(char *) * (nbr_tokens + 1))))
		ft_exit_error();
	while (++x < nbr_tokens)
	{
		tmp = ft_tokens_split(minishell->line, x + 1);
		minishell->tokens[x] = ft_strdup(tmp);
		free(tmp);
	}
	minishell->tokens[x] = NULL;
	return (1);
}

int get_next_char(int fd, char *cptr)
{
	static char buf;
	int ret;

	buf = 0;
	if (fd < 0 || fd > FOPEN_MAX || !cptr)
		return (-1);
	ret = read(fd, &buf, 1);
	if (ret == -1)
		ft_err_read_error("read failed", -1);
	else
		*cptr = buf;
	return (ret);
}

int ft_line_handle(void)
{
	t_minishell *minish;
	int ret;
	char c;

	minish = get_minishell();
	while ((ret = get_next_char(STDIN_FILENO, &c)) == 1)
	{
		if (c == '\n')
			break;
		minish->line = ft_strjoin_doublefree(minish->line, ft_chardup(c));
	}
	if (ret == -1)
		ft_exit_error();
	if (ret == 1)
	{
		if (!minish->line || !ft_lexing())
			return (0);
		free(minish->line);
		minish->line = NULL;
	}
	else if (ret == 0 && (minish->was_eof = 1))
		if (!minish->line || !(minish->line)[0])
			ft_eof_exit();
	return (ret);
}
