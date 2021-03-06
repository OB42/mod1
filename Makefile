# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 10:47:39 by pcluchet          #+#    #+#              #
#    Updated: 2018/09/12 17:49:13 by pcluchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mod1

SRC_DIR = ./

CC = gcc

EXTRAFLAGS = -Ofast -Wall -Wextra -Werror #-fsanitize=address

CFLAGS = -I$(LIBFT_DIR)includes/ -I$(H_DIR) -I$(MLX_DIR) $(EXTRAFLAGS)

MLX_FLAGS = -framework OpenGL -framework AppKit

UTILS = mlx_utils.c \
line_utils.c \
color_utils.c \
parse_utils.c \
point_utils.c \

FILE = file_helper.c \
gen_map.c

POINTS = set_dots.c \
gen_point.c \
connect_dots.c \
draw_dot.c \
connect_water_dots.c

SCENARIOS = raining.c \
rising_water.c \
wave.c

WATER = spread_water.c \
gen_watermap.c \
ft_triangle.c \
spread_inside.c \
more_water.c \
watermap.c \
gen_current_elev_map.c

SRC = main.c \
line.c \
hook.c \
setters.c \
coef_inside.c \
coef_between.c \
bigmap.c

C_FILES = $(addprefix utils/, $(UTILS)) \
$(addprefix file/, $(FILE)) \
$(addprefix scenarios/, $(SCENARIOS)) \
$(addprefix points/, $(POINTS)) \
$(addprefix water/, $(WATER)) \
$(addprefix src/, $(SRC)) \

LIBFT_DIR = ./libft/

MLX_DIR = ./minilibx_macos/

O_FILES = $(C_WITH_PATH:.c=.o)

H_DIR = ./includes/

LINKS = -L $(MLX_DIR) -lmlx -L $(LIBFT_DIR) -lftprintf

C_WITH_PATH = $(addprefix $(SRC_DIR),$(C_FILES))

all : $(NAME)

$(NAME) : libs $(O_FILES)
	$(CC) -o $(NAME) $(O_FILES) $(CFLAGS) $(MLX_FLAGS) $(LINKS)

clean :
	rm -f $(O_FILES)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)libftprintf.a
	rm -f $(MLX_DIR)libmlx.a

re :
	$(MAKE) fclean
	$(MAKE) all

libs:
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)

.PHONY: all re clean fclean libs
