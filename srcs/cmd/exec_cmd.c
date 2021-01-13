/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/13 23:33:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ret = ft_exec_export(cmd, 0);
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
		if (!(tmp = check_rdir_space(in->file)))
			return (0);
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
		if (!(tmp = check_rdir_space(out->file)))
			return (0);
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

void		exec_no_pipe(t_cmd *cmd)
{
	int	btin_nb;

	open_redirection(cmd);
	if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
		ft_get_exit_code(NO_STATUS, ft_exec_builtin(btin_nb, cmd));
	else if (cmd->argv[0])
		ft_exec_extern(cmd);
	close_redirection(cmd);
}

/*
** ft_exec_cmd is the command in charge of executing the different comands
** found in the t_cmd struct
*/

int			ft_exec_cmd(void)
{
	t_cmd		*cmd;

	get_minishell()->executed = 1;
	cmd = get_minishell()->cmd;
	while (cmd)
	{
		ft_dollar_quotes(cmd);
		if (cmd->pipe)
		{
			cmd = handle_pipe(get_minishell(), cmd, count_pipes(cmd), -1);
			continue ;
		}
		if (!check_in(cmd->in) || !check_out(cmd->out))
		{
			get_minishell()->exval = 1;
			cmd = cmd->next;
			continue;
		}
		if (!cmd->is_rdir)
			update_lastcmd(ft_last_arg(cmd->argv));
		exec_no_pipe(cmd);
		cmd = cmd->next;
	}
	get_minishell()->executed = 0;
	return (1);
}
