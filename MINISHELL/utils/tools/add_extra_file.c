/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_extra_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:48:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/27 15:42:17 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_how(char *string, char this)
{
	int	index ;
	int	flag;

	flag = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == this)
			flag++ ;
		index++ ;
	}
	return (flag);
}

int	check_only_digit(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (if_else(string[index]) == -1)
			return (-1);
		if (count_how(string, '+') > 1)
			return (-1);
		index++ ;
	}
	return (0);
}

void	funcrtion_this_exit(t_tree *leaf)
{
	if (count_twode(leaf->content) > 1)
	{
		if (check_only_digit(leaf->content[2]) == -1)
		{
			print_error("numeric argument required", leaf->content[2]);
			(exit_status(255, 0), \
			gc(0, 2, 0, exit_status(0, 1)));
		}
		else if (count_twode(leaf->content) == 3)
		{
			exit_status((convert_number(leaf->content[2]) % 256), 0);
			(!leaf->is_in_pipe) && (printf("exit"));
			gc(0, 2, 0, exit_status(0, 1));
		}
		else
		{
			print_error("exit: too many arguments", NULL);
			(here_para(0), here_para(1), exit_status(1, 0));
		}
	}
	else
	{
		(!leaf->is_in_pipe) && (printf("exit"), 0);
		gc(0, 2, 0, 0);
	}
}

int	check_this_start(char *string, char *compare)
{
	int	index ;
	int	flag ;

	flag = 0;
	index = 0;
	while (compare[index])
	{
		if (compare[index])
		{
			if (string[index] == compare[index])
				flag++ ;
		}
		index++ ;
	}
	if (flag == le_count(compare))
		return (-1);
	return (0);
}

int	sec_check(char string)
{
	if (string == '|' || string == '*' || string == ' ' \
	|| string == '{' || string == '}' || string == '+' )
		return (-1);
	if (string == '-' || string == '&' || string == '^' \
	|| string == '\'' || string == '#')
		return (-1);
	if (string == '/' || string == '~' || string == ':' || string == '\t')
		return (-1);
	if (string == ';' || string == '|' || string == '@' || string == '$')
		return (-1);
	if (string == '!' || string == '?' || string == '\"' || string == ',')
		return (-1);
	if (string == '%' || string == '(' || string == ')' \
	|| string == '.' || string == '\\' || string == '=')
		return (-1);
	return (0);
}
