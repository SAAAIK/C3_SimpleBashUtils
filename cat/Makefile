CFLAGS = -Wall -Werror -Wextra -std=c11
OBJ = s21_cat
TEST_LEAKS= test_leak_cat.sh
TEST_FUNC= test_func_cat.sh

UTIL = -fsanitize=address


all: style $(OBJ)

clean:
	rm $(OBJ)

style:
	clang-format -i ./*.c ./*.h
	clang-format -n ./*.c ./*.h

leaks:
	cppcheck --enable=all --suppress=missingIncludeSystem .

good: clean all test
	sleep 3
	clear

rebuild: clean $(OBJ) 

s21_cat:
	gcc $(KEYS) parser.c reader.c s21_cat.c -o $(OBJ)

test:
	bash $(TEST_FUNC)
