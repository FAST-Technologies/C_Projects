# Название проекта
PROJECT = s21_decimal
# Название теста
TEST = tests
# gcc compilator
CC = gcc
# ARFLAGS
ARFLAGS = ar rc
# FLAGS for testing
FLAGS = -Wall -Wextra -Werror -std=c11
# Ranlib
RANLIB = ranlib
# CFLAGS
CFLAGS=$(FLAGS) -c
# Флаги для lcov
GCOV_FLAGS =-fprofile-arcs -ftest-coverage
# Дополнительные библиотеки для линковки
LIBS = -lcheck $(LIBS_ADDITIONAL)
# Дополнительные библиотеки для линковки c отчетом о покрытии
LIBS_GCOV = $(LIBS) -lgcov
# Дополнительные библиотеки не для Mac, по умолчанию оставляем пустым, чтобы не портить сборку на Mac
LIBS_ADDITIONAL = 
# Команда для открытия файла отчета о покрытии по умполчанию
CMD_OPEN = open
# Необходимо чтобы отстилизовать не копируя кленг
STYLEFILES = $(wildcard *.c $(PROJECT)/*.c $(TEST)/*.c)
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
TEST_EXE = s21_decimal_test
# Цель и название исполняемого файла для отчета о покрытии
GCOV_EXE = gcov_report
# Имя статичной библиотеки со всеми модулями проекта
MODULES_STATIC_LIBRARY = $(PROJECT).a
# Имя статичной библиотеки для создания покрытия
MODULES_STATIC_LIBRARY_GCOV = s21_decimal_gcov.a
# clearing object files
OBJ_CLEAR = ./$(PROJECT)/arithmetic/s21_*.o ./$(PROJECT)/comparison/s21_*.o ./$(PROJECT)/conversion/s21_*.o ./$(PROJECT)/functions/s21_*.o ./$(PROJECT)/helps/s21_*.o
# checking for clang
CLANG_CHECK = *.h ./$(PROJECT)/*.h  ./$(PROJECT)/arithmetic/*.c ./$(PROJECT)/arithmetic/*.h ./$(PROJECT)/comparison/*.c ./$(PROJECT)/comparison/*.h ./$(PROJECT)/conversion/*.c ./$(PROJECT)/conversion/*.h ./$(PROJECT)/functions/*.c ./$(PROJECT)/functions/*.h ./$(PROJECT)/helps/*.c ./$(PROJECT)/helps/*.h ./$(TEST)/*.c ./$(TEST)/*.h ./$(TEST)/arithmetic/*.c ./$(TEST)/comparison/*.c ./$(TEST)/conversion/*.c ./$(TEST)/functions/*.c
# clean clang
CLANG_CLEAN = ./$(PROJECT)/.clang-format  ./$(PROJECT)/arithmetic/.clang-format ./$(PROJECT)/comparison/.clang-format ./$(PROJECT)/conversion/.clang-format ./$(PROJECT)/functions/.clang-format ./$(PROJECT)/helps/.clang-format ./$(TEST)/.clang-format ./$(TEST)/arithmetic/.clang-format ./$(TEST)/comparison/.clang-format ./$(TEST)/conversion/.clang-format ./$(TEST)/functions/.clang-format
# Определяем ОС
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

ifeq ($(detected_OS), Linux)
	detected_Linux := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')
	# Значение по умолчанию для любых версий Linux
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	ifeq ($(detected_Linux), Arch)
	LIBS_ADDITIONAL = -lm
	CMD_OPEN = xdg-open
	endif

	ifeq ($(detected_Linux), Ubuntu)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif
	
	ifeq ($(detected_Linux), Debian)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif
endif

# Заполняем переменные со списком директорий, исходных и исполняемых файлов
ALL_MODULES_DIRS = $(shell find $(PROJECT) -type d)
MODULES_C_TYPE = $(notdir $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.c"))
MODULES_H_TYPE = $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.h")
S21_DECIMAL_H = $(shell find . -maxdepth 1 -name "*.h")
ALL_H_FILES = $(MODULES_H_TYPE) $(S21_DECIMAL_H)
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

# Далее идут все цели
all: $(TEST_EXE) $(GCOV_EXE)
# s21_decimal_test
$(TEST_EXE): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_STATIC_LIBRARY) $(TEST_O_TYPE)
	@$(CC) $(TEST_O_TYPE) $(MODULES_STATIC_LIBRARY) $(LIBS) -o $(TEST_EXE)
	@./$(TEST_EXE)
# gcov_report
$(GCOV_EXE): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR) $(MODULES_STATIC_LIBRARY_GCOV) $(TEST_O_TYPE) $(ALL_H_FILES) $(TEST_H_TYPE)
	@$(CC) $(TEST_O_TYPE) $(MODULES_STATIC_LIBRARY_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	@./$(GCOV_EXE)
	@gcov -o $(GCOV_OBJ_DIR) $(MODULES_C_TYPE)
	@lcov -t "s21_decimal_test" --output-file rep.info --capture --directory .
	@genhtml -q --output-directory report rep.info
	@open ./report/index.html

# s21_decimal.a
$(MODULES_STATIC_LIBRARY): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_O) $(ALL_H_FILES)
	@$(ARFLAGS) $(MODULES_STATIC_LIBRARY) $(addprefix $(OBJ_DIR)/, $(ALL_MODULES_O))
	@$(RANLIB) $(MODULES_STATIC_LIBRARY)
# s21_decimal_gcov.a
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
# Очистка директории
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f *.a *.o
	rm -f *.c.gcov *.gcno *.gcov *.gcda *.info
	rm -f ./$(GCOV_EXE) ./$(TEST_EXE) 
	rm -rf $(OBJECTE) 
	rm -rf $(OBJJ)
# Стилизация
style:
	@clang-format -style=Google -n $(STYLEFILES)
# Перестройка проекта
rebuild: clean all
# Проверить стиль во всех директориях
check:
	cp ../materials/linters/.clang-format . 
	cp ../materials/linters/.clang-format ./$(PROJECT)
	cp ../materials/linters/.clang-format ./$(PROJECT)/arithmetic 
	cp ../materials/linters/.clang-format ./$(PROJECT)/comparison 
	cp ../materials/linters/.clang-format ./$(PROJECT)/conversion 
	cp ../materials/linters/.clang-format ./$(PROJECT)/functions 
	cp ../materials/linters/.clang-format ./$(PROJECT)/helps 
	cp ../materials/linters/.clang-format ./$(TEST) 
	cp ../materials/linters/.clang-format ./$(TEST)/arithmetic 
	cp ../materials/linters/.clang-format ./$(TEST)/comparison 
	cp ../materials/linters/.clang-format ./$(TEST)/conversion 
	cp ../materials/linters/.clang-format ./$(TEST)/functions 
	clang-format -style=Google -n $(CLANG_CHECK)
	cppcheck --enable=all --suppress=missingIncludeSystem $(CLANG_CHECK)
	rm .clang-format $(CLANG_CLEAN)
# Исправить стиль во всех директориях
clang:
	cp ../materials/linters/.clang-format . 
	cp ../materials/linters/.clang-format ./$(PROJECT)
	cp ../materials/linters/.clang-format ./$(PROJECT)/arithmetic 
	cp ../materials/linters/.clang-format ./$(PROJECT)/comparison 
	cp ../materials/linters/.clang-format ./$(PROJECT)/conversion 
	cp ../materials/linters/.clang-format ./$(PROJECT)/functions 
	cp ../materials/linters/.clang-format ./$(PROJECT)/helps 
	cp ../materials/linters/.clang-format ./$(TEST) 
	cp ../materials/linters/.clang-format ./$(TEST)/arithmetic 
	cp ../materials/linters/.clang-format ./$(TEST)/comparison 
	cp ../materials/linters/.clang-format ./$(TEST)/conversion 
	cp ../materials/linters/.clang-format ./$(TEST)/functions 
	clang-format -style=Google -i $(CLANG_CHECK)
	rm .clang-format $(CLANG_CLEAN)
# Проверить на утечки на Линукс
leaks_check:
	leaks -atExit -- ./$(TEST_EXE)
# Линтер
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(CLANG_CHECK)
# Проверка на утечки
valgrind_check:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXE)

.PHONY: all clean rebuild cppcheck leaks valgrind