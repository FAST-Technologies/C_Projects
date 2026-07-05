CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
GOVFLAGS=-fprofile-arcs -ftest-coverage
AR=ar
ARFLAGS=rcs
CHECKFLAGS=$(shell pkg-config --cflags --libs check)

# возвращает список всех файлов, соответствующих шаблону
SRCS=$(wildcard s21_*.c)
TEST_SRCS=$(wildcard test_*.c)

# заменить все вхождения .c на .o
OBJS=$(SRCS:.c=.o)
TEST_OBJS=$(TEST_SRCS:.c=.o)

all: s21_string.a

s21_string.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# чистим, что бы не засорять текущую директорию
	rm -f $(OBJS)

# компилирует исходники в объектные файлы
# % - означает любой набор символов
s21_%.o: s21_%.c
	$(CC) $(CFLAGS) -c $< -o $@
# $<: имя исходного файла
# $@: имя целевого файла

test_%.o: test_%.c
	$(CC) $(CFLAGS) $(GOVFLAGS) -c $< -o $@


test: clean s21_string.a test_s21_string
# запускаем тест и удаляем тестовый исполняемый файл
	./test_s21_string
	
# удаляем объектный файл
	rm -f ./test_s21_*.o


test_s21_string: $(TEST_OBJS) s21_string.a
	$(CC) $(CFLAGS) $(GOVFLAGS) $(TEST_OBJS) s21_string.a -o $@ $(CHECKFLAGS)

# Цель для генерации отчетов о покрытии кода в формате HTML
gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage

clean:
	rm -f $(OBJS) $(TEST_OBJS) s21_string.a test_s21_string *.gcno *.gcda *.gcov coverage.info *.out
	rm -rf coverage

check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format

leaks_check:
	leaks -atExit -- ./test_s21_string

valgrind_check:
	valgrind --leak-check=full --show-leak-kinds=all ./test_s21_string
