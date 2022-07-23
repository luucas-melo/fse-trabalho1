CC = gcc
CPPC = g++
LDFLAGS = -lwiringPi
BLDDIR = .
INCDIR = $(BLDDIR)/inc
SRCDIR = $(BLDDIR)/src
OBJDIR = $(BLDDIR)/obj
CFLAGS = -c -Wall -I$(INCDIR)
SRCCPP = $(wildcard $(SRCDIR)/*.cpp)
OBJCPP = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCCPP))
SRCC = $(wildcard $(SRCDIR)/*.c)
OBJC = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCC))
OBJ = $(OBJC) $(OBJCPP)
EXE = bin/bin

all: clean $(EXE)

$(EXE): $(OBJ)
	$(CPPC) $(OBJDIR)/*.o -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CPPC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run:
	bin/bin

clean:
	-rm -f $(OBJDIR)/*.o $(EXE)
