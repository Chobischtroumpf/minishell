/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:56:04 by ncolin            #+#    #+#             */
/*   Updated: 2021/02/14 14:12:40 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup2_and_close_pipe(int pipes[], int i, int nb)
{
	int	j;

	j = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i < nb)
		dup2(pipes[i * 2 + 1], 1);
	if (i > 0)
		dup2(pipes[(i - 1) * 2], 0);
	while (j < 2 * nb)
		close(pipes[j++]);
}

static void	close_pipe_and_wait(int pipes[], int nb, int cpid[])
{
	int status;
	int	i;

	i = 0;
	while (i < 2 * nb)
		close(pipes[i++]);
	i = 0;
	while (i < nb + 1)
	{
		waitpid(cpid[i], &status, 0);
		i++;
	}
	ft_get_exit_code(status, NO_EXCODE);
}

static int	start_pipes(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pipes + (i * 2)) == -1)
			ft_exit_error(NULL);
		i++;
	}
	return (1);
}

static void	handle_with_pipes(t_cmd *cmd)
{
	int btin_nb;

	open_redirection(cmd);
	if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
		exit(ft_exec_builtin(btin_nb, cmd));
	exec_cmd(cmd);
	close_redirection(cmd);
}

t_cmd		*handle_pipe(t_minishell *m, t_cmd *cmd, int pipe_nb, int i)
{
	int pipe_fds[pipe_nb * 2];
	int pids[pipe_nb + 1];

	if (!start_pipes(pipe_fds, pipe_nb))
		return (0);
	while (++i < (pipe_nb + 1))
	{
		if ((pids[i] = fork()) == 0)
		{
			dup2_and_close_pipe(pipe_fds, i, pipe_nb);
			ft_dollar_quotes(cmd);
			if ((!check_in(cmd->in) || !check_out(cmd->out)) && (m->exval = 1))
				continue ;
			handle_with_pipes(cmd);
		}
		else if (pids[i] == -1)
			ft_exit_error(NULL);
		cmd = cmd->next;
	}
	close_pipe_and_wait(pipe_fds, pipe_nb, pids);
	return (cmd);
}
