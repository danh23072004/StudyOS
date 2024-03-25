#!/bin/bash

readInput() {
    read -r input
    read -r -a arr <<< "$input"
}

readInput

a="${arr[0]}"
op="${arr[1]}"
b="${arr[2]}"

echo 'The expression is: '"$a" "$op" "$b"


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

echo "The result is: $result"
