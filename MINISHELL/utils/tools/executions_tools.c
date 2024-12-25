/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:20 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 08:25:16 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	limit_check(char *string)
{
	if (!here_comp(string, ">>", 2))
		return (1);
	else if (!here_comp(string, ">", 1))
		return (1);
	else if (!here_comp(string, "<", 1))
		return (1);
	else if (!here_comp(string, "<<", 2))
		return (1);
	return (0);
}

void	close_fds(t_tree *leaf)
{
	int	i;

	i = -1;
	if (leaf->fd_in != 0)
		close(leaf->fd_in);
	if (leaf->here_fd != 0)
		close(leaf->here_fd);
	if (leaf->fd_out != 1)
		close(leaf->fd_out);
	while (leaf->tree_h->pipes[++i])
	{
		close(leaf->tree_h->pipes[i][0]);
		close(leaf->tree_h->pipes[i][1]);
	}
	i = -1;
	while (leaf->tree_h->fds[++i])
		close(leaf->tree_h->fds[i]);
}

int	last_part(char *tmp_2)
{
	DIR	*dir;

	dir = opendir(tmp_2);
	if (dir)
		return (print_error("is a diractory", tmp_2), \
		closedir(dir), gc(0, 2, 0, 126), 1);
	return (0);
}

char	*check_access(t_tree *leaf, t_th *tree_h, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp_2;

	i = -1;
	tmp_2 = cmd;
	if (!cmd || !cmd[0] || !ft_strcmp(cmd, ".."))
		return (print_error("command not found", cmd), \
		close_fds(leaf), gc(0, 2, 0, 127), NULL);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		return (last_part(cmd), cmd);
	cmd = ft_strjoin("/", cmd);
	(tree_h->path) && (tmp = ft_strjoin(tree_h->path[++i], cmd), 0);
	while (tree_h->path && i <= count_twode(leaf->tree_h->path) \
	&& access(tmp, X_OK) == -1)
	{
		tmp = ft_strjoin(tree_h->path[i], cmd);
		i++;
	}
	last_part(tmp_2);
	if (tree_h->path && i <= count_twode(leaf->tree_h->path))
		return (tmp);
	return (print_error("command not found", tmp_2), \
	close_fds(leaf), gc(0, 2, 0, 127), NULL);
}

char	**path_maker(char **env)
{
	char	**path;
	int		i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
	if (!ft_strncmp(env[i], "PATH=", 5))
	{
		path = ft_split(env[i], ':');
		path[0] = ft_strtrim(path[0], "PATH=");
		return (path);
	}
	return (NULL);
}
