# /* ************************************************************************** */
# /*                                                                            */
# /*                                                        :::      ::::::::   */
# /*   Makefile                                           :+:      :+:    :+:   */
# /*                                                    +:+ +:+         +:+     */
# /*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
# /*                                                +#+#+#+#+#+   +#+           */
# /*   Created: 2025-07-03 21:44:47 by sguruge           #+#    #+#             */
# /*   Updated: 2025-07-03 21:44:47 by sguruge          ###   ########.fr       */
# /*                                                                            */
# /* ************************************************************************** */


NAME = cub3D
RM = rm -f
INCLUDES = -Iincludes
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
UTILSDIR = utils

SRCS = \
       $(SRCDIR)/main.c \
       $(SRCDIR)/free.c \
       $(SRCDIR)/check_args.c \
       $(SRCDIR)/mlx_init.c \
       $(SRCDIR)/parse_cub_file.c \
       $(SRCDIR)/parse_component.c \
       $(SRCDIR)/parse_surface.c \
       $(SRCDIR)/parse_map.c \
       $(SRCDIR)/map_validation.c \
       $(SRCDIR)/map_checker.c \
       $(SRCDIR)/parse_utils1.c \
       $(SRCDIR)/parse_utils2.c \
       $(SRCDIR)/mlx_main_loop.c \
       $(SRCDIR)/raycast.c \
       $(SRCDIR)/frame.c \
       $(SRCDIR)/player_movement.c \
       $(SRCDIR)/trig_table.c \
       $(UTILSDIR)/ft_calloc.c \
       $(UTILSDIR)/ft_strtrim.c \
       $(UTILSDIR)/ft_isdigit.c \
       $(UTILSDIR)/ft_memset.c \
       $(UTILSDIR)/ft_strlen.c \
       $(UTILSDIR)/ft_substr.c \
       $(UTILSDIR)/print1.c \
       $(UTILSDIR)/special_itoa1.c \
       $(UTILSDIR)/ft_atoi.c \
       $(UTILSDIR)/ft_itoa.c \
       $(UTILSDIR)/ft_printf.c \
       $(UTILSDIR)/ft_strncmp.c \
       $(UTILSDIR)/get_next_line.c \
       $(UTILSDIR)/print2.c \
       $(UTILSDIR)/special_itoa2.c \
       $(UTILSDIR)/ft_strdup.c \
       $(UTILSDIR)/get_next_line_utils.c

	   
OBJS = $(SRCS:.c=.o)
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(MLX_LIB) $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re bonus