/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:13:25 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 10:29:20 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static bool	try_open_infile(const char *filename)
{
	int	fd;

	if (access(filename, R_OK) == 0)
		return (true);
	else
		return (false);
}

static void	register_valid_infile(t_input **token, t_command_data *cmd)
{
	cmd->content_analyze.is_there_infile = true;
	ft_strlcpy(cmd->in_file, (*token)->next->string, MAXIMUM_FILENAME_SIZE);
}

int	handle_redir_in(t_shell *shell, t_input **token, int *cmd_i,
		t_command_data **cmds)
{
	char	*filename;
	int		fd;

	if (!token || !*token || !(*token)->next)
		return (0);
	filename = (*token)->next->string;
	fd = try_open_infile(filename);
	if (fd == false)
	{
		alert_err_of_file(filename);
		set_status_skip(shell, cmds, cmd_i, 1);
		return (0);
	}
	register_valid_infile(token, cmds[*cmd_i]);
	return (3);
}
