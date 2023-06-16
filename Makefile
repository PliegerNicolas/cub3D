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

LIB			:=	libft.a

MLX			:=	libmlx.a

OBJS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJPATH), $(OBJS))

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror

CCFLAGS		:=	-Iincludes -I/usr/include -Imlx -g3

LFLAGS		:=	-L/usr/lib -lXext -lX11 -lm -lz

RM			:=	rm -rf

NAME		:=	cub3D

####################  COLOR  ####################

RED			= \033[31;01m

GREEN		= \033[32;01m

NOCOL		= \033[0m

####################  RULES  ####################

${NAME}: ${LIBPATH}${LIB} ${MLXPATH}${MLX} ${OBJPATH} ${OBJS} $(INCLUDES)
		@${CC} ${CFLAGS} ${OBJS} ${LIBPATH}${LIB} ${MLXPATH}${MLX} ${LFLAGS} -o ${NAME}	\
		&& echo "${GREEN}Cub3D compiled! :D ${NOCOL}"	\
		|| echo "${RED}Cub3D compilation failed... X(${NOCOL}"

all:	${NAME}

.objects/%.o:	%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} ${CCFLAGS} -c $< -o $@ ${INC}

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
		${RM} ${NAME} \
# ${MLXPATH}

re:		fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=ignore_rl_leaks.supp ./cub3D
# --trace-children=yes

gmk:
		@mkdir -p make
		@find -name '*.c' | grep -Ev 'libft|mlx' | sed 's/^/SOURCES += /' > make/sources.mk
		@find -name '*.h' | grep -Ev 'libft|mlx' | sed 's/^/INCLUDES += /' > make/includes.mk

.PHONY: all clean fclean re%