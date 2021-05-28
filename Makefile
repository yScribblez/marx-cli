# output binary name
BIN := marx-cli

# directories for build and source files
PATHS := src
PATHT := test
PATHB := build

RPATH  := $(PATHB)/release
RPATHD := $(RPATH)/.d
RPATHO := $(RPATH)/.o
RPATHR := $(RPATH)/res
RPATHE := $(RPATH)/out

DPATH  := $(PATHB)/debug
DPATHD := $(DPATH)/.d
DPATHO := $(DPATH)/.o
DPATHR := $(DPATH)/res
DPATHE := $(DPATH)/out

MARXCLI 		:= $(RPATH)/$(BIN)
MARXCLI_DEBUG 	:= $(DPATH)/$(BIN)

# source files
SRCS := $(wildcard $(PATHS)/*.c $(PATHS)/data/*.c)
# test source files
TEST_SRCS := $(wildcard $(PATHT)/unity/*.c $(PATHT)/data/*.c)
# all source files for dependency generation
ALL_SRCS := $(SRCS) $(TEST_SRCS)

# RELEASE #
# objects and dependencies used to generate main executable
OBJS := $(patsubst %,$(RPATHO)/%.o,$(basename $(SRCS)))
DEPS := $(patsubst %,$(RPATHD)/%.d,$(basename $(SRCS)))

# entire set of objects and dependencies (includes test files)
ALL_OBJS := $(patsubst %,$(RPATHO)/%.o,$(basename $(ALL_SRCS)))
ALL_DEPS := $(patsubst %,$(RPATHD)/%.d,$(basename $(ALL_SRCS)))

# list of result files and binaries used for testing purposes
RESULTS 	:= $(patsubst $(PATHT)/%_test.c,$(RPATHR)/%_test.txt,$(TEST_SRCS))
RESULTS_BIN := $(patsubst $(PATHT)/%_test.c,$(RPATHE)/%_test.out,$(TEST_SRCS))

# DEBUG #
# objects and dependencies used to generate main executable
DEBUG_OBJS := $(patsubst %,$(DPATHO)/%.o,$(basename $(SRCS)))
DEBUG_DEPS := $(patsubst %,$(DPATHD)/%.d,$(basename $(SRCS)))

# entire set of objects and dependencies (includes test files)
DEBUG_ALL_OBJS := $(patsubst %,$(DPATHO)/%.o,$(basename $(ALL_SRCS)))
DEBUG_ALL_DEPS := $(patsubst %,$(DPATHD)/%.d,$(basename $(ALL_SRCS)))

# list of result files and binaries used for testing purposes
DEBUG_RESULTS 		:= $(patsubst $(PATHT)/%_test.c,$(DPATHR)/%_test.txt,$(TEST_SRCS))
DEBUG_RESULTS_BIN 	:= $(patsubst $(PATHT)/%_test.c,$(DPATHE)/%_test.out,$(TEST_SRCS))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(ALL_OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(ALL_DEPS)) >/dev/null)
$(shell mkdir -p $(dir $(RESULTS)) >/dev/null)
$(shell mkdir -p $(dir $(RESULTS_BIN)) >/dev/null)
$(shell mkdir -p $(dir $(DEBUG_ALL_OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEBUG_ALL_DEPS)) >/dev/null)
$(shell mkdir -p $(dir $(DEBUG_RESULTS)) >/dev/null)
$(shell mkdir -p $(dir $(DEBUG_RESULTS_BIN)) >/dev/null)

CC 	:= clang
LD 	:= clang
TAR := tar

CFLAGS 	:= -std=c11 -Isrc/ -Itest/unity/ -O0
LDFLAGS := -ldl -lm
LDLIBS 	:= -Llib/

# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF

COMPILE.c = $(CC) $(DEPFLAGS)/$*.d $(CFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) -o $@

all: release_build $(MARXCLI)
release_build: 
	$(eval DEPFLAGS += $(RPATHD))

debug: debug_build $(MARXCLI_DEBUG)
debug_build: 
	$(eval DEPFLAGS += $(RPATHD))
	$(eval CFLAGS += -g)

.PHONY: test
test: debug_build $(DEBUG_RESULTS)
	@echo "-----------------------\nPASS:\n-----------------------"
	@echo `grep -h -s PASS $(DPATHR)/**/*.txt`
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo `grep -h -s IGNORE $(DPATHR)/**/*.txt`
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo `grep -h -s FAIL $(DPATHR)/**/*.txt`
	@echo "\nDONE"

.PHONY: clean
clean:
	$(RM) -r $(PATHB)

.PHONY: help
help:
	@echo available targets: all clean test

$(MARXCLI): $(OBJS)
	$(LINK.o) $^

$(MARXCLI_DEBUG): $(DEBUG_OBJS)
	$(LINK.o) $^

$(DPATHR)/%.txt: $(DPATHE)/%.out
	-./$< > $@ 2>&1

$(DPATHE)/%_test.out: $(DPATHO)/$(PATHT)/%_test.o $(DPATHO)/$(PATHT)/unity/unity.o $(filter-out $(DPATHO)/$(PATHS)/main.o,$(DEBUG_OBJS))
	$(LINK.o) $^

$(RPATHO)/%.o: %.c
$(RPATHO)/%.o: %.c $(RPATHD)/%.d
	$(COMPILE.c) $<

$(DPATHO)/%.o: %.c
$(DPATHO)/%.o: %.c $(DPATHD)/%.d
	$(COMPILE.c) $<

.PRECIOUS: $(RPATHD)/%.d
.PRECIOUS: $(RPATHO)/%.o
.PRECIOUS: $(RPATHR)/%.txt
.PRECIOUS: $(RPATHE)/%_test.out
.PRECIOUS: $(DPATHD)/%.d
.PRECIOUS: $(DPATHO)/%.o
.PRECIOUS: $(DPATHR)/%.txt
.PRECIOUS: $(DPATHE)/%_test.out
$(RPATHD)/%.d: ;
$(DPATHD)/%.d: ;

-include $(ALL_DEPS) $(DEBUG_ALL_DEPS)
