#!/bin/bash

# -- ANS --

ifANS() {
    if [[ "$a" == "ANS" ]]; then
    {
        a=$ans
    }
    fi
    
    if [[ "$b" == "ANS" ]]; then
    {
        b=$ans
    }
    fi
}

# -- HIST --


appendHIST() {
    if [ $histCountLine -lt 5 ]; then
    {
        hist="$hist""${arr[0]}"' '"${arr[1]}"' '"${arr[2]}"'\n'
        ((histCountLine+=1))
    }
    else
    {
        hist="$hist""${arr[0]}"' '"${arr[1]}"' '"${arr[2]}"'\n'
        hist="${hist#*'\n'}"
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
        local printhist="${hist:0:-2}"
        echo -e "$printhist"
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

division() {
    if [[ $b == 0 ]]; then
        result='MATH ERROR'
    else
        result=$(echo "$a / $b" | bc -l)
    fi
}

calculate() {
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
        division
        ;;
    '%')
        result=$(echo "$((a % b))" | bc -l)
        ;;
    *)

    esac

    if [[ $result != 'MATH ERROR' && $result != 'SYNTAX ERROR' ]]; then
    {
        # echo 'value of result '"$result"
        # echo 'value of ans before change: '"$ans"
        ans="$result"
        # echo 'value of ans after change: '"$ans"
    }
    fi
}

showOutput(){
    #echo 'The expression is: '"$a" "$op" "$b"
    #printf "%.2f" "$result"
    if [[ $result != 'MATH ERROR' && $result != 'SYNTAX ERROR' ]]; then
    {
        printf "%.2f \n" "$result"
    }
    else
        echo "$result"
    fi
    
    #echo "$result"
    read -n 1 -s -r
}

# -- Main program here --


histCountLine=0
hist=''
ans=0 # for storing output after result
result=0 # for storing output after perform execution
#output=0

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
