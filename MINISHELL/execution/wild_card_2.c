/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:39:33 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:37:06 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quotes_only(char **input, int i)
{
	int	l;

	l = ft_strlen(input[i]) - 1;
	if ((input[i][0] != '\'' && input[i][0] != '\"') \
	|| (input[i][l] != '\'' && input[i][l] != '\"'))
		return (1);
	if (((i - 1 == -1) || (!here_comp(input[i - 1], " ", 1) \
	|| !here_comp(input[i - 1], "\t", 1))) \
	&& ((!input[i + 1]) \
	|| (!here_comp(input[i + 1], " ", 1) \
	|| !here_comp(input[i + 1], "\t", 1))))
		return (not_empyt_quote(input[i]));
	return (1);
}

int	wild_case(char *input)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(input) - 1;
	if ((input[0] == '\'' || input[0] == '\"') \
	&& (input[l] == '\'' \
	|| input[l] == '\"'))
	{
		while (++i < l)
			if (input[i] == '*')
				return (0);
	}
	return (1);
}

int	not_empyt_quote(char *input)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(input) - 1;
	while (++i < l)
		if (input[i] != 32 && input[i] != 9)
			return (1);
	return (0);
}

int	all_sapce(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != 32 && input[i] != 9)
			return (1);
	if (i > 0)
		return (0);
	return (1);
}

char	*delete_first_and_last(char *string)
{
	char	*allocation ;
	int		index;

	allocation = gc(sizeof(char) * (le_count(string) + 1), 0, 0, 0);
	index = 0;
	while (string[index] && string[index + 1])
	{
		allocation[index] = string[index];
		index++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}
