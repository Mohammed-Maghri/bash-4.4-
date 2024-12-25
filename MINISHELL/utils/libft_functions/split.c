/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:45:22 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:42 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_countlength_n(char *s, char c)
{
	int	i;
	int	nws;

	i = 0;
	nws = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			nws++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (nws);
}

int	ft_eachlength_n(char *s, char c, int	*p)
{
	int	l;

	l = 0;
	while (s[*p] && s[*p] == c)
		*p += 1;
	while (s[*p])
	{
		if (s[*p] == c)
			break ;
		else
		{
			l++;
			*p += 1;
		}
	}
	return (l);
}

int	ft_allocat_n(char **str, char *s, int nwss, char c)
{
	int		eachlength;
	int		p;
	int		i;

	i = 0;
	p = 0;
	while (nwss != 0 && i < nwss)
	{
		eachlength = ft_eachlength_n((char *)s, c, &p);
		str[i] = ft_substr(s, (p - eachlength), eachlength);
		i++;
	}
	str[i] = 0;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		nwss;

	nwss = ft_countlength_n((char *)s, c);
	str = gc((nwss + 1) * sizeof(char *), 0, 0, 0);
	ft_allocat_n(str, (char *)s, nwss, c);
	return (str);
}
