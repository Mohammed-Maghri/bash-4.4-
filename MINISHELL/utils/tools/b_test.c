/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:53:25 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/23 18:11:02 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	loop_on_all(char *string, int check)
{
	int	index ;

	index = 0;
	if (string[0] == '=')
		return (-1);
	while (string[index])
	{
		if (check == 0)
		{
			if (string[index] == '\'' || string[index] == '\"')
				return (-1);
		}
		if (check_if_it_valid(string[0]) == -1)
			return (-1);
		if (one_check(string[index]) == -1)
			return (-1);
		index++ ;
	}
	return (0);
}

int	on_all(char *string, int check)
{
	int	index ;

	index = 0;
	if (string[0] == '=')
		return (-1);
	while (string[index])
	{
		if (check == 0)
		{
			if (string[index] == '\'' || string[index] == '\"')
				return (-1);
		}
		if (check_if_it_valid(string[0]) == -1)
			return (-1);
		if (sec_check(string[index]) == -1)
			return (-1);
		index++ ;
	}
	return (0);
}

int	get_position(char *string, char chara)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == chara)
			break ;
		index++ ;
	}
	return (index);
}

int	only_for_you_plus(char *string)
{
	int	pos;

	if (search_in_for(string, '+') == 1)
	{
		pos = get_position(string, '+');
		if (string[0] == '+')
			return (-1);
		if ((string[pos + 1] != '=') || (string[pos - 1] == ' ' \
		|| string[pos - 1] == '\t'))
			return (-1);
	}
	return (0);
}

int	check_quotes_only(char *string)
{
	char	*it_here ;

	if (!string[0])
		return (print_error("not a valid identifier", NULL), \
			here_para(0), here_para(1), -1);
	it_here = only_for_one_of_this_add(string, '=');
	if (loop_on_all(it_here, 1) == -1 || only_for_you_plus(it_here) == -1)
		return (print_error("not a valid identifier", NULL), \
			here_para(0), here_para(1), -1);
	return (0);
}
