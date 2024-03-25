#!/bin/bash

# -- ANS --

ifANS() {
    if [ "$a" == "ANS" ]; then
    {
        a=$result
    }
    fi
    
    if [ "$b" == "ANS" ]; then
    {
        b=$result
    }
    fi
}

# -- HIST --

ifHIST() {
    echo "$hist"
}

showHIST() {
    echo '' 
}

histCountLine=0
hist=''
appendHIST() {
    if [ $histCountLine -le 5 ]; then
    {
        hist="$hist""$input"'\n'
        ((var+=1))
    }
    else
    {
        hist="$hist""$input"'\n'
    }
    fi

}

# -- READ --

readInput() {
    echo -n '>> '
    read -r input
    read -r -a arr <<< "$input"

    # append history command to variable "hist"
    appendHIST

    a="${arr[0]}"
    op="${arr[1]}"
    b="${arr[2]}"

    ifANS
}

# -- CALCULATE --

calculate(){
    case $op in
    '+')
        result=$(echo "$a + $b" | bc -l)
        ;;
    '-')
        result=$(echo "$a - $b" | bc -l)
        ;;
    'x')
        result=$(echo "$a * $b" | bc -l)
        ;;
    '/')
        result=$(echo "$a / $b" | bc -l)
        ;;
    '%')
        result=$(echo "$a % $b" | bc -l)
        ;;
    esac
}

showOutput(){
    #echo 'The expression is: '"$a" "$op" "$b"
    #printf "%.2f" "$result"
    printf "%.2f \n" "$result"
    read -n 1 -s -r
}

# Main program here

readInput

while [[ $input != "EXIT" ]]
do
    calculate
    showOutput
    readInput
done
