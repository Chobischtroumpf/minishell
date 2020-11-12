/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/12 17:01:51 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** is_builtin is a function that checks whether the command currently being
** executed is built into minishell, if it is, it returns the position in the
** array where it is located
*/

static int	is_built_in(char *command)
{
	char		**builtin;
	int			i;

	i = 0;
	builtin = get_built_in();
	while (builtin[i])
	{
		if (!ft_strcmp(command, builtin[i]))
			return (i);
		i++;
	}
	return (-1);
}

/*
** executes the specified builtin command, depending on the bltin_pos
** variable's value
*/

static int	ft_exec_builtin(int bltin_pos, t_cmd *cmd)
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

static int	check_in(t_rdir *in)
{
	while (in)
	{
		if ((in->fd = open(in->file, O_RDONLY)) < 0)
			return (ft_no_file_error(NULL, in->file, 0));
		if (in->next)
			close(in->fd);
		in = in->next;
	}
	return (1);
}

// check_out and check_in will need to be modified so that the $ symbol is checked in filenames as well

static int check_out(t_rdir *out)
{
	while (out)
	{
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
		check_dollar(cmd);
		//rm ' ' && " "
		//check pipe
		ft_bracket_removal(&cmd);
		check_in(cmd->in);
		check_out(cmd->out);
		open_redirection(cmd);
		if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
			ft_get_exit_code(NO_STATUS, ft_exec_builtin(btin_nb, cmd));
		else
			ft_exec_extern(cmd);
		close_redirection(cmd);
		printf("excode = %d\n", get_minishell()->excode);
		cmd = cmd->next;
	}
	get_minishell()->executed = 0;
	return (1);
}
