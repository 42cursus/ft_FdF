# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 22:28:51 by abelov            #+#    #+#              #
#    Updated: 2023/10/23 22:34:31 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= FdF
CC				:= cc
INC_DIR			=  ./include
INCLUDE_FLAGS	:= -I. -I $(INC_DIR) -I/usr/include
OPTIMIZE_FLAGS	:= -O0
DEBUG_FLAGS		:= -g3 -gdwarf-3
#MANDATORY_FLAGS	:= -Wall -Wextra -Werror
MANDATORY_FLAGS	:=
CFLAGS			= $(MANDATORY_FLAGS) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(INCLUDE_FLAGS)

TEST_MAPS		=  ./resources/test_maps
LIBFT_PATH		=  ./lib/ft
LIBFT			=  $(LIBFT_PATH)/libft.a
LIBX_PATH		=  ./lib/minilibx-linux
LIBX			=  $(LIBX_PATH)/libmlx.a


LINK_FLAGS		:= -L $(LIBFT_PATH) -L $(LIBX_PATH) -lmlx -lft -lX11 -lXext -lm

CTAGS			:= ctags
RM				:= /bin/rm

BUILD_DIR		= build
SRC_DIR			= src
OBJ_DIR			= $(BUILD_DIR)/obj

SRC_FS	 		:= main.c utils.c load_data.c \
					draw_line_d.c \
					data_convert.c \
					my_str_to_wordtab.c \
					on_expose.c
SRCS	 		:= $(SRC_FS:%.c=$(SRC_DIR)/%.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: clean $(NAME) test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ -c $<

$(LIBFT):
		@make -C $(LIBFT_PATH) -j8

$(LIBX):
		@make -C $(LIBX_PATH) -j8

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $^  $(LINK_FLAGS)

test: $(NAME)
		@printf '\033[36m%s\033[0m\n' 'this is a test'
#		@rm -rf $(TEST_MAPS)
#		@cd resources && unzip maps.zip
		./FdF $(TEST_MAPS)/elem2.fdf || true
		./FdF $(TEST_MAPS)/elem-col.fdf || true
		./FdF $(TEST_MAPS)/t1.fdf || true
		./FdF $(TEST_MAPS)/t1.fdf 9 2|| true
#		./FdF $(TEST_MAPS)/t2.fdf || true
#		./resources/fdf_linux $(TEST_MAPS)/42.fdf || true
#		./FdF $(TEST_MAPS)/elem2.fdf 15 1 || true
#		./FdF $(TEST_MAPS)/elem2.fdf 4 3 || true
#		./FdF $(TEST_MAPS)/pyramide.fdf || true
#		./FdF $(TEST_MAPS)/pyramide.fdf 6 3 || true
#		./FdF $(TEST_MAPS)/42.fdf || true
#		./FdF $(TEST_MAPS)/42.fdf 16 2 || true

clean:
		@$(RM) -fr $(OBJ_DIR)
		@make -C $(LIBFT_PATH) clean
		@make -C $(LIBX_PATH) clean

fclean: clean
		@$(RM) -fr $(NAME) $(BUILD_DIR) a.out
		@make -C $(LIBFT_PATH) fclean
		@make -C $(LIBX_PATH) clean

re: fclean all

norm:
		@norminette $(SRCS)
		@make -C $(LIBFT_PATH) norm
		@make -C $(LIBX_PATH) norm

.PHONY: all clean test re
