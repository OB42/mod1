# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 10:47:39 by pcluchet          #+#    #+#              #
#    Updated: 2017/02/17 10:57:45 by pcluchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mod1

SRC_DIR = ./

CC = gcc

EXTRAFLAGS = -fsanitize=address#-Wall -Wextra -Werror

CFLAGS =  -I$(LIBFT_DIR)includes/  -I$(H_DIR) -I$(MLX_DIR) $(EXTRAFLAGS)

MLX_FLAGS = -framework OpenGL -framework AppKit

C_FILES = main.c \
get_color_by_altitude.c \
file_feed.c \
file_helper.c \
get_next_line.c \
color_utils.c \
engine.c \
hook.c \
mlx_utils.c \
line_utils.c \
point_utils.c \
parse_utils.c \
setters.c \
getters.c \
set_dots.c \
connect_dots.c

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
