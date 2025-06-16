/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_big_malloc_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:04 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 00:21:09 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_big_malloc_cmds(size_t err_num, t_command_data **cmds, int i_param)
{
	if (!cmds)
		return ;
	int k = 0;
	while (cmds[k])
	{
		if (cmds[k]->cmd_splitted)
			free_2d_arr(cmds[k]->cmd_splitted);
		if (cmds[k]->in_file)
			free(cmds[k]->in_file);
		if (cmds[k]->out_file)
			free(cmds[k]->out_file);
		if (cmds[k]->cmd_full)
			free(cmds[k]->cmd_full);
		if (cmds[k]->cmd_path)
			free(cmds[k]->cmd_path);
		if (cmds[k]->delim)
			free_2d_arr(cmds[k]->delim);
		if (cmds[k]->path_var)
			free(cmds[k]->path_var);
		free(cmds[k]);
		cmds[k] = NULL;
		k++;
	}
	free(cmds);
}
