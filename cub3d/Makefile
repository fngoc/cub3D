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

SRC = main.c checking_errors_arg.c parser.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra

FLAGMLX = -framework OpenGL -framework AppKit

OPTION = -c -D GL_SILENCE_DEPRECATION

OPTIONOBJ = -o

DEL = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) #$(LIBMLX)
	@cd  $(LIBFT_DIR) && mv ./libft.a ../../
	#@cd  $(LIBMLX_DIR) && mv ./libmlx.dylib ../../
	@gcc $(FLAG) $(OBJ) -L. -lmlx -lft $(FLAGSMLX) $(OPTIONOBJ) $(NAME)
	@./cub3d map.cub

$(LIBFT):
	@cd $(LIBFT_DIR) && $(MAKE)

# $(LIBMLX):
# 	cd $(LIBMLX_DIR) && $(MAKE)

%.o: %.c
	@gcc $(FLAG) $(OPTION) $< $(OPTIONOBJ) $@

clean:
	$(DEL) $(OBJ)
	cd $(LIBFT_DIR) && $(MAKE) $(CLEAN)
	cd $(LIBMLX_DIR) && $(MAKE) $(CLEAN)

fclean: clean
	$(DEL) $(NAME) ./libft.a ./libmlx.dylib
	$(DEL) $(OBJ)
	cd $(LIBFT_DIR) && $(MAKE) $(FCLEAN)

re: fclean all
