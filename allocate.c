#include "allocate.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*buffer;

	i = 0;
	buffer = (unsigned char *)b;
	while (i < len)
	{
		buffer[i] = c;
		i++;
	}
	return (buffer);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static void	*ft_calloc(size_t count, size_t size)
{
	void	*loc;
	size_t	bytes;

	loc = NULL;
	bytes = count * size;
	if (count != 0 && bytes / count != size)
		return (NULL);
	loc = malloc(bytes);
	if (!loc)
		return (NULL);
	ft_bzero(loc, bytes);
	return (loc);
}


static t_allocate	**block_loc(void)
{
	static t_allocate	*collec = NULL;

	return (&collec);
}

void	*allocate(size_t count, size_t size)
{
	t_allocate **collec;
	t_allocate	*new;

	collec = block_loc();
	new = malloc(sizeof(t_allocate));
	if (!new)
		return (NULL);
	new->block = ft_calloc(count, size);
	if (!new->block)
		return (free(new), NULL);
	(TRUE) && (new->next = *collec, *collec = new);
	return (new->block);
}

void	cleanup(void)
{
	t_allocate	*set;
	t_allocate	*next;
	t_allocate	**collec;

	collec = block_loc();
	set = *collec;
	while (set)
	{
		next = set->next;
		if (set->block)
			free(set->block);
		(free(set), set = next);
	}
	*collec = NULL;
}
