#!/bin/bash

make s21_cat

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

FILE=tests/test.txt
FLAGS=
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
result=$(diff a b)
failed=0
i=1

# TEST 1
if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 2
FILE=tests/test1.txt
FLAGS=-b
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
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
cat $FLAGS tests/test2.txt tests/test.txt >a
./s21_cat $FLAGS tests/test2.txt tests/test.txt >b
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
FILE=tests/test3.txt
FLAGS=-s
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
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
FILE=tests/test.txt
FLAGS=-t
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
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
FILE=tests/test.txt
FLAGS=-e
cat $FLAGS $FILE >a
./s21_cat $FLAGS tests/test.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

((i++))

# TEST 7
FILE=tests/weirdo.txt
FLAGS=
cat $FILE >a
./s21_cat $FILE >b
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
FILE=tests/weirdo.txt
FLAGS=-b
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
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
FILE=tests/weirdo.txt
FLAGS=-n
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
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
FILE=tests/weirdo.txt
FLAGS=-s
cat $FLAGS $FILE >a
./s21_cat $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
	printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
	printf " TEST #$i ${RED}FAILED${NC}\n"
	printf "$result"
	((failed++))
fi

printf " ${GREEN}-----DONE[$((i - failed))/$((i))]-----${NC}\n"

rm a b
make clean
