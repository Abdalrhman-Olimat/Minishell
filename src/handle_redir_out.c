/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:13:30 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 10:33:51 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	success_redir_out(t_shell *shell, t_input **token,
		t_command_data **cmd, int *cmd_i)
{
	cmd[*cmd_i]->content_analyze.is_there_outfile = true;
	close(cmd[*cmd_i]->temp);
	ft_strlcpy(cmd[*cmd_i]->out_file, (*token)->next->string,
		MAXIMUM_FILENAME_SIZE);
	return (3);
}

int	handle_redir_out(t_shell *shell, t_input **token, t_command_data **cmd,
		int *cmd_i)
{
	int	fd;

	fd = open((*token)->next->string, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	cmd[*cmd_i]->temp = fd;
	if (fd == -1)
	{
		alert_err_of_file((*token)->next->string);
		set_status_skip(shell, cmd, cmd_i, 1);
		return (0);
	}
	return (success_redir_out(shell, token, cmd, cmd_i));
}
