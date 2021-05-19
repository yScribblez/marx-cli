# output binary
MARXCLI := marx-cli

# source files
SRCS := $(wildcard src/*.c)

# intermediate directory for generated object files
OBJDIR := .o
# intermediate directory for generated dependency files
DEPDIR := .d

# object files, auto generated from source files
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
# dependency files, auto generated from source files
DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)

CC 	:= clang
LD 	:= clang
TAR := tar

CFLAGS 	:= -std=c11 -D_GNU_SOURCE
LDFLAGS := -ldl -lm
LDLIBS 	:= -Llibs/

# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.d

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) -o $@

all: $(MARXCLI)

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR) $(MARXCLI)

.PHONY: test
test:
	@echo no tests configured

.PHONY: help
help:
	@echo available targets: all clean test

$(MARXCLI): $(OBJS)
	$(LINK.o) $^

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(COMPILE.c) $<

.PRECIOUS: $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)
