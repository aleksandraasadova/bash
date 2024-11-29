CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11
TARGET = s21_grep
FILES = *.c

all: $(TARGET)

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all

format:
	clang-format -i $(FILES) *.h

check-format:
	clang-format -n $(FILES) *.h

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES) *.h
