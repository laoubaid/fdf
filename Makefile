# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:40:25 by laoubaid          #+#    #+#              #
#    Updated: 2025/05/16 21:17:19 by laoubaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/

TARGET = fdf


CFLAGS = -Wall -Wextra
MLXFLAGS = -L./minilibx-linux -lmlx_Linux -I./minilibx-linux -lXext -lX11 -lm -lz


C_FILE = main.c additionals.c drawline_utils.c rotation.c color.c\
	 gets.c map.c draw.c ft_itoa.c hex.c map_utils.c drawline.c ft_split.c hooks.c mlx_utils.c 

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))



all: $(TARGET)

$(TARGET): $(OBJ) 
	$(CC) $(OBJ) $(MLXFLAGS) -o $(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(TARGET)

re: fclean all

.SECONDARY: $(OBJ)

.PHONY : bonus all clean fclean re
