/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:52:20 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 13:01:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	handle_heredoc_child_process(int pipe_fd[2], t_command_data *cmd,
		int delem_index)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	handle_heredoc_input(pipe_fd[1], cmd, delem_index);
	close(pipe_fd[1]);
	exit(0);
}

int	handle_heredoc_parent_process(t_shell *shell, t_command_data *cmd,
		int pipe_fd[2], pid_t pid)
{
	int	status;

	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 130))
		return (handle_heredoc_interrupt2(shell, cmd, pipe_fd[0]));
	if (g_signal == 130)
		return (handle_heredoc_interrupt2(shell, cmd, pipe_fd[0]));
	cmd->fd_of_heredoc = pipe_fd[0];
	return (0);
}

int	handle_heredoc_interrupt2(t_shell *shell, t_command_data *cmd, int pipe_fd)
{
	close(pipe_fd);
	cmd->fd_of_heredoc = -1;
	cmd->skip_all_execution = true;
	shell->exit_status = 130;
	shell->heredoc_interrupted = true;
	if (cmd->cmd_full && ft_strcmp(cmd->cmd_full, "cat") == 0)
	{
		free(cmd->cmd_full);
		cmd->cmd_full = NULL;
		if (cmd->cmd_splitted)
		{
			free(cmd->cmd_splitted[0]);
			free(cmd->cmd_splitted);
			cmd->cmd_splitted = NULL;
		}
	}
	return (1);
}
