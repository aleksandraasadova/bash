CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11
TARGET = s21_cat
FILES = *.c

all: $(TARGET)

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all

format:
	clang-format -i *.c

check-format:
	clang-format -n *.c

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES)
