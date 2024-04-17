#include "libft.h"

static size_t	ccc(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s !=c && *s != 0)
	{
		s++;
		i++;
	}
	return (i);
}

static size_t	count_wordss(char const *s, char c)
{
	char const	*ps;
	size_t	num_words;

	ps = s;
	num_words = 0;
	while (*ps)
	{
		if (*ps == c)
			ps++;
		else
		{
			num_words++;
			while (*ps != c && *ps)
				ps++;
		}
	}
	return (num_words);
}

static void	ft_mmmmemcpy(char *dst, char const *src, size_t srclen)
{
	// dst[srclen] = 0;
	while (srclen--)
	{
		dst[srclen] = src[srclen];
	}

}

static void	free_function(char **ret_val, size_t i)
{
	while(i != 0)
		free(ret_val[i--]);
	free(ret_val);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	strlen;
	size_t	num_words;
	char	**ret_val;

	i = 0;
	num_words = count_wordss(s, c);
	ret_val = malloc(sizeof(char *) * num_words + 1);
	if (ret_val == NULL)
		return (NULL);
	ret_val[num_words] = NULL;
	while (i < num_words)
	{
		while (*s && *s == c)
			s++;
		strlen = ccc(s, c);
		ret_val[i] = malloc(strlen + 1);
		if (ret_val[i] == NULL)
		{
			free_function(ret_val, i);
			return(NULL);
		}
		ft_mmmmemcpy(ret_val[i], s, strlen);
		ret_val[i][strlen] = 0;
		i++;
		s += strlen + 1;
	}
	ret_val[num_words] = 0;
	return (ret_val);
}