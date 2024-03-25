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
        result=$((a * b))
        ;;
    '/')
        result=$((a / b))
        ;;
    '%')
        result=$((a % b))
        ;;
    esac
}

showOutput(){
    echo 'The expression is: '"$a" "$op" "$b"

    echo "The result is: $result"
}

readInput

calculate



