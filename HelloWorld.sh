#! /bin/bash

echo "Hello World"
greeting=Hello
name=danh55162

echo $greeting $name

# an expression
varA=$((4 + 7)) 
# a string
varA=4+7 

echo 'The result of \"varA\" is '"$varA"

echo 'What is the name of this file?'
echo 'The name is '"$0"

echo 'What is the value of the input string?'
echo 'The value is '"$1"

read -p 'Enter first number : ' -r a
read -p 'Enter second number : ' -r b

varB=$((a + b))
echo 'Sum of two input numbers: ' $varB

# Write a simple bash code compare two variables a and b
if [ "$a" -gt "$b" ]; then
    echo 'a is greater than b'
elif [ "$a" -eq "$b" ]; then
    echo 'a is equal to b'
else
    echo 'a is less than b'
fi

echo 'This extra line is unnecessary, the merge should remove this line.'