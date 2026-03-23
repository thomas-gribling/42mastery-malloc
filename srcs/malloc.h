#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

#include <stdio.h> // pour les tests

#define TINY_MAX_BYTES 64 // 1 - 64B
#define TINY_ZONE_SIZE getpagesize() * 16 // 64KB
#define MED_MAX_BYTES 512 // 65 - 512B
#define MED_ZONE_SIZE getpagesize() * 128 // 512KB

typedef struct s_block
{
	size_t	size;
	int	free;
	struct s_block	*next;
}	t_block;

typedef struct s_zone t_zone;
typedef struct s_zone
{
	size_t	size;
	t_block *blocks;
	t_zone	*next; // seulement pour le large
}	t_zone;

extern t_zone *z_tiny;
extern t_zone *z_med;
extern t_zone *z_big;

void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);

void	show_alloc_mem();