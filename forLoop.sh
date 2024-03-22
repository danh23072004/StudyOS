#!/bin/bash

# for loop in bash script: do echo command 5 times
welcome_function() {
    for i in {1..5}
    do
        echo "Welcome $i times"
    done
}

welcome_function