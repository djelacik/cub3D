NAME = libgetnextline.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SOURCES = get_next_line.c get_next_line_utils.c
BONUS_SOURCES = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
