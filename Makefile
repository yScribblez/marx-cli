# output binary
MARXCLI := marx-cli

# directories for build and source files
PATHS := src
PATHT := test
PATHB := build
PATHD := build/.d
PATHO := build/.o
PATHR := build/res
PATHE := build/out

# source files
SRCS := $(wildcard $(PATHS)/*.c $(PATHS)/data/*.c)
# test source files
TEST_SRCS := $(wildcard $(PATHT)/unity/*.c $(PATHT)/data/*.c)
# all source files for dependency generation
ALL_SRCS := $(SRCS) $(TEST_SRCS)

# objects and dependencies used to generate main executable
OBJS := $(patsubst %,$(PATHO)/%.o,$(basename $(SRCS)))
DEPS := $(patsubst %,$(PATHD)/%.d,$(basename $(SRCS)))

# entire set of objects and dependencies (includes test files)
ALL_OBJS := $(patsubst %,$(PATHO)/%.o,$(basename $(ALL_SRCS)))
ALL_DEPS := $(patsubst %,$(PATHD)/%.d,$(basename $(ALL_SRCS)))

# list of result files and binaries used for testing purposes
RESULTS 	:= $(patsubst $(PATHT)/%_test.c,$(PATHR)/%_test.txt,$(TEST_SRCS))
RESULTS_BIN := $(patsubst $(PATHT)/%_test.c,$(PATHE)/%_test.out,$(TEST_SRCS))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(ALL_OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(ALL_DEPS)) >/dev/null)
$(shell mkdir -p $(dir $(RESULTS)) >/dev/null)
$(shell mkdir -p $(dir $(RESULTS_BIN)) >/dev/null)

CC 	:= clang
LD 	:= clang
TAR := tar

CFLAGS 	:= -std=c11 -D_GNU_SOURCE -Isrc/ -Itest/unity/ -g -O0
LDFLAGS := -ldl -lm
LDLIBS 	:= -Llib/

# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(PATHD)/$*.d

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) -o $@

all: $(MARXCLI)

.PHONY: test
test: $(RESULTS)
	@echo "-----------------------\nPASS:\n-----------------------"
	@echo `grep -h -s PASS $(PATHR)/**/*.txt`
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo `grep -h -s IGNORE $(PATHR)/**/*.txt`
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo `grep -h -s FAIL $(PATHR)/**/*.txt`
	@echo "\nDONE"

.PHONY: clean
clean:
	$(RM) -r $(PATHB) $(MARXCLI) $(TEST_MARXCLI)

.PHONY: help
help:
	@echo available targets: all clean test

$(MARXCLI): $(OBJS)
	$(LINK.o) $^

$(PATHR)/%.txt: $(PATHE)/%.out
	-./$< > $@ 2>&1

$(PATHE)/%_test.out: $(PATHO)/$(PATHT)/%_test.o $(PATHO)/$(PATHT)/unity/unity.o $(filter-out $(PATHO)/$(PATHS)/main.o,$(OBJS))
	$(LINK.o) $^

$(PATHO)/%.o: %.c
$(PATHO)/%.o: %.c $(PATHD)/%.d
	$(COMPILE.c) $<

.PRECIOUS: $(PATHD)/%.d
.PRECIOUS: $(PATHO)/%.o
.PRECIOUS: $(PATHR)/%.txt
.PRECIOUS: $(PATHE)/%.out
$(PATHD)/%.d: ;

-include $(ALL_DEPS)
