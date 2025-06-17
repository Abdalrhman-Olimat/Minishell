/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 13:02:01 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	parent_signal_handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 130;
}

static int	setup_heredoc_process(t_shell *shell, t_command_data *cmd,
		int delem_index, int pipe_fd[2])
{
	if (cmd == NULL || cmd->delim == NULL || cmd->delim[delem_index] == NULL)
	{
		write(2, "Error: Invalid heredoc configuration\n", 36);
		shell->exit_status = 1;
		shell->heredoc_interrupted = true;
		return (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

int	processing_helper(t_shell *shell, t_command_data *cmd, int delem_index)
{
	if (FT)
	{
		cmd->fd_of_heredoc = -1;
		cmd->index_of_heredoc = 0;
	}
	return (0);
}

int	process_heredoc(t_shell *shell, t_command_data *cmd, int delem_index)
{
	int	pipe_fd[2];
	int	pid;

	if (setup_heredoc_process(shell, cmd, delem_index, pipe_fd) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
		handle_heredoc_child_process(pipe_fd, cmd, delem_index);
	else
		return (handle_heredoc_parent_process(shell, cmd, pipe_fd, pid));
	return (0);
}
