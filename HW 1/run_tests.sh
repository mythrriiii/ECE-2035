#!/bin/bash
# Bash script to test student's code for the alternative
# squares method for ECE2035. 
# Written by Diego Fratta and AI in 2023

# Only current issue here is that you can't check for the newline, but students shouldn't
# be changing it...

# Set the paths and filenames for the source code and compiled executable
source_code="HW1-2.c"         
executable="HW1-2"            

# Compiler and compiler flags 
compiler="gcc"                          
compiler_flags="-Wall -g -o $executable"        

# Test numbers
test_numbers=(15 54 2035)              

# Test outputs as variables for different values of x
test_output_15="x: 15, SQ: 225, A: 225, Result: 1"
test_output_54="x: 54, SQ: 2916, A: 3016, Result: 0"
test_output_2035="x: 2035, SQ: 4141225, A: 4141225, Result: 1"


# Function to compile the code
compile_code() {
    $compiler $compiler_flags $source_code
}

# Function to run the compiled executable and capture the output
run_code() {
    ./$executable > program_output.txt
}

# Function to compare the program output with the test output
compare_output() {
    local expected_output="test_output_$x"
    local program_output=$(cat program_output.txt)
    
    echo "---- Test $x ----"
    echo "Expected Output:"
    echo "${!expected_output}"
    echo "Program Output:"
    echo "$program_output"
    
    if [ "$program_output" = "${!expected_output}" ]; then
        echo "Test $x passed! Output matches the expected test output."
    else
        echo "Test $x failed! Output does not match the expected test output."
    fi
}

# Function to modify the value of variable x in the source code
modify_variable() {
    new_value="$1"
    sed -i "s/int x = [0-9]\+/int x = $new_value/" $source_code
}

# Main execution starts here
compile_code

rm -f log.out # this removes the previous log file
if [ $? -eq 0 ]; then
    echo "Code compiled successfully!"
    for test_number in "${test_numbers[@]}"; do
        x=$test_number
	echo " "
        echo "Running Test $x ..." | tee -a log.out
        modify_variable $x # Update X
        compile_code | tee -a log.out # Recompile 
        run_code | tee -a log.out # Run the executable
        compare_output | tee -a log.out # Check if it passed
    done
else
    echo "Compilation failed. Please check your source code."
fi

echo "These tests do not represent the complete set of tests that will be run to grade your code." | tee -a log.out

# Cleanup temporary files
rm -f program_output.txt $executable
