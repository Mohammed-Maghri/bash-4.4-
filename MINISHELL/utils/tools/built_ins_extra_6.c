/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:19:34 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:41:45 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_this_end(char *string, char *compare)
{
	int	index;
	int	increment;
	int	flag;

	flag = 0;
	increment = le_count(compare);
	index = le_count(string);
	if (increment <= index)
	{
		index-- ;
		increment-- ;
		while (increment > -1)
		{
			if (string[index] == compare[increment])
				flag++ ;
			increment--;
			index-- ;
		}
		if (flag == le_count(compare))
			return (-1);
	}
	return (0);
}

char	**check_both(char **all_in, char *string)
{
	int		index ;
	char	**allocation ;
	int		increment ;

	increment = 0;
	allocation = gc((sizeof(char *) * (count_twode(all_in) + 1)), 0, 0, 0);
	index = 0;
	while (all_in[index])
	{
		if (check_this_end(all_in[index], string) == -1)
		{
			allocation[increment] = all_in[index];
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = NULL;
	return (allocation);
}

char	**keep_only_what_to_start_find(char **res_type, char *start)
{
	int		index ;
	int		increment ;
	char	**allocation;

	increment = 0;
	index = 0;
	allocation = gc((sizeof(char *) * (count_twode(res_type) + 1)), 0, 0, 0);
	while (res_type[index])
	{
		if (check_this_start(res_type[index], start) == -1)
		{
			allocation[increment] = return_line(res_type[index]);
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = NULL ;
	return (allocation);
}

char	**check_sides(char **all_in, char *string, char *last_string)
{
	int		index ;
	char	**allocation ;
	int		increment ;

	increment = 0;
	allocation = gc((sizeof(char *) * (count_twode(all_in) + 1)), 0, 0, 0);
	index = 0;
	while (all_in[index])
	{
		if (check_this_end(all_in[index], last_string) == -1 \
		&& check_this_start(all_in[index], string) == -1)
		{
			allocation[increment] = all_in[index];
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = NULL;
	return (allocation);
}

char	**check_in_every(char **all_in, char *string)
{
	int		index ;
	char	**allocation ;
	int		increment ;

	increment = 0;
	allocation = gc((sizeof(char *) * (count_twode(all_in) + 1)), 0, 0, 0);
	index = 0;
	while (all_in[index])
	{
		if (search_inside(all_in[index], string) == -1)
		{
			allocation[increment] = all_in[index];
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = NULL;
	return (allocation);
}
