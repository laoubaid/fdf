SRC_DIR = ./
NAME = fdf
C_FILE = main.c map.c hex.c ft_strjoin.c ft_split.c get_next_line.c get_next_line_utils.c
SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g -o $(NAME)
	rm -rf *.o

leak: $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -fsanitize=address -g -o $(NAME)
	rm -rf *.o

%.o: %.c
	$(CC) -Wall -I/usr/include -Imlx_linux -O0 -g -c $< -o $@

clean:
	rm -rf *.o
