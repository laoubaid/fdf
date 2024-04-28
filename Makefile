# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:40:25 by laoubaid          #+#    #+#              #
#    Updated: 2024/04/25 04:22:24 by laoubaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./mandatory/
SRC_DIR_BONUS = ./bonus/

NAME = fdf
NAME_BONUS = fdf_bonus

CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz


C_FILE = main.c map.c map_utils.c hex.c ft_split.c hooks.c gets.c \
	draw.c mlx_utils.c drawline.c drawline_utils.c rotation.c ft_strjoin.c

C_FILE_BONUS = main_bonus.c map_bonus.c map_utils_bonus.c hex_bonus.c \
	additionals_bonus.c ft_split_bonus.c hooks_bonus.c gets_bonus.c \
	draw_bonus.c mlx_utils_bonus.c drawline_bonus.c drawline_utils_bonus.c\
	rotation_bonus.c ft_itoa_bonus.c color_bonus.c


SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))
SRC_BONUS	=	$(addprefix $(SRC_DIR_BONUS),$(C_FILE_BONUS))

OBJ			=	$(SRC:.c=.o)
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)


all: $(NAME)

bonus: $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(MLXFLAGS) -o $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O0 -c  $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)

re: fclean all
