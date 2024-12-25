/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:43:46 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:22 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strtrim(char *s1, char *s2)
{
	size_t	start;
	size_t	end;
	size_t	newlen ;

	start = 0;
	if (!s1 || !s2)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(s2, s1[start]))
		start++ ;
	while (start < end && ft_strchr(s2, s1[end]))
		end-- ;
	newlen = end - start + 1;
	return (ft_substr(s1, start, newlen));
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (start + len > (unsigned int)ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	sub = gc(len + 1, 0, 0, 0);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
