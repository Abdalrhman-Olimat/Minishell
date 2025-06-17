/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:25:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/17 12:48:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	print_word(char *word, int *first_ptr)
{
	if (!*first_ptr)
		printf(" ");
	printf("%s", word);
	*first_ptr = 0;
}

static void	init_echo_vars(int *i, int *suppress_newline, int *first)
{
	*i = 1;
	*suppress_newline = 0;
	*first = 1;
}

static int	is_valid_n_flag(char *arg)
{
	int	j;

	if (arg[0] != '-')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	if (arg[j] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	suppress_newline;
	int	first;

	init_echo_vars(&i, &suppress_newline, &first);
	if (argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (argv[i] != NULL && is_valid_n_flag(argv[i]))
	{
		suppress_newline = 1;
		i++;
	}
	while (argv[i] != NULL)
	{
		print_word(argv[i], &first);
		i++;
	}
	if (!suppress_newline)
		printf("\n");
	return (0);
}
