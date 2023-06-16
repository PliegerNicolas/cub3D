vpath %.c sources

################### INCLUDE ###################
INCFILE	:=	libft.h
INCPATH	:=	includes/
INC		:=	-I $(INCPATH)

#################### PATHS ####################
SRCPATH	:=	sources/
OBJPATH	:=	.objects/
STRPATH	:=	Strings/
MEMPATH	:=	Memory/
CNVPATH	:=	Convert/
OPTPATH	:=	Output/
IPTPATH	:=	Input/
LSTPATH	:=	Lists/

#################### NAMES ####################

STR		:=	\
		ft_split.c		\
		ft_splitset.c	\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strjointab.c	\
		ft_strlcat.c	\
		ft_strlcpy.c	\
		ft_strlen.c		\
		ft_strmapi.c	\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c
MEM		:=	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_bzero.c		\
		ft_calloc.c
CNV		:=	\
		ft_atoi.c		\
		ft_itoa.c		\
		ft_tolower.c	\
		ft_toupper.c
OPT		:=	\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_printf/ft_printf.c		\
		ft_printf/ft_printf_args.c	\
		ft_printf/ft_printf_flut.c	\
		ft_printf/ft_printf_util.c	\
		ft_printf/ft_printf_flag.c
IPT		:=	\
		get_next_line_bonus.c		\
		get_next_line_utils_bonus.c
LLT		:=	\
		ft_lstadd_back.c	\
		ft_lstadd_front.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstlast.c		\
		ft_lstnew.c			\
		ft_lstsize.c		\
		ft_lstmap.c
CLT		:=	\
		ft_clstadd_back.c	\
		ft_clstadd_front.c	\
		ft_clstclear.c		\
		ft_clstdelone.c		\
		ft_clstiter.c		\
		ft_clstlast.c		\
		ft_clstnew.c		\
		ft_clstsize.c		\
		ft_clstmap.c
LST		:= $(addprefix List/, ${LLT}) $(addprefix CircularList/, ${CLT})

################### SOURCES ###################
STRSRCS	:=	$(addprefix ${STRPATH}, ${STR})
MEMSRCS	:=	$(addprefix ${MEMPATH}, ${MEM})
CNVSRCS	:=	$(addprefix ${CNVPATH}, ${CNV})
OPTSRCS	:=	$(addprefix ${OPTPATH}, ${OPT})
IPTSRCS	:=	$(addprefix ${IPTPATH}, ${IPT})
LSTSRCS	:=	$(addprefix ${LSTPATH}, ${LST})
SRCS	:=	${STRSRCS} ${MEMSRCS} ${CNVSRCS} ${OPTSRCS} ${IPTSRCS} ${LSTSRCS}
OBJS	:=	${SRCS:.c=.o}

OBJS	:=	$(addprefix $(OBJPATH), $(OBJS))
SRCS	:=	$(addprefix $(SRCPATH), $(SRCS))


CC		:= cc

CFLAGS	:= -Wall -Wextra -Werror

MKLIB	:= ar rc

RM		:= rm -rf

NAME	:= libft.a

#################### RULES ####################
${NAME}:	${OBJPATH} ${OBJS} $(addprefix $(INCPATH), $(INCFILE))
		${MKLIB} ${NAME} ${OBJS}
		ranlib ${NAME}

all:		${NAME}

.objects/%.o:	%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ ${INC}

${OBJPATH}:
		mkdir -p ${OBJPATH}

clean:
		${RM} ${OBJPATH}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re%