/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_again_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:20 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:36:33 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_line(char *string)
{
	int		index ;
	char	*allocation ;

	index = 0;
	allocation = gc(sizeof(char *) * (le_count(string) + 1), 0, 0, 0);
	while (string[index] && string[index] == ' ' && le_count(string) > 2)
		index++ ;
	while (string[index])
	{
		allocation[index] = string[index];
		index++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}

int	check_function_compare(char *string, char *check)
{
	int	index ;
	int	flag;

	flag = 0;
	index = 0;
	if (le_count(string) != le_count(check))
		return (-1);
	while (string[index])
	{
		if (string[index] == check[index])
			flag++ ;
		index++ ;
	}
	if (flag == le_count(check))
		return (0);
	return (-1);
}

int	search_in_for(char *string, char search)
{
	int	index ;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
	{
		if (string[index] == search)
			return (1);
		index++ ;
	}
	return (0);
}

char	**add_it_to_env_index(char **env, char *string, int here)
{
	char	**allocation;
	int		index ;

	index = 0;
	allocation = gc(sizeof(char **) * (count_twode(env) + 3), 0, 0, 0);
	while (env[index])
	{
		if (index == here)
			allocation[index] = return_line(string);
		else
			allocation[index] = return_line(env[index]);
		index++ ;
	}
	allocation[index] = NULL ;
	return (allocation);
}

char	**add_it_to_env(char **env, char *string)
{
	int		index ;
	char	**allocation;

	allocation = gc(sizeof(char **) * \
	((count_twode(env) + 3) + (le_count(string) + 1)), 0, 0, 0);
	index = 0;
	if (!allocation)
		return (NULL);
	if (!env)
	{
		allocation[index] = return_line(string);
		index++ ;
		allocation[index] = NULL ;
		return (allocation);
	}
	while (env[index])
	{
		allocation[index] = return_line(env[index]);
		index++ ;
	}
	allocation[index] = return_line(string);
	index++ ;
	allocation[index] = NULL ;
	return (allocation);
}
