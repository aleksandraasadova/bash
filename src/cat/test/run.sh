#!/bin/bash

make -C ../ s21_cat

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
failed=0
i=1

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

# TEST 1
FILE=test1.txt
FLAGS=
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 2
FILE=test2.txt
FLAGS=-b
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 3
FLAGS=-n
cat $FLAGS test2.txt test.txt >a
../s21_cat $FLAGS test2.txt test.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 4
FILE=test3.txt
FLAGS=-s
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 5
FILE=test5.txt
FLAGS=-t
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 6
FILE="test6.txt test1.txt test2.txt test3.txt test4.txt test5.txt test7.txt"
FLAGS=-e
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE>b
result=$(diff -c a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 7
FILE=test7.txt
FLAGS=
cat $FILE >a
../s21_cat $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 8
FILE=test7.txt
FLAGS=-b
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 9
FILE=test7.txt
FLAGS=-n
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 10
FILE=test7.txt
FLAGS=-s
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 11 FOR FLAG S

FILE="test00.txt test0.txt"
FLAGS=-s
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 12 FOR FLAG S

FILE="test0.txt test00.txt"
FLAGS=-s
cat $FLAGS $FILE >a
../s21_cat $FLAGS $FILE >b
result=$(diff -c a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

printf " ${GREEN}-----DONE[$((i - failed))/$((i))]-----${NC}\n"



rm a b
make -C ../ clean
