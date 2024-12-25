/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_again_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:40:00 by mmaghri           #+#    #+#             */
/*   Updated: 2024/03/14 14:41:57 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**put_check_env(char *check, char *value, char **env)
{
	int		index ;
	char	**allocation ;

	index = 0;
	allocation = env;
	if (le_count(check) == 6)
	{
		if (check_function_compare(check, "export") == -1)
			return (NULL);
		else if (value)
		{
			if (check_if_in_env(env, value) == 0)
				return (env);
			while (value[index] && (search_in_for(value, '=') == 1))
			{
				allocation = add_it_to_env(env, value);
				break ;
			}
			return (allocation);
		}
	}
	return (env);
}
