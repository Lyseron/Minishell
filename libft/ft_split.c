/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:35:36 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/11 15:35:36 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_bail(char **tab, size_t word)
{
	while (word > 0)
	{
		free(tab[word - 1]);
		word--;
	}
}

static int	fill_tab(char const *s, char c, char **tab)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			return (0);
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		tab[i] = malloc(sizeof(char) * ((end - start) + 1));
		if (!tab[i])
			return (free_bail(tab, i), -1);
		ft_strlcpy(tab[i], s + start, end - start + 1);
		start = end;
		i++;
	}
	return (1);
}

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count_word;

	count_word = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || (s[i - 1] == c)) && (s[i] != c))
			count_word++;
		i++;
	}
	return (count_word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nb_of_word;

	nb_of_word = word_count(s, c);
	tab = malloc(sizeof(char *) * (nb_of_word + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(s, c, tab) == -1)
	{
		free(tab);
		return (NULL);
	}
	tab[nb_of_word] = NULL;
	return (tab);
}

// int	main(void)
// {
// 	char s[] = "lili/est/super";
// 	char c = '/';
// 	char **tab = ft_split(s, c);
// 	int i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }