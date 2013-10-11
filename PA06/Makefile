
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS =
SOURCES = answer06.c pa06.c
TARGET = pa06

# -------------------------------------------------------------

test0: pa06
	./pa06 images/01-unnormalized-smile.ee264 outputs/output1.ppm
	diff -w outputs/output1.ppm expected/01-smile.ppm
	valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog1 ./pa06 images/01-unnormalized-smile.ee264 outputs/output1.ppm

	./pa06 images/02-unnormalized-cat-chess.ee264 outputs/output2.ppm
	diff -w outputs/output2.ppm expected/02-cat-chess.ppm
	valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog2 ./pa06 images/02-unnormalized-cat-chess.ee264 outputs/output2.ppm

	./pa06 images/03-unnormalized-hawkes-bay-NZ.ee264 outputs/output3.ppm
	diff -w outputs/output3.ppm expected/03-hawkes-bay-NZ.ppm
	valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog3 ./pa06 images/03-unnormalized-hawkes-bay-NZ.ee264 outputs/output3.ppm

	./pa06 images/04-unnormalized-nelsonmandela.ee264 outputs/output4.ppm
	diff -w outputs/output4.ppm expected/04-nelsonmandela.ppm
	valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog4 ./pa06 images/04-unnormalized-nelsonmandela.ee264 outputs/output4.ppm

	./pa06 images/05-unnormalized-sagan-stamp.ee264 outputs/output5.ppm
	diff -w outputs/output5.ppm expected/05-sagan-stamp.ppm
	valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog5 ./pa06 images/05-unnormalized-sagan-stamp.ee264 outputs/output5.ppm

test1: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog6 ./pa06 images/corrupt-testcases/bad-comment-len.ee264 outputs/output6.ppm

test2: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog7 ./pa06 images/corrupt-testcases/big-width-height.ee264 outputs/output7.ppm

test3: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog8 ./pa06 images/corrupt-testcases/check-magic-bits.ee264 outputs/output8.ppm

test4: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog9 ./pa06 images/corrupt-testcases/comment-has-no-null-byte.ee264 outputs/output9.ppm

test5: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog10 ./pa06 images/corrupt-testcases/height0.ee264 outputs/output10.ppm

test6: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog11 ./pa06 images/corrupt-testcases/height-wrong.ee264 outputs/output11.ppm

test7: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog12 ./pa06 images/corrupt-testcases/incomplete-header.ee264 outputs/output12.ppm

test8: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog13 ./pa06 images/corrupt-testcases/incomplete-image.ee264 outputs/output13.ppm

test9: pa06
	! valgrind --leak-check=full --verbose --log-file=outputs/valgrindlog14 ./pa06 images/corrupt-testcases/width0.ee264 outputs/output14.ppm


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

