/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:38:47 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/13 16:40:04 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lexing(char *line)
{
	int			nbr_tokens;
	char		**tokens;
	char		*tmp;
	int			index;
	int			x;

	x = 0;
	index = 0;
	while (ft_haschr(SPACE, line[x]))
		x++;
	if (!(tmp = ft_substr(line, x, ft_strlen(line) - x)))
		ft_exit_error();
	if ((nbr_tokens = ft_tokens_count(tmp)) < 0)
	{
		free(tmp);
		return (ft_get_exit_code(NO_STATUS, ft_eof_error(nbr_tokens, 2)));
	}
	if (!(tokens = ft_calloc((nbr_tokens + 1), sizeof(char *))))
		ft_exit_error();
	x = -1;
	while (++x < nbr_tokens)
		if (!(tokens[x] = ft_tokens_split(tmp, &index)))
			ft_exit_error();
	free(tmp);
	return (tokens);
}

int		get_next_char(int fd, char *cptr)
{
	static char	buf;
	int			ret;

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

int		ft_line_handle(int ret)
{
	t_minishell	*minish;
	char		c;

	minish = get_minishell();
	while ((ret = get_next_char(STDIN_FILENO, &c)) == 1)
	{
		if (c == '\n')
			break ;
		if (!(minish->line = ft_strjoin_doublefree(minish->line,
												ft_chardup(c))))
			ft_exit_error();
	}
	if (ret == -1)
		ft_exit_error();
	if (ret == 1)
	{
		if (!minish->line)
			return (0);
		else if (!(minish->tokens = ft_lexing(minish->line)))
			ft_exit_error();
	}
	else if (ret == 0 && (minish->was_eof = 1))
		if (!minish->line || !(minish->line)[0])
			ft_eof_exit();
	return (ret);
}
