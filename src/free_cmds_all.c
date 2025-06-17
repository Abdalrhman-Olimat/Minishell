/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:19 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 09:17:38 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/**
 * safe_free_str - Safely frees a string pointer
 * @ptr: The pointer to free
 *
 * Only frees if the pointer is not NULL
 */
static void	safe_free_str(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
}

/**
 * free_cmd_strings - Frees all string members of a command
 * @cmd: The command data structure
 */
static void	free_cmd_strings(t_command_data *cmd)
{
	safe_free_str(cmd->cmd_full);
	safe_free_str(cmd->in_file);
	safe_free_str(cmd->out_file);
	safe_free_str(cmd->path_var);
	safe_free_str(cmd->cmd_path);
}

/**
 * free_delimiters - Frees the array of delimiter strings
 * @delim: Array of delimiter strings
 */
static void	free_delimiters(char **delim)
{
	int	i;

	if (!delim)
		return ;
	i = 0;
	while (delim[i] != NULL)
	{
		safe_free_str(delim[i]);
		i++;
	}
	free(delim);
}

/**
 * free_single_cmd_node - Frees a single command node and all its members
 * @cmd: Command data to free
 */
static void	free_single_cmd_node(t_command_data *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fd_of_heredoc != -1)
	{
		close(cmd->fd_of_heredoc);
		cmd->fd_of_heredoc = -1;
	}
	free_cmd_strings(cmd);
	if (cmd->cmd_splitted)
		free_2d_arr(cmd->cmd_splitted);
	if (cmd->delim)
		free_delimiters(cmd->delim);
	free(cmd);
}

/**
 * free_cmds_all - Frees an array of command data structures
 * @cmds: Array of command data pointers
 * @count: Number of commands in the array
 * @start_index: Index to start freeing from
 */
void	free_cmds_all(t_command_data **cmds, short count, int start_index)
{
	short	index;

	if (!cmds)
		return ;
	if (start_index < 0)
		start_index = 0;
	index = start_index;
	while (index < count)
	{
		if (cmds[index])
			free_single_cmd_node(cmds[index]);
		index++;
	}
	free(cmds);
}
