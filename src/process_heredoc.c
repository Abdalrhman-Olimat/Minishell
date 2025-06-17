/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 08:42:06 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	handle_heredoc_parent_process(t_shell *shell, t_command_data *cmd,
				int pipe_fd[2], pid_t pid);
static int	handle_heredoc_interrupt(t_shell *shell, t_command_data *cmd,
				int pipe_fd);
static int	setup_heredoc_process(t_shell *shell, t_command_data *cmd,
				int delem_index, int pipe_fd[2]);
static void	parent_signal_handler(int sig);
static void	handle_heredoc_child_process(int pipe_fd[2], t_command_data *cmd,
		int delem_index)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	handle_heredoc_input(pipe_fd[1], cmd, delem_index);
	close(pipe_fd[1]);
	exit(0);
}

static int	handle_heredoc_parent_process(t_shell *shell, t_command_data *cmd,
		int pipe_fd[2], pid_t pid)
{
	int	status;

	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 130))
		return (handle_heredoc_interrupt(shell, cmd, pipe_fd[0]));
	if (g_signal == 130)
		return (handle_heredoc_interrupt(shell, cmd, pipe_fd[0]));
	cmd->fd_of_heredoc = pipe_fd[0];
	return (0);
}

static int	handle_heredoc_interrupt(t_shell *shell, t_command_data *cmd,
		int pipe_fd)
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

static void	parent_signal_handler(int sig)
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
