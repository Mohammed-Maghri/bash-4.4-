/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:21:54 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:38:23 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_to_string(char *string, char *to_add, int start, int end)
{
	int		i;
	char	*res;
	char	*part_1;
	char	*part_2;

	part_1 = ft_substr(string, 0, start + 1);
	part_2 = ft_substr(string, end, ft_strlen(string) - end);
	res = ft_strjoin(part_1, to_add);
	res = ft_strjoin(res, part_2);
	i = ft_strlen(res);
	return (res[i] = 0, res);
}

char	*cut_string(char *string, int start, int finish)
{
	int		i;
	char	*part_1;
	char	*part_2;
	char	*res;

	part_1 = ft_substr(string, 0, start + 1);
	part_2 = ft_substr(string, finish, ft_strlen(string) - finish);
	res = ft_strjoin(part_1, part_2);
	i = ft_strlen(res);
	return (res[i] = 0, res);
}

char	*delete_opening_quotes(char *string, int quotes_type)
{
	char	*res;
	char	*c;
	int		i;

	i = -1;
	c = gc(2, 0, 0, 0);
	c[1] = 0;
	if (quotes_type == D_QU)
		c[0] = '\"';
	else
		c[0] = '\'';
	if (!string[0])
		return (c[0] = 0, c);
	res = ft_strtrim(string, c);
	while (res[++i])
	{
		if (res[i] == c[0])
		{
			res = cut_string(res, i - 1, i + 1);
			i = -1;
		}
	}
	return (res);
}
