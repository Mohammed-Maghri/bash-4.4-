/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:00:47 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:41:20 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*merge_till_end(char **twode)
{
	int		index;
	int		increment ;
	int		up ;
	char	*allocation;

	up = 0;
	increment = 0;
	index = 0;
	allocation = gc(sizeof(char **) * (count_twode(twode) + 3), 0, 0, 0);
	while (twode[index])
	{
		while (twode[index][increment])
		{
			allocation[up] = twode[index][increment];
			up++;
			increment++;
		}
		allocation[up] = ' ';
		up++;
		increment = 0;
		index++;
	}
	allocation[up] = '\0';
	return (allocation);
}

int	count_twode(char **string)
{
	int	index ;

	index = 0;
	if (!string)
		return (0);
	while (string[index] != NULL)
		index++;
	return (index);
}

char	**printf_export_declared(char **env)
{
	int		index ;
	char	**allocation;
	char	*string ;

	string = "declare -x";
	index = 0;
	allocation = gc(sizeof(char **) * \
	((count_twode(env)) + (le_count(string + 1))), 0, 0, 0);
	if (!allocation)
		return (NULL);
	while (env[index])
	{
		allocation[index] = merge_both(string, env[index]);
		index++;
	}
	allocation[index] = NULL;
	return (allocation);
}

void	put_twode(char **string)
{
	int	index ;

	index = 0;
	while (string[index])
	{
		putstr(string[index]);
		paste('\n');
		index++;
	}
}

void	adress_unset(int *flag, int *increment, int *index, int cap)
{
	if (cap == -1)
	{
		*increment = 0;
		*index = 0;
		*flag = 0;
	}
	else if (cap == 0)
	{
		*flag = 0;
		*increment = 0;
		*index += 1;
	}
}
