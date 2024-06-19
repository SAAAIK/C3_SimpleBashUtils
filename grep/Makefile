CFLAGS = -Wall -Werror -Wextra -std=c11
OBJ = s21_grep
TEST= tests.sh

UTIL = -fsanitize=address


all: style $(OBJ)

clean:
	rm $(OBJ) *log*

style:
	clang-format -i ./*.c ./*.h
	clang-format -n ./*.c ./*.h

leaks:
	cppcheck --enable=all --suppress=missingIncludeSystem .

good: clean all test
	sleep 3
	clear

rebuild: clean $(OBJ) 

s21_grep:
	gcc $(KEYS) parser.c reader.c s21_grep.c -o $(OBJ)

test:
	bash $(TEST)