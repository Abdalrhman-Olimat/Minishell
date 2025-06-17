/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_big_malloc_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:04 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 09:22:18 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	free_single_command(t_command_data *cmd, size_t err_num)
{
	if (cmd->fd_of_heredoc != -1)
	{
		close(cmd->fd_of_heredoc);
		cmd->fd_of_heredoc = -1;
	}
	if (cmd->cmd_splitted)
		free_2d_arr(cmd->cmd_splitted);
	if (cmd->in_file)
		free(cmd->in_file);
	if (cmd->out_file)
		free(cmd->out_file);
	if (cmd->cmd_full)
		free(cmd->cmd_full);
	if (cmd->path_var)
		free(cmd->path_var);
	if (cmd->cmd_path && !err_num)
		free(cmd->cmd_path);
	if (cmd->delim)
		free_2d_arr(cmd->delim);
	free(cmd);
}

void	free_big_malloc_cmds(size_t err_num, t_command_data **cmds, int i)
{
	if (!cmds)
		return ;
	if (i == -1)
	{
		while (cmds[++i])
		{
			free_single_command(cmds[i], err_num);
		}
		free(cmds);
	}
}
