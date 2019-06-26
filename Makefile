# CC     = gcc
# CFLAGS = -Wall -Wextra -Wpedantic

# EXE    = crack
# OBJ    = crack.c

# $ (EXE): $(OBJ)
# 	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# clean:
# 	rm -f $(EXE)


###########################  Save for future use: #############################

CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -O2 -fomit-frame-pointer

EXE    = crack
OBJ    = crack.o sha256.o


# top (default) target
all: $(EXE)

# how to link executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# other dependencies
crack.o: sha256.h 
sha256.o: sha256.h

# phony targets (these targets do not represent actual files)
.PHONY: clean cleanly all CLEAN

# `make clean` to remove all object files
# `make CLEAN` to remove all object and executable files
# `make cleanly` to `make` then immediately remove object files (inefficient)
clean:
	rm -f $(OBJ)
CLEAN: clean
	rm -f $(EXE)
cleanly: all clean
