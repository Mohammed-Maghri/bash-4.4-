/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:51:38 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:37:00 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_invalid(char string)
{
	if (string == ';' || string == '|' || string == '&')
		return (-1);
	if (string == '(' || string == ')' || string == '}')
		return (-1);
	if (string == '{' || string == ']' || string == '[')
		return (-1);
	if (string == '*' || string == '?' || string == '@')
		return (-1);
	if (string == '>' || string == '<' || string == '/' )
		return (-1);
	if (string == '(' || string == ')')
		return (-1);
	return (0);
}

int	loop_check(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (return_invalid(string[index]) == -1)
			return (-1);
		index++ ;
	}
	return (0);
}

char	**function_to_check(char **env, int here, char *put)
{
	int		index ;
	int		increment;
	char	**allocation ;

	increment = 0;
	index = 0;
	allocation = gc(sizeof(char **) *(count_twode(env) + 1), 0, 0, 0);
	while (env[index])
	{
		if (index != here)
			allocation[increment] = return_line(env[index]);
		else if (here == index)
			allocation[increment] = return_line(put);
		index++ ;
		increment = 0;
	}
	allocation[increment] = NULL ;
	return (allocation);
}

int	check_exist_in_env(char *value, char **env)
{
	int	index ;

	index = 0;
	if (count_twode(env) < 1)
		return (-1);
	while (env[index])
	{
		if (le_count(copy_till_charac(env[index], '=')) == le_count(value))
		{
			if (check_function_compare(copy_till_charac(env[index], '='), \
			value) == 0)
				return (index);
		}
		index++ ;
	}
	return (-1);
}

char	*copy_after_find(char *string, char here)
{
	int		index ;
	int		increment;
	char	*allocation ;

	increment = 0;
	index = 0;
	allocation = gc(sizeof(char *) *(le_count(string) + 1), 0, 0, 0);
	if (string == NULL)
		return ("");
	while (string[index])
	{
		if (string[index] == here)
			break ;
		index++ ;
	}
	index++ ;
	while (index <= le_count(string))
	{
		allocation[increment] = string[index];
		increment++ ;
		index++ ;
	}
	allocation[increment] = '\0';
	return (allocation);
}
