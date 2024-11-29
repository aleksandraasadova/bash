#!/bin/bash
echo "unit tests"
FLAGS="ivcln"
for (( i=0; i<= ${#FLAGS}; i++ )); do
        for (( j=i+1; j <= ${#FLAGS}; j++)); do
        ARGS="-${FLAGS:$i:1}${FLAGS:$j:1} a  test.txt War.txt buffer/t.txt"
        grep $ARGS > 1.txt
        ../../src/grep/s21_grep $ARGS > 2.txt
        echo "Flag -${FLAGS:$i:1}${FLAGS:$j:1}"
        diff -q 1.txt 2.txt
        if [ $? -eq 0 ]; then
        echo "    Успешно"
        else
        echo "    Ошибка"
        fi
        done
		valgrind --tool=memcheck --leak-check=yes  ./s21_grep $ARGS
done
echo "Flag -e"
grep -e ab -e ba War.txt > 1.txt
../../src/grep/s21_grep -e ab -e ba War.txt > 2.txt
diff -q 1.txt 2.txt
if [ $? -eq 0 ]; then
echo "    Успешно"
else
echo "    Ошибка"
fi
		valgrind --tool=memcheck --leak-check=yes ./s21_grep -e ab -e ba War.txt
