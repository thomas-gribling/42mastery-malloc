#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

#define TINY_MAX_BYTES 256 // 8B - 256B
#define TINY_ZONE_SIZE getpagesize() * 16 // 64KB
#define MED_MAX_BYTES 2048 // 264B - 2048B
#define MED_ZONE_SIZE getpagesize() * 128 // 512KB

typedef struct s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
}					t_block;

typedef struct s_zone
{
	size_t			size;
	t_block 		*blocks;
	struct s_zone	*next; // seulement pour la zone large
}					t_zone;

// Zones (seule global autorisee)
extern t_zone *zo[3];

// Prototypes du sujet
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem();

// Utils
int		is_zone_empty(t_zone *zone);
int		is_allocated(void *ptr);

void	ft_putstr(char *s);
void	ft_putsize(size_t size);
void	ft_putaddress(unsigned long address, int first);