CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lraylib -lm
# lm is for libm used by raygui

SRCDIR = src
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")

# compile files but not link
OBJDIR = objs
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# compiled and linked program (final executable)
OUTDIR = out
OUTFILE = $(OUTDIR)/Goopy

all: main

# https://stackoverflow.com/questions/2145590/what-is-the-purpose-of-phony-in-a-makefile
# clean command is not associated with any file found that could be named "clean"
.PHONY: clean | debug

# wait for all object files to be generated and
# link them for final executable
# ldflags are put after input file cuz it doesnt work otherwise (IDK why)
main: $(OBJ) | $(OUTDIR)
	@echo -n "\033[0;34mlinking objects: \033[0m"
	$(CC) $(CFLAGS) $? -o $(OUTFILE) $(LDFLAGS)

# TODO: compile for gdb
# main_debug:

# for all c files found in SRCDIR create an object file in OBJDIR
# and if folder obj not found create it
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo -n "\033[0;32mgenerating $@: \033[0m" # codes to color green
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# create dirs if not found
$(OUTDIR) | $(OBJDIR):
	mkdir $@

debug:
	@echo $(SRCS)
	@echo $(OBJ)

outfile:
	@echo $(OUTFILE)


clean:
	rm -r $(OBJDIR)/* $(OUTDIR)/*
	rmdir $(OBJDIR) $(OUTDIR)



