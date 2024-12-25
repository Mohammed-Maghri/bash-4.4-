/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/03/29 01:27:25 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dollar_merge(t_list **tmp, int token_type)
{
	t_list	*tmp_2;

	tmp_2 = (*tmp);
	tmp_2 = tmp_2->next;
	while (tmp_2 && tmp_2->token_type != token_type)
		tmp_2 = tmp_2->next;
	(*tmp)->next = tmp_2;
}

int	compare(t_list *tmp, int token)
{
	if (!tmp)
		return (0);
	if (tmp->token_type == token)
		return (1);
	return (0);
}

void	put_tmp(char *in, int fd, char **env, int bool)
{
	int	i;

	i = -1;
	if (!bool)
		in = expand_factory(in, env, NULL, 1);
	while (in[++i])
		write(fd, &in[i], 1);
	write(fd, "\n", 1);
}

void	is_quotes(char *string, int *bool)
{
	int	i;

	i = -1;
	while (string[++i])
		if (string[i] == '\'' || string[i] == '\"')
			*bool = 1;
}
