# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 11:30:29 by fngoc             #+#    #+#              #
#    Updated: 2021/01/18 14:11:53 by fngoc            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean bonus fclean re

NAME = cub3d

HEADER = cub3d.h

LIBFT_DIR = libs/libft/

LIBFT = $(LIBFT_DIR)libft.a

LIBMLX_DIR = libs/minilibx_mms/

LIBMLX = $(LIBMLX_DIR)libmlx.dylib

MAKE = make

CLEAN = clean

FCLEAN = fclean

SRC = main.c parser.c start_cub2d.c parser_map.c error.c\
	error_check_utils_one.c error_check_utils_two.c\
	get_inf_utils.c start_cub3d.c close_win.c\
	my_mlx_pixel_put.c get_pixel.c create_rgb.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra

FLAGMLX = -framework OpenGL -framework AppKit

OPTION = -c -D GL_SILENCE_DEPRECATION

OPTIONOBJ = -o

DEL = rm -rf

GREEN='\033[1;32m'

WHITE='\033[0;37m'

YELLOW='\033[1;33m'

CYAN='\033[1;36m'

MAGENTA='\033[1;35m'

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@cd $(LIBFT_DIR) && mv ./libft.a ../../
	@cd $(LIBMLX_DIR) && mv ./libmlx.dylib ../../
	@$(CC) $(FLAG) $(OBJ) -L. -lmlx -lft $(FLAGSMLX) $(OPTIONOBJ) $(NAME)
	@echo ${YELLOW}"Step 3 is done!"
	@echo $(GREEN)"Start!"${WHITE}
	@./cub3d map.cub

$(LIBFT):
	@cd $(LIBFT_DIR) && $(MAKE)
	@echo ${MAGENTA}"Step 1 is done!"

$(LIBMLX):
	@cd $(LIBMLX_DIR) && $(MAKE)
	@echo ${CYAN}"Step 2 is done!"

%.o: %.c
	@$(CC) $(FLAG) $(OPTION) $< $(OPTIONOBJ) $@

clean:
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(CLEAN)
	@cd $(LIBMLX_DIR) && $(MAKE) $(CLEAN)
	@echo $(GREEN)"All cleared."

fclean: clean
	@$(DEL) $(NAME) ./libft.a ./libmlx.dylib
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(FCLEAN)
	@echo $(GREEN)"All libs cleared."

re: fclean all
