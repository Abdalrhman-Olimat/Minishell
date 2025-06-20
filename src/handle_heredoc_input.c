/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 09:17:23 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static char	*validate_heredoc_delimiter(t_command_data *cmd, int delem_index)
{
	char	*delimiter;

	if (cmd == NULL || cmd->delim == NULL || cmd->delim[delem_index] == NULL)
	{
		write(2, "Error: Invalid heredoc delimiter\n", 32);
		exit(1);
	}
	delimiter = cmd->delim[delem_index];
	if (delimiter[0] == '\0')
	{
		write(2, "Error: Empty heredoc delimiter\n", 30);
		exit(1);
	}
	return (delimiter);
}

static void	put_and_free(char *line, int fd_outstream)
{
	if (line)
	{
		write(fd_outstream, line, ft_strlen(line));
		write(fd_outstream, "\n", 1);
		free(line);
	}
}

void	handle_heredoc_input(int fd_outstream, t_command_data *cmd,
		int delem_index)
{
	char	*line;
	char	*delimiter;

	delimiter = validate_heredoc_delimiter(cmd, delem_index);
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal == 130)
		{
			if (line)
				free(line);
			close(fd_outstream);
			exit(130);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(fd_outstream);
			exit(0);
		}
		put_and_free(line, fd_outstream);
	}
}
