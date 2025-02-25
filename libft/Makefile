INCLUDES = -I../includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

AR = ar rcs

NAME = libft.a

EXECUTABLE = libft

HEADER = ../includes/libft.h

#sources calls the source codes
SOURCES = ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isspace.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strncmp.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putstr_fd.c \
		  ft_putnbr_fd.c \
		  ft_strrchr.c \
		  int_overflows.c \
		  has_duplicates.c \
		  get_next_line.c \
		  ft_atoi_base.c \
		  ft_strcmp.c \
		  ft_strndup.c \

#b_sources calls the bonus source codes
B_SOURCES = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			gc_alloc/gc_alloc.c \
			gc_alloc/gc_itoa.c \
			gc_alloc/gc_next_line.c \
			gc_alloc/gc_split.c \
			gc_alloc/gc_strdup.c \
			gc_alloc/gc_strjoin.c \
			gc_alloc/gc_substr.c \
			gc_alloc/gc_calloc.c \
			gc_alloc/gc_strndup.c \
			gc_alloc/gc_lstnew.c \
			vector/vec_new.c \
			vector/vec_free.c \
			vector/vec_resize.c \
			vector/vec_push.c \
			vector/vec_get.c

#objects calls the .o equivalent of the sources.c files
OBJECTS = $(SOURCES:.c=.o)

#b_objects calls the .o equivalent of the b_sources.c files
B_OBJECTS = $(B_SOURCES:.c=.o)

#all is libft.a
all: $(NAME)

#exe is libft
exe: $(EXECUTABLE)

#bonus is dot bonus
bonus: .bonus

#.bonus calls libft.a and all of the bonus objects
.bonus: $(NAME) $(B_OBJECTS)
	$(AR) $(NAME) $(B_OBJECTS)
	@touch .bonus

#libft.a calls all of the mandatory objects
$(NAME): $(OBJECTS)
	$(AR) $@ $?

#executable calls all of the mandatory objects
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking object files, creating executable"
	cc $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

#any object calls its equivalent source code
%.o: %.c
	cc $(CFLAGS) -c $< -o $@

#clean removes all objects, and the .bonus file
clean:
	rm -f $(OBJECTS) $(B_OBJECTS) .bonus

#fclean calls clean, and removes the executable and libft.a
fclean: clean
	rm -f $(EXECUTABLE) $(NAME)

#re calls fclean all, all calls name, name is libft.a
re: fclean all

.PHONY: all clean fclean re bonus exe
