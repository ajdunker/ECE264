
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS =
SOURCES = answer10.c pa10.c
TARGET = pa10

# -------------------------------------------------------------

test0: pa07
	./pa07 inputs/input0_A inputs/input0_B
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=outputs/valgrindlog0 ./pa07 inputs/input0_A inputs/input0_B

.PHONY : all build clean environment help testall $(TESTS)
.DEFAULT_GOAL := build

OBJF = obj
OBJS = $(patsubst %.c,$(OBJF)/%.o,$(SOURCES))

-include $(SOURCES:%=$(OBJF)/%.P)

build: $(TARGET)

clean:
	@cd $(CURDIR)
	rm -rf $(TARGET) $(OBJF) outputs *.o

environment:
	@cd $(CURDIR)
	@mkdir -p outputs
	@mkdir -p $(OBJF)


$(TARGET): $(OBJS) | environment
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJF)/%.o: %.c | environment
	@$(GCC) -MM $(CFLAGS) $< | sed 's,^\([^ ]\),$(OBJF)\/\1,g' | sed '$$ s,$$, \\,' > $(OBJF)/$<.P
	$(GCC) $(CFLAGS) -c -o $@ $<

