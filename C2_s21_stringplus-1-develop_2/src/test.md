# Check - тестирование функций в Си 

Библиотека Check предоставляет множество макросов для различных типов утверждений (assertions), которые можно использовать для проверки ожидаемых результатов в тестах. Вот некоторые из них:

## Утверждения для целых чисел

Проверяет, что два целых числа равны.
```
ck_assert_int_eq(int actual, int expected)
```

Проверяет, что два целых числа не равны.
```
ck_assert_int_ne(int actual, int expected)
```

Проверяет, что первое целое число меньше второго.
```
ck_assert_int_lt(int actual, int expected)
```

Проверяет, что первое целое число меньше или равно второму.
```
ck_assert_int_le(int actual, int expected)
```

Проверяет, что первое целое число больше второго.
```
ck_assert_int_gt(int actual, int expected)
```

Проверяет, что первое целое число больше или равно второму.
```
ck_assert_int_ge(int actual, int expected)
```

## Утверждения для строк

Проверяет, что две строки равны.
```
ck_assert_str_eq(const char *actual, const char *expected)
```

Проверяет, что две строки не равны.
```
ck_assert_str_ne(const char *actual, const char *expected)
```

Проверяет, что первая строка меньше второй (лексикографически).
```
ck_assert_str_lt(const char *actual, const char *expected)
```

Проверяет, что первая строка меньше или равна второй (лексикографически).
```
ck_assert_str_le(const char *actual, const char *expected)
```

Проверяет, что первая строка больше второй (лексикографически).
```
ck_assert_str_gt(const char *actual, const char *expected)
```

Проверяет, что первая строка больше или равна второй (лексикографически).
```
ck_assert_str_ge(const char *actual, const char *expected)
```

## Утверждения для указателей

Проверяет, что два указателя равны.
```
ck_assert_ptr_eq(void *actual, void *expected)
```

Проверяет, что два указателя не равны.
```
ck_assert_ptr_ne(void *actual, void *expected)
```

Проверяет, что указатель равен NULL.
```
ck_assert_ptr_null(void *ptr)
```

Проверяет, что указатель не равен NULL.
```
ck_assert_ptr_nonnull(void *ptr)
```

## Утверждения для чисел с плавающей запятой

Проверяет, что два числа с плавающей запятой равны.
```
ck_assert_float_eq(float actual, float expected)
```

Проверяет, что два числа с плавающей запятой не равны.
```
ck_assert_float_ne(float actual, float expected)
```

Проверяет, что первое число с плавающей запятой меньше второго.
```
ck_assert_float_lt(float actual, float expected)
```

Проверяет, что первое число с плавающей запятой меньше или равно второму.
```
ck_assert_float_le(float actual, float expected)
```

Проверяет, что первое число с плавающей запятой больше второго.
```
ck_assert_float_gt(float actual, float expected)
```

Проверяет, что первое число с плавающей запятой больше или равно второму.
```
ck_assert_float_ge(float actual, float expected)
```