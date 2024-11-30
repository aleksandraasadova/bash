#!/bin/bash

make -C ../ s21_grep

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
failed=0
i=1
FLAGS="ivcln"

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

for (( i=0; i<${#FLAGS}; i++ )); do
    for (( j=i+1; j<${#FLAGS}; j++ )); do
        ARGS="-${FLAGS:$i:1}${FLAGS:$j:1} a  test.txt test1.txt t.txt"

        grep $ARGS > 1.txt
        ../s21_grep $ARGS > 2.txt
        
        echo "Flag -${FLAGS:$i:1}${FLAGS:$j:1}"

        diff -q 1.txt 2.txt
        if [ $? -eq 0 ]; then
            echo "    Успешно"
        else
            echo "    Ошибка"
        fi

        valgrind --tool=memcheck --leak-check=yes ../s21_grep $ARGS
        ((i++))
    done
done

echo "Flag -e"
rm -f 1.txt 2.txt

grep -e ab -e ba test1.txt > 1.txt
../s21_grep -e ab -e ba test1.txt > 2.txt

# Сравниваем файлы 1.txt и 2.txt
diff -q 1.txt 2.txt
if [ $? -eq 0 ]; then
    echo "    Успешно"
else
    echo "    Ошибка"
fi

# Запуск valgrind для проверки утечек
valgrind --tool=memcheck --leak-check=yes ../s21_grep -e ab -e ba test1.txt

# Удаляем временные файлы
rm -f 1.txt 2.txt
make -C ../ clean