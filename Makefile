#################### INCLUDE ####################

-include make/includes.mk
-include make/sources.mk

INCPATH		:=	includes/
INC			:=	-I $(INCPATH)

################# FOLDER PATHS ##################

OBJPATH		:=	.objects/

LIBPATH		:=	libft/

MLXPATH		:=	mlx/

#################### SOURCES ####################

LIB			= libft.a

MLX			:= libmlx.a

OBJS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJPATH), $(OBJS))

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -g3

CLIBS		:=	-L${MLXPATH} -lmlx -L${LIBPATH} -lft

RM			:=	rm -rf

NAME		:=	cub3D

####################  RULES  ####################

${NAME}: ${LIBPATH}${LIB} ${MLXPATH}${MLX} ${OBJPATH} ${OBJS} $(INCLUDES)
		${CC} ${CFLAGS} ${OBJS} ${CLIBS} -o ${NAME}
		@echo "Cub3D compiled"

all:	${NAME}

.objects/%.o:	%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ ${INC}

${OBJPATH}:
		mkdir -p ${OBJPATH}

${LIBPATH}${LIB}: | ${LIBPATH}
		$(MAKE) -C ${LIBPATH}

# gitlibft: | ${LIBPATH}
# 		@cd ${LIBPATH} && git pull

# ${LIBPATH}:
# 		git clone https://github.com/ethanolmethanol/libft42 $@

${MLXPATH}${MLX}: | ${MLXPATH}
		$(MAKE) -C ${MLXPATH}

${MLXPATH}:
		git clone https://github.com/42Paris/minilibx-linux $@

clean:
		${RM} ${OBJPATH}

fclean: clean
		$(MAKE) -C ${LIBPATH} fclean
		${RM} ${NAME} ${MLXPATH}

re:		fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=ignore_rl_leaks.supp ./cub3D
# --trace-children=yes

gmk:
		@if [ -d make ];then echo ok;else mkdir make;fi
		@find -name '*.c' | grep -v libft | sed 's/^/SOURCES += /' > make/sources.mk
		@find -name '*.h' | grep -v libft | sed 's/^/INCLUDES += /' > make/includes.mk

.PHONY: all clean fclean re%