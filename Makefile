CC := clang
CFLAGS := -Wall -Wextra -Werror -O2

CPROGS := badchar cstat

SH_ALL := $(shell find src -type f -executable -exec basename {} \;)

EXEC_ALL := $(sort $(CPROGS) $(SH_ALL))
EXEC_ALL_BIN := $(addprefix bin/, $(EXEC_ALL))

.SECONDEXPANSION:

.PHONY: build
build: $(EXEC_ALL_BIN)

$(EXEC_ALL_BIN): bin

bin:
	mkdir bin

$(addprefix bin/, $(CPROGS)): bin/%: src/%.c
	$(CC) -o $@ $(CFLAGS) $<

$(addprefix bin/, $(SH_ALL)): bin/%: src/%
	cp $< $@

.PHONY: clean
clean:
	rm -rf bin
