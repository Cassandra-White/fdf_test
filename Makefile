SRC =	fdf.c\
		stock_map.c\
		parsing_argv.c\
		ft_error.c\
		get_next_line.c\
		ft_strjoin.c\
		ft_strdel.c\
		ft_memdel.c\
		ft_strnew.c\
		ft_strcpy.c\
		ft_strchr.c\
		ft_strsub.c\
		ft_strcat.c\
		ft_strclr.c\
		ft_strlen.c\
		ft_atoi.c\
		ft_wdcounter.c\
		ft_strsplit.c\
		init_value.c\
		color.c\
		draw.c\
		draw_set.c\
		free_fdf.c\
		deal_key.c\

















NAME = fdf

MLX_DIR = minilibx-linux
MLX = libmlx.a 
CC = clang

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

all:
	@$(MAKE) -j $(NAME)


$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
		@echo $(NAME) : Created !


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re


-include $(DPD)