flags=("i" "v" "n" "l" "c")
patterns=("ab" "hello" "aboba" "popa" "ba")

# Счетчики для совпадений и несовпадений
matches=0
mismatches=0

# Генерация всех комбинаций флагов
for (( i=0; i<${#flags[@]}; i++ )); do
    for (( j=i; j<${#flags[@]}; j++ )); do
        for (( k=j; k<${#flags[@]}; k++ )); do
            # Формируем комбинацию флагов
            flag_combination="${flags[i]}${flags[j]}${flags[k]}"
            flag_combination=$(echo "$flag_combination" | sed 's/^\(.*\)\(.\)\2/\1\2/g') # Удаляем дубликаты флагов

            # Генерация всех комбинаций шаблонов
            for (( m=0; m<${#patterns[@]}; m++ )); do
                for (( n=m; n<${#patterns[@]}; n++ )); do
                    # Формируем шаблоны с флагом -e
                    if [[ $m -eq $n ]]; then
                        pattern="-e ${patterns[m]}"
                    else
                        pattern="-e ${patterns[m]} -e ${patterns[n]}"
                    fi

                    # Проверка всех флагов
                    echo "Тестирование с флагами -$flag_combination и шаблоном '$pattern' на War.txt"
                    ./s21_grep -$flag_combination $pattern War.txt > s21_output.txt
                    grep -$flag_combination $pattern War.txt > grep_output.txt
                    if diff -u s21_output.txt grep_output.txt > /dev/null; then
                        echo "Вывод совпадает"
                        ((matches++))
                    else
                        echo "Вывод не совпадает"
                        ((mismatches++))
                    fi

                    echo "Тестирование с флагами -$flag_combination и шаблоном '$pattern' на tests/test.txt"
                    ./s21_grep -$flag_combination $pattern tests/test.txt > s21_output.txt
                    grep -$flag_combination $pattern tests/test.txt > grep_output.txt
                    if diff -u s21_output.txt grep_output.txt > /dev/null; then
                        echo "Вывод совпадает"
                        ((matches++))
                    else
                        echo "Вывод не совпадает"
                        ((mismatches++))
                    fi

                    echo "Тестирование с флагами -$flag_combination и шаблоном '$pattern' на обоих файлах"
                    ./s21_grep -$flag_combination $pattern War.txt tests/test.txt > s21_output.txt
                    grep -$flag_combination $pattern War.txt tests/test.txt > grep_output.txt
                    if diff -u s21_output.txt grep_output.txt > /dev/null; then
                        echo "Вывод совпадает"
                        ((matches++))
                    else
                        echo "Вывод не совпадает"
                        ((mismatches++))
                    fi
                done
            done
        done
    done
done

# Удаляем временные файлы
rm s21_output.txt grep_output.txt

# Выводим результаты
echo "Количество совпадений: $matches"
echo "Количество несовпадений: $mismatches"
