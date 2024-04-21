# SRCS_MAND := fmt_s.c fmt_u.c fmt_x.c \
# 				fmt_c.c fmt_p.c fmt_d.c \
# 				ft_printf_helper.c ft_numtoa.c \
# 				ft_printf.c check_input.c inits.c
# OBJS_MAND := $(SRCS_MAND:.c=.o)

SRCS_BONUS := fmt_s_bonus.c fmt_u_bonus.c fmt_x_bonus.c \
		fmt_c_bonus.c fmt_p_bonus.c fmt_d_bonus.c \
		ft_printf_helper_bonus.c ft_numtoa_bonus.c \
		ft_printf_bonus.c check_input_bonus.c inits_bonus.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS_BONUS := $(SRCS_BONUS:.c=.o)

LIBFT_DIR := ./libft
LIBFT := ./libft/libft.a
CFLAGS := -Wall -Wextra -Werror -g

NAME := libftprintf.a

all: $(NAME)

$(LIBFT):
ifeq (,$(wildcard $(LIBFT)))
	make -C $(LIBFT_DIR) all
endif

OBJS_LIST := $(OBJS_BONUS)

$(NAME): $(OBJS_LIST) $(LIBFT)
	cp $(LIBFT) ./$(NAME)
	ar crs $@ $(OBJS_BONUS)

bonus:
	make WITH_BONUS=1 all

clean:
	make -C $(LIBFT_DIR) clean
	rm -f *.o

re: fclean
	all

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
.PHONY : all bonus clean fclean re
