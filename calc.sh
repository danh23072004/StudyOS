#!/bin/bash

# -- ANS --

ifANS() {
    if [[ "$a" == "ANS" ]]; then
    {
        a=$result
    }
    fi
    
    if [[ "$b" == "ANS" ]]; then
    {
        b=$result
    }
    fi
}

# -- HIST --


appendHIST() {
    if [ $histCountLine -le 5 ]; then
    {
        hist="$hist"'\n'"${arr[0]}"' '"${arr[1]}"' '"${arr[2]}"
        ((histCountLine+=1))
        echo $histCountLine
    }
    else
    {
        hist="$hist"'\n'"${arr[0]}"' '"${arr[1]}"' '"${arr[2]}"
    }
    fi

}

# -- READ --

readInput() {
    echo -n '>> '
    read -r input
    read -r -a arr <<< "$input"

    if [[ $input == "HIST" ]]; then
    {
        echo -e "$hist"
        read -n 1 -s -r
    }
    else
    {
        # append history command to variable "hist"
        appendHIST

        a="${arr[0]}"
        op="${arr[1]}"
        b="${arr[2]}"

        ifANS
    }
    fi
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
        result=$(echo "$((a % b))" | bc -l)
        ;;
    esac
}

showOutput(){
    #echo 'The expression is: '"$a" "$op" "$b"
    #printf "%.2f" "$result"
    printf "%.2f \n" "$result"
    read -n 1 -s -r
}

# -- Main program here --

histCountLine=0
hist=''

readInput

while [[ $input != "EXIT" ]]
do
    if [[ $input != "HIST" ]]; then
    {
        calculate
        showOutput
    }
    fi
    readInput
done
