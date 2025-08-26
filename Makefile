# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/26 21:22:20 by abelov            #+#    #+#              #
#    Updated: 2025/08/26 21:22:20 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			:= /bin/bash

# remove built-in suffix rules to avoid fallback like '.o'
.SUFFIXES:

TEMPLATE_DIR	?= templates/day
PLACEHOLDER		?= __PROJECT_NAME__

# Defaults to quiet. Use "make V=1" to have verbose output.
V ?= 0
ifeq ($(V),0)
  Q := @
  MAKEFLAGS += --no-print-directory
else
  Q :=
endif
export V

all:
	$(Q)printf '\n'
	$(Q)printf '=%.0s' {1..60}; printf '\n\n'
	$(Q)echo -e "  Usage: make new\n"
	$(Q)echo -e "  Creates new assignment project folder based on a template\n"
	$(Q)printf '=%.0s' {1..60}; printf '\n\n'


## make new-<name>
new-%:
	$(Q)set -e; \
	export name="$*"; \
	if [ -z "$$name" ]; then \
		echo "Empty assignment name" >&2; exit 2; \
	fi; \
	if [ -e "$$name" ]; then \
		printf "Directory '%s' already exists\n" "$$name" >&2; exit 1; \
	fi; \
	printf "\nCreating '%s'...\n" "$$name"; \
	mkdir -p "$$name/src" "$$name/include"; \
	rsync -a "$(TEMPLATE_DIR)/" "$$name/"; \
	mv "$$name/include/day.h" "$$name/include/$$name.h"; \
	perl -pi -e 's/$(PLACEHOLDER)/'"$${name^^}"'/g;' \
	  "$$name"/include/"$$name".h; \
	export files=( \
	  "$$name"/CMakeLists.txt \
	  "$$name"/src/*.c \
	  "$$name"/include/*.h \
	); \
	perl -pi -e 's/$(PLACEHOLDER)/'"$$name"'/g;' \
		$${files[@]} 2>/dev/null || true; \
	for f in $${files[@]}; do \
	  vim -Es -Nu NONE -c "runtime plugin/stdheader.vim" +"Stdheader" +wq -- "$$f"; \
	done;
	$(Q)printf "cmake -S . -B build -G Ninja\n"; \
	printf "cmake --build build --target $*\n"; \
	printf "\nUpdating cmake files...\n"; \
	echo "add_subdirectory($*)" >> CMakeLists.txt; \
	git add "$*" .gitignore; \
	cmake -S . -B build -G Ninja; \
	printf "\nBuilding the project...\n"; \
	cmake --build build --target "$*";
	$(Q)printf '\n'; printf '=%.0s' {1..80}; printf '\n\n'; \
	printf "  Assignment '$*' has been created.\n\n"; \
	printf '=%.0s' {1..80}; printf '\n\n';


## Name for interactive mode if NAME was not provided
PROJECT_NAME ?= $(shell bash ./scripts/get_project_name.sh)

## Interactive prompt for the name
new:
	+$(Q)$(MAKE) --no-print-directory new-$(PROJECT_NAME)

.PHONY: all new-% new