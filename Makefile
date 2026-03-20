ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAMELINK = libft_malloc.so

SRCS = srcs/

CC = gcc
CFLAGS = -fPIC -Iinclude
LDFLAGS = -shared

FILES = malloc.c show_alloc_mem.c
OBJECTS = $(addprefix $(SRCS), $(FILES:.c=.o))

%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	ln -sf $(NAME) $(NAMELINK)

clean:
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAMELINK)

re: fclean all