/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_function_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:44:33 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:36:47 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_white(char string)
{
	if (string == ' ')
		return (-1);
	else if (string == '\t')
		return (-1);
	else if (string >= 9 && string <= 13)
		return (-1);
	else if (string == '\0')
		return (-1);
	return (0);
}

char	*copy_for_remove_string(char *allocation, char *string)
{
	t_all_vars	copy;

	copy.increment = 0;
	copy.index = 0;
	while (string[copy.index])
	{
		allocation[copy.increment] = string[copy.index];
		copy.increment++ ;
		copy.index++ ;
	}
	allocation[copy.increment] = '\0';
	return (allocation);
}

char	*remove_string(char *string, char *to_move)
{
	t_all_vars	rem;

	rem.increment = 0;
	rem.index = 0;
	rem.allocation = gc(sizeof(char **) * \
	((le_count(string) + 1) + (le_count(to_move) + 1)), 0, 0, 0);
	while (string[rem.index] && all_white(string[rem.index]) == -1)
		rem.index++ ;
	if (string[rem.index] == to_move[0])
	{
		rem.index++ ;
		rem.increment++ ;
		while (string[rem.index] == to_move[rem.increment])
		{
			rem.index++ ;
			rem.increment++ ;
		}
	}
	rem.increment = 0;
	if (string[rem.index + 1] != '\0')
		rem.allocation = copy_for_remove_string(rem.allocation, \
		&string[rem.index]);
	return (rem.allocation);
}

char	*only_for_one_of_this_add(char *string, char to_here)
{
	t_all_vars	till;
	int			flag;

	till.index = 0;
	flag = 0;
	till.allocation = gc(sizeof(char **) * \
	(le_count(string) + 3), 0, 0, 0);
	while (string[till.index])
	{
		if (string[till.index] == to_here)
		{
			flag = 1;
			till.allocation[till.index] = string[till.index];
			till.index++ ;
			break ;
		}
		till.allocation[till.index] = string[till.index];
		till.index++ ;
	}
	if (flag == 1)
	{
		till.allocation[till.index] = '\0';
		return (till.allocation);
	}
	return (string);
}

char	*only_for_one_of(char *string, char to_here)
{
	t_all_vars	till;
	int			flag;

	till.index = 0;
	flag = 0;
	till.allocation = gc(sizeof(char **) * \
	(le_count(string) + 3), 0, 0, 0);
	while (string[till.index])
	{
		if (string[till.index] == to_here)
		{
			flag = 1;
			break ;
		}
		till.allocation[till.index] = string[till.index];
		till.index++ ;
	}
	if (flag == 1)
	{
		till.allocation[till.index] = '\0';
		return (till.allocation);
	}
	return (string);
}
