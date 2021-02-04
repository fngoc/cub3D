# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 11:30:29 by fngoc             #+#    #+#              #
#    Updated: 2021/02/04 11:44:38 by fngoc            ###   ########.fr        #
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

SRC = main.c\
	start_cub2d.c\
	start_cub3d.c\
	parser/parser.c\
	parser/parser_map.c\
	errors_check/error.c\
	errors_check/error_check_utils_one.c\
	errors_check/error_check_utils_two.c\
	utils/get_inf_utils.c\
	utils/close_win.c\
	utils/my_mlx_pixel_put.c\
	utils/get_pixel.c\
	utils/create_rgb.c\
	utils/key_hook_utils_one.c\
	utils/key_hook_utils_two.c\
	utils/get_sprite.c\
	utils/set_dir_plr.c\
	utils/sprite_utils.c\
	utils/screenshot.c\
	utils/free_lst_map.c\
	utils/cub2d_utils.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra -g -O0

FLAGMLX = -framework OpenGL -framework AppKit

OPTION = -c -D GL_SILENCE_DEPRECATION

OPTIONOBJ = -o

DEL = rm -rf

GREEN ='\033[1;32m'

WHITE ='\033[0;37m'

YELLOW ='\033[1;33m'

CYAN ='\033[1;36m'

MAGENTA ='\033[1;35m'

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
