# Название проекта
PROJECT = s21_matrix
# Название теста
TEST = tests
# gcc compilator
CC = gcc
# ARFLAGS
ARFLAGS = ar rcs
# FLAGS for testing
# Флаг компиляции языка
MAIN_FLAGS = -std=c11
# Отладочные флаги
DEBUG_FLAGS = -Wall -Wextra -Werror
# Валгринд
VALG_FLAGS = -g

# Макрос POSIX
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

# Линковка мат библиотеки
MATHLIB = -lm

# Совокупность флагов для сборки
FLAGS = $(DEBUG_FLAGS) $(MAIN_FLAGS) $(POSIX_FLAG)
# Ranlib
RANLIB = ranlib
# CFLAGS (compile)
CFLAGS=$(FLAGS) -c
# Флаги для lcov
GCOV_FLAGS =-fprofile-arcs -ftest-coverage
# Дополнительные библиотеки для линковки
LIBS = -lcheck $(LIBS_ADDITIONAL)

# Сборка флагов в 1 компонент
LIBFLAGS= $(LIBS) $(MATHLIB)

# Дополнительные библиотеки для линковки c отчетом о покрытии
LIBS_GCOV = $(LIBS) -lgcov
# Дополнительные библиотеки не для Mac, по умолчанию оставляем пустым, чтобы не портить сборку на Mac
LIBS_ADDITIONAL =
# Команда для открытия файла отчета о покрытии по умполчанию
CMD_OPEN = open
# Необходимо для стилизации кленгом без копирования
STYLEFILES = $(wildcard *.c *.h $(TEST)/*.c)
# Пути до используемых папок
# Директория для объектных файлов
OBJ_DIR = object_dir
OBJECTE = object
OBJJ = obj
# Директория для gcov файлов
GCOV_OBJ_DIR = obj/gcov


# Директория для тестовых файлов
TESTS_OBJ_DIR = obj/tests
# Директория для тестов
TEST_DIR = tests
# Директория для вывода репорта
REPORT_DIR = report
# Цель и название исполняемого файла для тестов
TEST_EXE = s21_matrix_test
# Цель и название исполняемого файла для отчета о покрытии
GCOV_EXE = gcov_report
# Имя статичной библиотеки со всеми модулями проекта
MODULES_STATIC_LIBRARY = $(PROJECT).a
# Имя статичной библиотеки для создания покрытия
MODULES_STATIC_LIBRARY_GCOV = $(PROJECT)_gcov.a
# clearing object files
OBJ_CLEAR = *.o
# checking for clang
CLANG_CHECK = *.h *.c $(TEST_DIR)/*.c
# clean clang
CLANG_CLEAN = .clang-format $(TEST_DIR)/.clang-format

CL_DIR = ../materials/linters/.clang-format
MAIN_HEADER=$(PROJECT_NAME:=.h)

VALG_FILE = RESULT_VALGRIND.txt
CPPCHECK_FILE = RESULT_CPPCHECK.txt
VALG = valgrind --tool=memcheck --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(VALG_FILE) -s ./
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem --force
CLANG = clang-format

# Определяем ОС
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

ifeq ($(detected_OS), Linux)
        detected_Linux := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')
        # Значение по умолчанию для любых версий Linux
        LIBS_ADDITIONAL = $(MATHLIB) -pthread -lsubunit -lrt
        ifeq ($(detected_Linux), Arch)
        LIBS_ADDITIONAL = $(MATHLIB)
        CMD_OPEN = xdg-open
        endif

        ifeq ($(detected_Linux), Ubuntu)
        LIBS_ADDITIONAL = $(MATHLIB) -pthread -lsubunit -lrt
        CMD_OPEN = xdg-open
        endif

        ifeq ($(detected_Linux), Debian)
        LIBS_ADDITIONAL = $(MATHLIB) -pthread -lsubunit -lrt
        CMD_OPEN = xdg-open
        endif
endif

# Заполняем переменные со списком директорий, исходных и исполняемых файлов
ALL_MODULES_DIRS = $(shell find $(PROJECT).c -type d)
MODULES_C_TYPE = $(notdir $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.c"))
MODULES_H_TYPE = $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.h")
S21_MATRIX_H = $(shell find . -maxdepth 1 -name "*.h")
ALL_H_FILES = $(MODULES_H_TYPE) $(S21_MATRIX_H)
ALL_MODULES_O = $(MODULES_C_TYPE:%.c=%.o)

# Находим необходимые директории и типы для компиляции
ALL_TESTS_DIRS = $(shell find $(TEST_DIR) -type d)
TEST_C_TYPE = $(notdir $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.c"))
TEST_H_TYPE = $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.h")
TEST_O_TYPE = $(addprefix $(TESTS_OBJ_DIR)/, $(notdir $(TEST_C_TYPE:%.c=%.o)))

# Finding all modules to create gcov library
ALL_MODULES_GCOV_O = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(MODULES_C_TYPE:.c=.o)))

# Указываем список каталогов, в которых make выполняет поиск
vpath %.c $(ALL_MODULES_DIRS) : $(ALL_TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# main files
HEAD_FILES = $(shell find . ! -path './tests/*' -type f -name '*.h')
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

# for test files
TEST_SRC_FILES = $(shell find tests/ -type f -name '*.c')
TEST_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.c=.o)))
TEST_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.c=)))
TEST_COV_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.c=.cov.o)))
TEST_COV_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.c=_cov)))


# УТОЧНИТЬ НУЖНЫ ЛИ
BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage
GCOV_OBGEG_DIR = $(BUILD_DIR)/service_files

# Далее идут все цели
all: $(TEST_EXE) $(GCOV_EXE)
# s21_decimal_test
$(TEST_EXE): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_STATIC_LIBRARY) $(TEST_O_TYPE)
	@$(CC) $(TEST_O_TYPE) $(MODULES_STATIC_LIBRARY) $(LIBS) -o $(TEST_EXE)
	@./$(TEST_EXE)

SRC_FILES = $(shell find . ! -path './tests/*' -type f -name '*.c')
# object files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(MAIN_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: */%.c
	$(CC) $(MAIN_FLAGS) -c $< -o $@

# gcov_report
$(GCOV_EXE): $(GCOV_OBJ_DIR) $(GCOV_OBGEG_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR) test $(MODULES_STATIC_LIBRARY_GCOV) $(TEST_O_TYPE) $(ALL_H_FILES) $(TEST_H_TYPE)
	@$(CC) $(TEST_O_TYPE) $(MODULES_STATIC_LIBRARY_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	@./$(GCOV_EXE)
	@gcov -b --object-directory $(GCOV_OBJ_DIR) $(MODULES_C_TYPE) tests/*.c
	@gcov -b --object-directory=$(OBJ_DIR) $(SRC_FILES)
	@lcov -t "s21_matrix_test" --output-file rep.info --capture --directory .
	@gcovr --object-directory $(OBJ_DIR) -r . --html --html-details --exclude-unreachable-branches --output=$(COV_DIR)/
	@genhtml -q --output-directory report rep.info
	@open ./report/index.html


# s21_matrix.a
$(MODULES_STATIC_LIBRARY): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_O) $(ALL_H_FILES)
	@$(ARFLAGS) $(MODULES_STATIC_LIBRARY) $(addprefix $(OBJ_DIR)/, $(ALL_MODULES_O))
	@$(RANLIB) $(MODULES_STATIC_LIBRARY)
# s21_matrix_gcov.a
$(MODULES_STATIC_LIBRARY_GCOV): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_GCOV_O) $(ALL_H_FILES)
	@$(ARFLAGS) $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_MODULES_GCOV_O)
	@$(RANLIB) $(MODULES_STATIC_LIBRARY_GCOV)
# running classic objects file
%.o: %.c $(ALL_H_FILES) $(TEST_H_TYPE)
	@$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) $<
# running object files in obj/gcov
$(GCOV_OBJ_DIR)/%.o : %.c $(ALL_H_FILES) $(TEST_H_TYPE)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $@ $<
# running object files in obj/tests
$(TESTS_OBJ_DIR)/%.o : %.c $(ALL_H_FILES) $(TEST_H_TYPE)
	@$(CC) $(CFLAGS) -o $@ $<
# report
$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
# object_dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
# obj/gcov
$(GCOV_OBJ_DIR):
	@mkdir -p $(GCOV_OBJ_DIR)
# obj/tests
$(TESTS_OBJ_DIR):
	@mkdir -p $(TESTS_OBJ_DIR)

$(OBJ_DIR) $(BUILD_DIR) $(COV_DIR):
	@mkdir -p $@


test: $(TEST_EXE)
	./$(TEST_EXE)


# Очистка директории
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f *.a *.o *.txt
	rm -f *.c.gcov *.gcno *.gcov *.gcda *.info .clang-format tests/.clang-format
	rm -f ./$(GCOV_EXE) ./$(TEST_EXE)
	rm -rf ./../build
	rm -rf $(OBJECTE)
	rm -rf $(OBJJ)
# Стилизация
style:
	@$(CLANG) -style=Google -n $(STYLEFILES)
# Перестройка проекта
rebuild: clean all

rebuild_report: clean gcov_report

#checkers
# Исправить стиль во всех директориях
# Styling all code top clang-format
clang:
	cp $(CL_DIR) .$(CLANG)
	$(CLANG) -i **/*.c *.h *.c
	$(CLANG) -i $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)
	rm -f .$(CLANG)

# Проверить стиль во всех директориях
# Checking the clang-format
check:
	cp $(CL_DIR) .$(CLANG)
	$(CLANG) -i **/*.c *.h *.c
	$(CLANG) -n $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)
	rm -f .$(CLANG)



# Проверить на утечки на Линукс
leaks:
	leaks -atExit -- ./$(TEST_EXE)

# Линтер
cppcheck:
	$(CPPCHECK) **/*c **/*h *.h *.c

# Проверка на утечки
valgrind: $(TEST_EXE)
	$(VALG)$(TEST_EXE)

# Проверка с помощью Valgrind
#valgrind_me: $(TEST_EXEC)
    #$(VALG)$(TEST_EXEC)


.PHONY: all clean rebuild gcov_report cppcheck leaks valgrind

