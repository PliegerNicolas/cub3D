# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emis <emis@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 11:52:14 by nicolas           #+#    #+#              #
#    Updated: 2023/08/19 14:29:53 by emis             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#* ************************************************************************** *#
#* *                            GENERAL INFO                                * *#
#* ************************************************************************** *#

NAME				=			cub3D
RUN_PARAMS			=			maps/mandatory/map.cub

#* ************************************************************************** *#
#* *                             COMPILATION                                * *#
#* ************************************************************************** *#

CC						=			gcc
CC_FLAGS				=
LIBRARY_FLAGS			=			-L/usr/lib -Lmlx -lXext -lX11 -lz -lm


#* ************************************************************************** *#
#* *                               SOURCES                                  * *#
#* ************************************************************************** *#

SOURCES_EXTENSION		=			.c
SOURCES_PATH			=			sources

-include make/sources.mk

#* ************************************************************************** *#
#* *                               LIBFT                                    * *#
#* ************************************************************************** *#

IS_LIBFT				=			true

LIBFT_DIR				=			libft
LIBFT_INCLUDES_DIRS		=			libft
LIBFT_NAME				=			libft.a

LIBFT_COMPLETE			=			$(LIBFT_DIR)/$(LIBFT_NAME)

ifeq ($(IS_LIBFT),true)
	INCLUDES_FLAGS		+=			$(addprefix -I , ${LIBFT_INCLUDES_DIR})
	ALL_LIBS			+=			$(LIBFT_COMPLETE)
endif

#* ************************************************************************** *#
#* *                                MLX                                     * *#
#* ************************************************************************** *#

IS_MLX					=			true

MLX_DIR					=			mlx
MLX_INCLUDES_DIRS		=			mlx
MLX_NAME				=			libmlx_Linux.a

MLX_COMPLETE			=			$(MLX_DIR)/$(MLX_NAME)

ifeq ($(IS_MLX),true)
	INCLUDES_FLAGS		+=			$(addprefix -I , ${MLX_INCLUDES_DIR})
	ALL_LIBS			+=			$(MLX_COMPLETE)
endif

#* ************************************************************************** *#
#* *                              INCLUDES                                  * *#
#* ************************************************************************** *#

INCLUDES_DIRS			=			includes
INCLUDES_FLAGS			=			$(addprefix -I, $(INCLUDES_DIRS))

#* ************************************************************************** *#
#* *                              OBJECTS                                   * *#
#* ************************************************************************** *#

OBJECTS_PATH			=			objects

OBJECTS					:=			$(addprefix $(OBJECTS_PATH)/, $(SOURCES:.c=.o))
DEPENDENCIES			:=			$(OBJECTS:.o=.d)

#* ************************************************************************** *#
#* *                           RULES FILTER                                 * *#
#* ************************************************************************** *#

