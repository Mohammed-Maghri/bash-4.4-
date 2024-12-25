/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 23:14:38 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:37:14 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_new(char	**new, char	**content, char *tmp, t_pt *bool)
{
	new[bool->e_bool++] = ft_substr(tmp, 0, ft_strlen(tmp));
	if (content[bool->d_bool])
		new[bool->e_bool++] = ft_substr(content[bool->d_bool], 0, \
		ft_strlen(content[bool->d_bool]));
}

void	if_export(char	**content, t_pt	*bool)
{
	if (!here_comp("export", delete_opening_quotes(content[0], \
	what_qoutes(content[0])), 7))
		bool->s_bool = 1;
}

char	*cut_star(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (string[i])
	{
		if (string[i] == '*')
		{
			j = i - 1;
			while (string[++j] && string[j] == '*')
				;
			string = cut_string(string, i++, j);
		}
		else
			i++;
	}
	return (string);
}

int	search_inside(char *string, char *what_to)
{
	int	index;
	int	increment;
	int	flag ;

	flag = 0;
	increment = 1;
	index = 0;
	if (le_count(string) >= le_count(what_to))
	{
		while (string[index])
		{
			if (string[index] == what_to[0])
			{
				index++ ;
				while (string[index] && string[index] == what_to[increment])
					incrementt(&flag, &index, &increment);
				if (flag == le_count(what_to) - 1)
					return (-1);
			}
			index++ ;
		}
	}
	return (0);
}

char	**add_to_content(char **wild, char **content, int index)
{
	char	**new_cont;
	int		i;
	int		j;

	i = count_twode(wild);
	j = count_twode(content);
	new_cont = gc(sizeof(char *) * ((i + (i - 1)) + j + 1), 0, 0, 0);
	i = -1;
	while (++i < index)
		new_cont[i] = content[i];
	j = -1;
	while (wild[++j])
	{
		new_cont[i++] = wild[j];
		if (wild[j + 1])
			new_cont[i++] = ft_substr(" ", 0, 1);
	}
	j = index;
	while (content[++j])
		new_cont[i++] = content[j];
	return (new_cont[i] = NULL, new_cont);
}
