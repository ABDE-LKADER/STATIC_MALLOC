#ifndef MYLIB_H
# define MYLIB_H

# include <stdlib.h>

///////////////// HEAP_CLEANER /////////////////

# define TRUE 1

typedef struct s_allocate
{
	void				*block;
	struct s_allocate	*next;
}						t_allocate;

void	cleanup(void);
void	*allocate(size_t count, size_t size);

#endif