ifeq (noflag, $(filter noflag,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-Wall -Wextra
else
	CC_FLAGS			+=			-Wall -Wextra -Werror
endif

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-g3
endif

ifeq (sanadd, $(filter sanadd,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-fsanitize=address -g3
endif

ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-fsanitize=thread -g3
endif

ifeq (optimize, $(filter optimize,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-O3
endif

ifeq (bonus, $(filter bonus,$(MAKECMDGOALS)))
	CC_FLAGS			+=			-D BONUS=1
	MAP_FOLDER			=			bonus
else
	CC_FLAGS			+=			-D BONUS=0
	MAP_FOLDER			=			mandatory
endif


#* ************************************************************************** *#
#* *                          TEXT CONSTANTS                                * *#
#* ************************************************************************** *#

BLACK					=			\033[30m
RED						=			\033[31m
GREEN					=			\033[32m
YELLOW					=			\033[33m
BLUE					=			\033[34m
MAGENTA					=			\033[35m
CYAN					=			\033[36m

BOLD					=			\033[1m
THIN					=			\033[2m
ITALIC					=			\033[3m
UNDERLINE				=			\033[4m

RESET_TEXT				=			\033[0m

#* ************************************************************************** *#
#* *                           PRESENTATION                                 * *#
#* ************************************************************************** *#

define intro

	@echo -n "$(BOLD)$(BLUE)"
	@echo "                                      .--,-``-.                 "
	@echo "   ,----..                           /   /     '.      ,---,    "
	@echo "  /   /   \                 ,---,   / ../        ;   .'  .' \`\  "
	@echo " |   :     :         ,--, ,---.'|   \ \`\`\  .\`-    ',---.'     \ "
	@echo " .   |  ;. /       ,'_ /| |   | :    \___\/   \   :|   |  .\`\  |"
	@echo " .   ; /--\`   .--. |  | : :   : :         \   :   |:   : |  '  |"
	@echo " ;   | ;    ,'_ /| :  . | :     |,-.      /  /   / |   ' '  ;  :"
	@echo " |   : |    |  ' | |  . . |   : '  |      \  \   \ '   | ;  .  |"
	@echo " .   | '___ |  | ' |  | | |   |  / :  ___ /   :   ||   | :  |  '"
	@echo " '   ; : .'|:  | : ;  ; | '   : |: | /   /\   /   :'   : | /  ; "
	@echo " '   | '/  :'  :  \`--'   \|   | '/ :/ ,,/  ',-    .|   | '\` ,/  "
	@echo " |   :    / :  ,      .-./|   :    |\ ''\        ; ;   :  .'    "
	@echo "  \   \ .'   \`--\`----'    /    \  /  \   \     .'  |   ,.'      "
	@echo "   \`---\`                  \`-'----'    \`--\`-,,-'    '---'        "
	@echo
	@echo "¸,ø¤º°\`°º¤ø,¸,ø¤°º¤ø,¸,ø¤º°º¤ø,¸,ø¤º°\`°º¤ø,¸,ø¤°º¤ø,¸,ø¤º°\`°º¤ø,¸"
	@echo -n "$(RESET_TEXT)"
endef

define end_success
	@echo
	@echo -n "$(BOLD)$(BLUE)"
	@echo "¸,ø¤º°\`°º¤ø,¸,ø¤°º¤ø,¸,ø¤º°º¤ø,¸,ø¤º°\`°º¤ø,¸,ø¤°º¤ø,¸,ø¤º°\`°º¤ø,¸"
	@echo "$(RESET_TEXT)"
	@echo -n "$(BLUE)"
	@echo	"	⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ "
	@echo	"	⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ "
	@echo	"	⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ "
	@echo	"	⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀         $(BOLD)$(GREEN)$(NAME)$(RESET_TEXT)$(BLUE)"
	@echo	"	⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      $(GREEN)successfully compiled !$(RESET_TEXT)$(BLUE)"
	@echo	"	⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉             "
	@echo -n "$(RESET_TEXT)"
endef

LAST_DIR = ""
FIRST_COMPILE_MESSAGE = true
define compile_message
	@if [ "$(FIRST_COMPILE_MESSAGE)" = "true" ]; then \
		printf "\n"; \
		FIRST_COMPILE_MESSAGE=false; \
	fi
	@if [ "$(dir $<)" != "$(LAST_DIR)" ]; then \
		printf "$(BOLD)$(YELLOW)Compiling files in directory $(RESET_TEXT)$(BOLD)$(CYAN)$(dir $<)$(RESET_TEXT)\n"; \
		LAST_DIR="$(dir $<)"; \
	fi
	printf "$(CYAN)    • $(notdir $<)";
	@$(eval LAST_DIR := $(dir $<))
endef

#* ************************************************************************** *#
#* *                          MAKEFILE RULES                                * *#
#* ************************************************************************** *#

all:					intro $(NAME)

intro:
	@$(call intro)

# -------------------- #
# Create object files. #
# -------------------- #

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%$(SOURCES_EXTENSION)
	@mkdir -p $(dir $@)
	@$(call compile_message)
	@$(CC) $(CC_FLAGS) -MMD -MF $(@:.o=.d)  $(INCLUDES_FLAGS) -c $< -o $@

$(OBJECTS_PATH)/%.o:	%$(SOURCES_EXTENSION)
	@mkdir -p $(dir $@)
	@$(call compile_message)
	@$(CC) $(CC_FLAGS) -MMD -MF $(@:.o=.d)  $(INCLUDES_FLAGS) -c $< -o $@

# -------------------------------- #
# Compile LIBFT and MLX if needed. #
# -------------------------------- #

$(LIBFT_COMPLETE):
ifeq ($(IS_LIBFT), true)
	@echo
	@echo "$(CYAN)Compiling library :$(RESET_TEXT)$(BOLD)$(YELLOW) LIBFT $(RESET_TEXT)$(CYAN)...$(RESET_TEXT)"
	@make --silent -C $(LIBFT_DIR) all
	@echo "$(GREEN)$(BOLD)៙ LIBFT$(RESET_TEXT)$(GREEN) successfully compiled ! 👏 $(RESET_TEXT)"
endif

$(MLX_COMPLETE):
ifeq ($(IS_MLX), true)
	@echo
	@echo "$(CYAN)Compiling library :$(RESET_TEXT)$(BOLD)$(YELLOW) MLX $(RESET_TEXT)$(CYAN)...$(RESET_TEXT)"
	@if git submodule status | egrep -q '^[-]|^[+]' ; then \
		git submodule update --init --recursive > /dev/null 2>&1 ; \
		echo "$(ITALIC)$(YELLOW)MLX$(GREEN) submodule successfully downloaded or updated$(RESET_TEXT)" ; \
	fi
	@make -C $(MLX_DIR) all > /dev/null 2>&1
	@echo "$(GREEN)$(BOLD)៙ MLX$(RESET_TEXT)$(GREEN) successfully compiled ! 👏 $(RESET_TEXT)"
endif
	
# ---------------------------------------- #
# Link the files after compiling them all. #
# ---------------------------------------- #

-include $(DEPENDENCIES)
$(NAME):				$(LIBFT_COMPLETE) $(MLX_COMPLETE) $(OBJECTS)
	@echo
	@echo
	@echo "$(YELLOW)Linking $(BOLD)$(CYAN)$@ $(RESET_TEXT)$(YELLOW)...$(RESET_COLOR)"
	@$(CC) $(CC_FLAGS) $(INCLUDES_FLAGS) -o $@ $(OBJECTS) $(ALL_LIBS) $(LIBRARY_FLAGS)
	@$(call end_success)

# --------------------- #
# Delete compiled data. #
# --------------------- #

clean:
	@rm -rf $(OBJECTS_PATH)
	@echo "$(YELLOW)Deleting $(CYAN)$(OBJECTS_PATH) $(YELLOW)...$(RESET_TEXT)"

fclean:					clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Deleting $(CYAN)$(NAME) executable $(YELLOW)...$(RESET_TEXT)"

fcleanlib:				fclean
ifeq ($(IS_LIBFT), true)
	@echo "$(YELLOW)Deleting all compiled $(CYAN)LIBFT$(YELLOW) files ...$(RESET_TEXT)"
	@make --silent -C $(LIBFT_DIR) fclean
endif
ifeq ($(IS_MLX), true)
	 @if [ -f $(MLX_DIR)/.git ] ; then \
		echo "$(YELLOW)Deleting all compiled $(CYAN)MLX$(YELLOW) files ...$(RESET_TEXT)" ; \
		make -C $(MLX_DIR) clean > /dev/null 2>&1 ; \
		echo "$(YELLOW)De-initializing $(CYAN)MLX$(YELLOW) submodule ...$(RESET_TEXT)" ; \
		git submodule deinit -f $(MLX_DIR) > /dev/null 2>&1 ; \
	fi
endif

# --------------------- #
# Recompile.			#
# --------------------- #

re:						clean all

relib:					fcleanlib all

# --------------------- #
# Additional flag.		#
# --------------------- #

noflag: 				all

debug:					all

sanadd:					all

santhread:				all

optimize:				all

bonus:					all

# --------------------- #
# Woop woop.			#
# --------------------- #

run:					all
	@echo "$(GREEN)Executing : $(CYAN)./$(NAME) $(RUN_PARAMS)$(RESET_TEXT)"
	@./$(NAME) $(RUN_PARAMS)

demo:					all
	@for map in maps/$(MAP_FOLDER)/*.cub ;	\
	do 										\
		./cub3D $$map ;						\
		echo $$map ;						\
	done

gmk:
	@if [ -d make ];then echo ok;else mkdir make;fi
	@find -name '*.c' -printf "%d%p\n" | sort -n | grep -v libft | grep -v mlx | sed 's/^[[:digit:]]/SOURCES += /' > make/sources.mk

.PHONY:	header clean fclean re run fcleanlib relib noflag debug sanadd santhread gmk bonus demo
