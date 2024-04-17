SRCS_MAND := get_path.c parse.c pipex.c utils.c heredoc.c
OBJS_MAND := $(SRCS_MAND:.c=.o)

SRCS_BONUS := fmt_s_bonus.c fmt_u_bonus.c fmt_x_bonus.c \
				fmt_c_bonus.c fmt_p_bonus.c fmt_d_bonus.c \
				ft_printf_helper_bonus.c ft_numtoa_bonus.c \
				ft_printf_bonus.c check_input_bonus.c inits_bonus.c
OBJS_BONUS := $(SRCS_BONUS:.c=.o)

LIBFT := src/libftprintf.a
CFLAGS := -Wall -Wextra -Werror -g

NAME := pipex

all: $(NAME)

ifdef WITH_BONUS
OBJS_LIST = $(OBJS_MAND) $(OBJS_BONUS)
else
OBJS_LIST = $(OBJS_MAND)
endif

$(NAME): $(LIBFT) $(OBJS_LIST)
	cc $(CFLAGS) $(OBJS_MAND) -o $@ -L./src -lftprintf
bonus: $(NAME)

clean:
	rm -f *.o

re: fclean
	make all

fclean: clean
	rm -f $(NAME)

.PHONY : all bonus clean fclean re
