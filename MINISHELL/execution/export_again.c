/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_again.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:37 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:36:37 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_in_env(char **env, char *value)
{
	int	index ;

	index = 0;
	while (env[index])
	{
		if (le_count(copy_till_charac(value, '=')) == \
		le_count(copy_till_charac(value, '=')) \
		&& check_string(value, env[index]) == 0)
		{
			if (check_string(env[index], value) == 0)
				return (0);
		}
		index++ ;
	}
	return (-1);
}

int	function_count_till(char *string, char till)
{
	int	index ;

	index = 0 ;
	while (string[index])
	{
		if (string[index] == till)
			break ;
		index++ ;
	}
	return (index);
}

void	print_var_name(char **env, char *string)
{
	int	index ;
	int	increment ;
	int	total ;

	total = 0;
	increment = 0;
	index = 0;
	while (env[index])
	{
		while (env[index][increment] && (search_in_for(env[index], '=') == 1))
		{
			if ((function_count_till(env[index], '=') - 1) == le_count(string))
			{
				total = function_count_till(string, '=');
				while (env[total])
				{
					printf("%s", env[total]);
					total++ ;
				}
			}
		}
		index++ ;
	}
}

char	*check_if_already(char *string, char *value )
{
	int		index ;
	int		increement;
	char	*allocation;

	index = 0;
	increement = 0;
	allocation = gc(sizeof(char *) * \
	((le_count(string) + 2) + (le_count(string) + 2)), 0, 0, 0);
	while (string[index] != '=')
	{
		allocation[index] = string[index];
		index++ ;
	}
	while (value[increement])
	{
		allocation[index] = string[increement];
		index++ ;
		increement++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}

int	return_before_equal(char *value, char **env, char *all_this)
{
	t_all_not_vars	t;

	if (!value)
		return (0);
	(void)all_this;
	t.index = 0;
	t.increment = 0;
	t.flag = 0;
	t.total = le_count(value);
	while (env[t.index])
	{
		while (value[t.increment] && t.increment \
		< t.total && env[t.index][t.increment])
		{
			if (env[t.index][t.increment] == value[t.increment])
				t.flag++ ;
			t.increment++ ;
		}
		if (t.flag == le_count(value))
			return (t.index);
		t.flag = 0;
		t.increment = 0;
		t.index++ ;
	}
	return (-1);
}
