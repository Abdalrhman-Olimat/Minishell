/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:12:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 01:08:03 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	increase_heredoc_index(t_command_data **cmd, int *cmd_i)
{
	if (NULL == cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc])
		return (0);
	else
	{
		cmd[*cmd_i]->index_of_heredoc++;
		return (1);
	}
}

int	handle_heredoc(t_shell *shell, t_input **token, t_command_data **cmd,
		int *cmd_i)
{
	if (FT)
	{
		/* Mark that this command has a heredoc */
		cmd[*cmd_i]->content_analyze.is_there_heredoc = true;
		
		/* Check if this token has a next token */
		if ((*token)->next == NULL)
		{
			/* No delimiter found */
			cmd[*cmd_i]->skip_cmd = true;
			shell->exit_status = 2;
			return (0);
		}
		
		/* Get the next token (delimiter) but don't modify the pointer */
		/* *token = (*token)->next; - Commented out to fix memory leak */
		
		/* If there's no command before the heredoc, create a dummy command */
		if (cmd[*cmd_i]->cmd_full == NULL || cmd[*cmd_i]->cmd_full[0] == '\0')
		{
			// cmd[*cmd_i]->cmd_full is already allocated by prepare_command_struct.
			// No need to malloc it again. Just copy "cat" into the existing buffer.
			ft_strlcpy(cmd[*cmd_i]->cmd_full, "cat", MAXIMUM_CMD_SIZE);
			
			// cmd_splitted part: prepare_command_struct initializes cmd_splitted to NULL.
			// The responsibility of creating cmd_splitted will now solely be on init_splits
			// based on the content of cmd_full.
			// Removed allocation of dummy cmd_splitted here to prevent leaks.
		}
		
		/* Store the delimiter */
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc] = ft_strdup((*token)->next->string);
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc + 1] = NULL;
	}
	return (increase_heredoc_index(cmd, cmd_i));
}
