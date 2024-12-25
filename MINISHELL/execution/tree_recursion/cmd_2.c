/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:22:01 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 08:10:44 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	initial_checks(void)
{
	char	*input;
	DIR		*dir;

	input = getcwd(NULL, 0);
	dir = opendir(".");
	if (!isatty(0) || !input || !dir)
		return (free(input), closedir(dir), 1);
	return (free(input), closedir(dir), 0);
}

int	look_space(t_tree *leaf)
{
	int	i;

	i = -1;
	while (leaf->content[++i])
	{
		if (leaf->content[i][0] == '\'' && \
		ft_strlen(leaf->content[i]) == 1)
			return (0);
	}
	return (1);
}

char	**generate_cmd(char **string)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (string[i])
	{
		if (here_comp(string[i], " ", 1) && here_comp(string[i], "\t", 1))
		{
			tmp = string[i++];
			while (string[i] && (here_comp(string[i], " ", 1) \
			&& here_comp(string[i], "\t", 1)))
				tmp = ft_strjoin(tmp, string[i++]);
			string[j++] = ft_substr(tmp, 0, ft_strlen(tmp));
		}
		else
			i++;
	}
	return (string[j] = NULL, string);
}
