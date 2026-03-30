<h1 align="center">
        malloc
</h1>

<p align="center">
        <i>42 mastery</i><br>
        Final grade: <b>awaiting correction</b>
</p>

# 📝 Subject
This project consists in recoding the fuctions `malloc`, `realloc` and `free` from the `<stdlib.h>` library. They must be prototyped like the original ones:<br>
```c
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
```
With the use of `mmap` and `munmap` fuctions, we are able to allocate memory zones of specific sizes, which means this project aims to teach us how to organize and manipulate memory ourselves.

We must separate our memory intro three zones, *tiny*, *medium* and *large*. Each zone will have a predefinite size, and a fork of allocation size it can accept. Our functions must automatically manage these zones, and we must define their limit so that at least 100 mallocs can be done per zone. The *large* zone doesn't have any limit, it will accept every malloc above the limit of the *medium* zone.

Since our memory management is not like a real one, `valgrind`, used to see memory allocatated with malloc, will be pointless. Instead, we have to code our own display fuction:<br>
```c
void	show_alloc_mem();
```
It will display the allocated memory blocks in each zones as followed:<br>
```bash
TINY : 0x7f7ec0d1a000
0x7f7ec0d1a030 - 0x7f7ec0d1a037 : 8 bytes
MEDIUM : 0x7f7ec0aa1000
0x7f7ec0aa1030 - 0x7f7ec0aa1137 : 264 bytes
LARGE : 0x7f7ec0d5e000
0x7f7ec0d5e030 - 0x7f7ec0d5e837 : 2056 bytes
Total : 2328 bytes
```

# 🖥️ Usage
First of all, the library must be compiled using `make`, this will create a dynamic library and a symbolik link to it named `libft_malloc.so`.<br>
To use that library, simply include its header `malloc.h` in a C file, and compile it with it, using the following command:<br>
```bash
gcc -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc main.c -L. -lft_malloc -Wl,-rpath=.
```