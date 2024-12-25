/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:53:32 by mmaghri           #+#    #+#             */
/*   Updated: 2024/03/14 14:50:46 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_string(char *string, char *what_to_compare)
{
	int	index ;
	int	increment ;
	int	flag ;

	flag = 0;
	increment = 0;
	index = 0;
	while (string[index])
	{
		if (le_count(what_to_compare) == increment)
			break ;
		if (string[index] == what_to_compare[increment])
			flag++ ;
		index++ ;
		increment++;
	}
	if (flag == le_count(what_to_compare))
		return (0);
	return (-1);
}
