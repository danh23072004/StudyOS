#!/bin/bash

readInput() {
    echo -n '>> '
    read -r input
    read -r -a arr <<< "$input"

    a="${arr[0]}"
    op="${arr[1]}"
    b="${arr[2]}"
}

calculate(){
    case $op in
    '+')
        result=$((a + b))
        ;;
    '-')
        result=$((a - b))
        ;;
    'x')
        result=$(echo "$a * $b" | bc -l)
        ;;
    '/')
        result=$(echo "$a / $b" | bc -l)
        ;;
    '%')
        result=$((a % b))
        ;;
    esac
}

showOutput(){
    #echo 'The expression is: '"$a" "$op" "$b"
    #printf "%.2f" "$result"
    printf "%.2f \n" "$result"
    read -n 1 -s -r
}

showHIST(){
    echo 'HIST'
}

# Main program here

readInput

while [[ $a != "EXIT" ]]
do
    calculate
    showOutput
    readInput
done
