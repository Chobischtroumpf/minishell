/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/08 23:03:51 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** is_builtin is a function that checks whether the command currently being
** executed is built into minishell, if it is, it returns the position in the
** array where it is located
*/

int			is_built_in(char *command)
{
	char		**builtin;
	int			i;

	i = 0;
	builtin = get_built_in();
	while (builtin[i])
	{
Norme: ./srcs/utils2.c
Norme: ./srcs/bltin_exit.c
Norme: ./srcs/cmd_parser_1.c
Norme: ./srcs/errors.c
Norme: ./srcs/bltin_echo.c
Norme: ./srcs/errors3.c
	}
	return (-1);
}

/*
** executes the specified builtin command, depending on the bltin_pos
** variable's value
*/

int			ft_exec_builtin(int bltin_pos, t_cmd *cmd)
{
	int			ret;

	ret = -1;
	if (bltin_pos == 0)
		ret = ft_exec_echo(cmd);
	if (bltin_pos == 1)
		ret = ft_exec_cd(cmd);
	else if (bltin_pos == 2)
		ret = ft_exec_pwd();
	else if (bltin_pos == 3)
		ret = ft_exec_export(cmd);
	else if (bltin_pos == 4)
		ret = ft_exec_unset(cmd);
	else if (bltin_pos == 5)
		ret = ft_exec_env();
	else if (bltin_pos == 6)
		ret = ft_exec_exit(cmd);
	return (ret);
}

int			check_in(t_rdir *in)
{
	char	*tmp;

	while (in)
	{
		tmp = check_quote(in->file, -1);
		free(in->file);
		in->file = tmp;
		if ((in->fd = open(in->file, O_RDONLY)) < 0)
		{
			if (ft_file_exists(in->file) && !ft_file_is_exec(in->file))
				return (ft_err_no_access(in->file, NULL, 0));
			else
				return (ft_err_file_not_found(NULL, in->file, 0));
		}
		if (in->next)
			close(in->fd);
		in = in->next;
	}
	return (1);
}

int			check_out(t_rdir *out)
{
	char	*tmp;

	while (out)
	{
		tmp = check_quote(out->file, -1);
		free(out->file);
		out->file = tmp;
		if (out->is_dbl)
			out->fd = open(out->file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		else
			out->fd = open(out->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		if (out->fd < 0)
			return (0);
		if (out->next)
			close(out->fd);
		out = out->next;
	}
	return (1);
}

/*
** ft_exec_cmd is the command in charge of executing the different comands
** found in the t_cmd struct
*/

int			ft_exec_cmd(void)
{
	int			btin_nb;
	t_cmd		*cmd;

	get_minishell()->executed = 1;
	cmd = get_minishell()->cmd;
	while (cmd)
	{
		ft_dollar_quotes(cmd);
		if (cmd->pipe)
		{
			cmd = handle_pipe(cmd, count_pipes(cmd));
			continue ;
		}
		if (!check_in(cmd->in) || !check_out(cmd->out))
		{
			get_minishell()->excode = 1;
			cmd = cmd->next;
			continue;
		}
		if (!cmd->is_rdir)
			update_lastcmd(ft_last_arg(cmd->argv));
		open_redirection(cmd);
		if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
			ft_get_exit_code(NO_STATUS, ft_exec_builtin(btin_nb, cmd));
		else if (cmd->argv[0])
			ft_exec_extern(cmd);
		close_redirection(cmd);
		cmd = cmd->next;
	}
	get_minishell()->executed = 0;
	return (1);
}
