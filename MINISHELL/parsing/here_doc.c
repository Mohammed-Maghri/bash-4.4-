/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:23:27 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 15:02:26 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int		g_signal_received;

void	function_handler(int sign)
{
	if (sign == SIGINT)
	{
		close(0);
		g_signal_received = 1;
		exit_status(1, 0);
	}
}

int	start_here_doc(char *del, char **env, int fd, int *bool)
{
	char	zero;
	char	*in;

	zero = my_dup(0);
	while (!g_signal_received && 1)
	{
		in = readline("here_> ");
		if (!in)
			break ;
		if (!here_comp(in, del, ft_strlen(del)))
		{
			free(in);
			break ;
		}
		put_tmp(in, fd, env, *bool);
		free(in);
	}
	return (my_dup2(zero, 0), close(zero), 0);
}

char	*set_delimiter(t_list **tmp_2, int *bool)
{
	t_list	*tmp;
	char	*res;

	tmp = (*tmp_2);
	res = gc(1, 0, 0, 0);
	res[0] = 0;
	while (tmp && (compare(tmp, WORD) \
	|| compare(tmp, D_QU) || compare(tmp, S_QU) \
	|| compare(tmp, DOLLAR)))
	{
		if (compare(tmp, DOLLAR) && (tmp->next && \
		(compare(tmp->next, D_QU) \
		|| compare(tmp->next, S_QU))))
			tmp = tmp->next;
		is_quotes(tmp->content, bool);
		if (compare(tmp, D_QU) || compare(tmp, S_QU))
			join_quotes(&tmp);
		res = ft_strjoin(res, delete_opening_quotes(tmp->content, \
		what_qoutes(tmp->content)));
		tmp = tmp->next;
	}
	return (res);
}

int	open_here_doc(t_list *tmp)
{
	char	*name;
	int		fd;
	int		i;

	i = 0;
	name = ft_substr(".here_doc", 0, 9);
	while (!access(name, F_OK))
		name = ft_strjoin(name, ft_itoa(++i));
	fd = open(name, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		return (print_error("Error in here_doc", NULL), \
		gc(0, 2, 0, 1), 1);
	gc(fd, 3, 1, 0);
	tmp->fd_in = open(name, O_RDWR);
	if (tmp->fd_in == -1)
		return (unlink(name), print_error("Error in here_doc", NULL), \
		gc(0, 2, 0, 0), 1);
	gc(tmp->fd_in, 3, 1, 0);
	unlink(name);
	return (fd);
}

int	run_here_doc(t_list *tmp, char **env)
{
	char	*del;
	int		fd;
	int		bool;

	fd = 0;
	bool = 0;
	tmp = tmp->next;
	if (((!compare(tmp, SPACEE) && !compare(tmp, WORD) && \
	!compare(tmp, D_QU)) && !compare(tmp, S_QU) && \
	!compare(tmp, DOLLAR)) || (compare(tmp, SPACEE) && \
	!compare(tmp->next, WORD) && !compare(tmp->next, D_QU) \
	&& !compare(tmp->next, S_QU) && !compare(tmp->next, DOLLAR)))
		return (print_error("syntax error", NULL), 1);
	fd = open_here_doc(tmp->prev);
	if (tmp->token_type == SPACEE)
		tmp = tmp->next;
	del = set_delimiter(&tmp, &bool);
	signal(SIGINT, function_handler);
	start_here_doc(del, env, fd, &bool);
	signal(SIGINT, signals_handler);
	if (wait_for_here_doc(5))
		return (close(fd), wait_for_here_doc(0), 1);
	return (close(fd), 0);
}
