#!/bin/bash

# for loop in bash script: do echo command 5 times
welcome_function() {
    for i in {1..5}
    do
        echo "Welcome $i times"
    done
}

a=0

while_loop() {
    while [[ $a -le 5 ]]
    do
        echo 'Value of variable a is: ' "$a"
        ((a += 1))
    done
}

welcome_function

while_loop