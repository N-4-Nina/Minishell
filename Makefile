# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:45:13 by chpl              #+#    #+#              #
#    Updated: 2021/09/25 11:40:44 by chpl             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#The Target Binary Program
TARGET      := minishell
LINK		:= link
#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := srcs
INCDIR      := includes
BUILDDIR    := objs
TARGETDIR   := .
#RESDIR      := res
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o
LIBFT = libft/
#Flags, Libraries and Includes
CC			:= clang
CFLAGS      := -Wall -Wextra -Werror
LIB         := -L libft/ -lft -lreadline
INC         := -I$(INCDIR) -I ${LIBFT}
INCDEP      := -I$(INCDIR)
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Default Make
all: ft directories $(TARGET)
#Remake
re: fclean all
#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)
	make -C libft clean
#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET)
	make -C libft fclean
#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
#Link
$(TARGET): $(OBJECTS)
	$(MAKE) ft
	$(MAKE) directories
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)
ft:
	@make -C libft
#Make the Directories
directories:
	@mkdir -p $(BUILDDIR)
#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -g -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
	
#Non-File Targets
.PHONY: all remake clean cleaner resources
