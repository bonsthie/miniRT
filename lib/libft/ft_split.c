/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:48:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counts(const char *str, const char sep)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			word++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (word);
}

static int	strlen_split(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static void	free_all(char **strs, int word_count)
{
	while (word_count)
		free(strs[word_count--]);
	free(strs);
}

static void	create_token(char **token, const char *s, int word_count, char c)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	while (++i < word_count)
	{
		j = 0;
		while (s[k] && s[k] == c)
			k++;
		token[i] = malloc((strlen_split(&s[k], c) + 1) * sizeof(char));
		if (!token[i])
		{
			free_all(token, word_count);
			return ;
		}
		while (s[k] && s[k] != c)
			token[i][j++] = s[k++];
		token[i][j] = 0;
	}
	token[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = word_counts(s, c);
	if (word_count == 0)
		return (NULL);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	create_token(result, s, word_count, c);
	return (result);
}
