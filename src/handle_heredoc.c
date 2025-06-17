/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:12:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 12:39:53 by aeleimat         ###   ########.fr       */
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
		cmd[*cmd_i]->content_analyze.is_there_heredoc = true;
		if ((*token)->next == NULL)
		{
			cmd[*cmd_i]->skip_cmd = true;
			shell->exit_status = 2;
			return (0);
		}
		if (cmd[*cmd_i]->cmd_full == NULL || cmd[*cmd_i]->cmd_full[0] == '\0')
			ft_strlcpy(cmd[*cmd_i]->cmd_full, "cat", MAXIMUM_CMD_SIZE);
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc]
			= ft_strdup((*token)->next->string);
	}
	return (increase_heredoc_index(cmd, cmd_i));
}
