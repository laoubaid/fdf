# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:40:25 by laoubaid          #+#    #+#              #
#    Updated: 2024/05/04 12:52:05 by laoubaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = mandatory/src/
SRC_DIR_BONUS = bonus/src/
OBJ_DIR = mandatory/obj/
OBJ_DIR_BONUS = bonus/obj/

TARGET = fdf
NAME = .name
NAME_BONUS = .bonus

CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz


C_FILE = main.c map.c map_utils.c hex.c ft_split.c hooks.c gets.c \
	draw.c mlx_utils.c drawline.c drawline_utils.c rotation.c ft_strjoin.c

C_FILE_BONUS = main_bonus.c map_bonus.c map_utils_bonus.c hex_bonus.c \
	additionals_bonus.c ft_split_bonus.c hooks_bonus.c gets_bonus.c \
	draw_bonus.c mlx_utils_bonus.c drawline_bonus.c drawline_utils_bonus.c\
	rotation_bonus.c ft_itoa_bonus.c color_bonus.c


SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))
SRC_BONUS	=	$(addprefix $(SRC_DIR_BONUS),$(C_FILE_BONUS))

OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_BONUS	=	$(patsubst $(SRC_DIR_BONUS)%.c, $(OBJ_DIR_BONUS)%.o, $(SRC_BONUS))


all: $(NAME)

$(NAME): $(OBJ) 
	@rm -rf $(NAME_BONUS)
	@touch $(NAME)
	$(CC) $(OBJ) $(MLXFLAGS) -o $(TARGET)

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	@rm -rf $(NAME)
	@touch $(NAME_BONUS)
	$(CC) $(OBJ_BONUS) $(MLXFLAGS) -o $(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)

fclean: clean
	@rm -rf $(TARGET)
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)

re: fclean all

.SECONDARY:

.PHONY : bonus all clean fclean re
