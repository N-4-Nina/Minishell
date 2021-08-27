# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:45:13 by chpl              #+#    #+#              #
#    Updated: 2021/08/27 12:40:29 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler and Linker
CC          := clang

#The Target Binary Program
TARGET      := minishell

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
CFLAGS      := -Wall -Wextra -Werror
LIB         := -L libft/ -lft -lreadline
INC         := -I$(INCDIR) -I ${LIBFT}
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: ft directories $(TARGET)

#Remake
re: fclean all

ft:
	@make -C libft

#Make the Directories
directories:
	@mkdir -p $(BUILDDIR)

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
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

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