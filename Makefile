CC= gcc
CFLAGS=-g -Werror -Wextra -std=c11
SOURSES=main.c s21_calc_core.c
OBJECTS=$(SOURSES:.c=.o)
TEST_FLAGS=-lcheck $(shell pkg-config --cflags --libs check)
LIB=libs21_calc_core.a
TEX_FILE=calc_doc
LATEX_COMPILER=latex
LATEX_FLAGS=-interaction=nonstopmode

ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit
endif

all: clean $(LIB)

$(LIB): s21_calc_core.o
	ar rc $(LIB) s21_calc_core.o
	ranlib $(LIB)
	rm *.o

build: $(LIB)
	@mkdir build-SmartCalc-Desktop
	@cd ./build-SmartCalc-Desktop/ && qmake ../SmartCalc/ && make

install: build unistall
	@mkdir -p $(HOME)/School_Projects_Rewiew/SmartCalc_v1.0/
	@cp -rf  build-SmartCalc-Desktop/ $(HOME)/School_Projects_Rewiew/SmartCalc_v1.0/
	make clean

unistall: 
	rm -rf $(HOME)/School_Projects_Rewiew/SmartCalc_v1/

dist:
	mkdir -p SmartCalc_v1.0/src
	cp Makefile *.c *.h \
	SmartCalc/*.pro SmartCalc/*.cpp SmartCalc/*.ui SmartCalc/*.user SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	mv SmartCalc_v1.0.tgz $(HOME)/School_Projects_Rewiew/
	rm -rf SmartCalc_v1.0/

dvi: $(TEX_FILE).dvi
	
$(TEX_FILE).dvi: $(TEX_FILE).tex
	$(LATEX_COMPILER) $(LATEX_FLAGS) $(TEX_FILE).tex

calc.dvi: calc.texi
	$(TEXI2DVI) ./calc.texi

debug: clean $(LIB) main.o
	$(CC) $(CFLAGS) main.o $(LIB) -lm -o debug
	./debug

test: $(LIB)
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	./test

add_coverage_flag: 
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag test
	rm test-*
	lcov -t “gcov_test” -o test.info --rc lcov_branch_coverage=1 --no-external -c -d .
	genhtml -o report/ test.info --rc lcov_branch_coverage=1
	open ./report/index.html

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov \
	*.html *.css *.info report main/*.o s21_math debug \
	build-SmartCalc-Desktop/ \
	*.gz *.aux *.log *.dvi *.toc *.out *.pdf

rebuild: clean all
