#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
TESTFILE=buffer/match.txt
TESTFILE2=buffer/match2.txt
TESTFILE3=Makefile

#TESTFILE4=buffer/War.txt
make rebuild
# Массивы флагов
FLAGS1=("-v" "-i" "-c" "-l" "-n")
FLAGS2=("-iv" "-vi" "-ic" "-ci" "-il" "-li" "-in" "-ni" "-vc" "-cv" "-vl" "-lv" "-vn" "-nv" "-cl" "-lc" "-cn" "-nc" "-ln" "-nl")
FLAGS3=("-e")
#FLAGS=("-v" "-i" "-c" "-l" "-n" "-cl" "-ivc" "-iv" "-ic" "-il" "-in" "-vc" "-vl" "-vn" "-cl" "-cn" "-ln")

# Массив паттернов для поиска
PATTERNS=("aboba" "a" "o" "he" "ba", "ab")

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

# Счетчик тестов
i=1
failed=0
echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "with 1 flag"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
# Внешний цикл по паттернам
for PAT in "${PATTERNS[@]}"; do
    # Внутренний цикл по флагам
    for FLAG in "${FLAGS1[@]}"; do
        # Выполнение стандартного grep
        printf " $FLAG $PAT\n"
        grep $FLAG $PAT $TESTFILE $TESTFILE2 $TESTFILE3 > a
        ./s21_grep $FLAG $PAT $TESTFILE $TESTFILE2 $TESTFILE3 > b
        result=$(diff a b)

        if [ $? -eq 0 ]; then
            printf " TEST #$i ${GREEN}PASSED${NC}\n"
        else
            printf " TEST #$i ${RED}FAILED${NC}\n"
            #valgrind --tool=memcheck --leak-check=yes ./s21_grep $FLAG $PAT $TESTFILE $TESTFILE4 $TESTFILE3
            printf "$result\n"
            ((failed++))
        fi

        ((i++))
    done
done
echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "with 2 flags"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
for PAT in "${PATTERNS[@]}"; do
    # Внутренний цикл по флагам
    for FLAG in "${FLAGS2[@]}"; do
        # Выполнение стандартного grep
        printf " $FLAG $PAT\n"
        grep $FLAG $PAT $TESTFILE $TESTFILE2 $TESTFILE3 > a
        ./s21_grep $FLAG $PAT $TESTFILE $TESTFILE2 $TESTFILE3 > b
        result=$(diff a b)

        if [ $? -eq 0 ]; then
            printf " TEST #$i ${GREEN}PASSED${NC}\n"
        else
            printf " TEST #$i ${RED}FAILED${NC}\n"
            #valgrind --tool=memcheck --leak-check=yes ./s21_grep $FLAG $PAT $TESTFILE $TESTFILE4 $TESTFILE3
            printf "$result\n"
            ((failed++))
        fi

        ((i++))
    done
done


printf " ${GREEN}-----DONE[$((i - failed))/$((i))]-----${NC}\n"

rm a b
make clean

