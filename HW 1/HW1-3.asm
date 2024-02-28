#=================================================================
# Copyright 2023 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# HW1-3
# Student Name: Mythri Muralikannan
# Date:09/04/23
#
# Assume 9 < x < 32,768.
# This program determines whether the square of x can be computed by
# 1) taking all but the least significant digit of x, adding this upper
#    number to the square of itself, and 
# 2) concatenating the result of step 1 to the 2-digit square of the least
# significant digit of x.
#
# For example, if x = 54, your program should determine whether 54^2 == 3016. 
#    1) 5^2+5 = 30
#    2) concat 30 w/ 4^2 = 16 to get 3016.
#
# Also, for HW1 (only), do not write values to registers $0, $29, $30, or $31
# and do NOT use helper functions or function calls (JAL).
#
# FOR FULL CREDIT (on all assignments in this class), BE SURE TO TRY
# MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

.data
# DO NOT change the following three labels (you may change the initial value):
xAddr:  .word 54        # xAddr will always be a random address in memory but
                        # will store what you put in. In this case it's 54.
                        # You might wanna change this for testing your code.
                        # You can refer to this random address location using
                        # the label 'xAddr'
			
# DO NOT Change the following allocations
SQAddr:	.alloc 1        # This basically states that we are allocating one word
                        # worth of memory. You can use SQAddr to refer to this memory location
AAddr:  .alloc 1
ResultAddr: .alloc 1    # You will store your result at this memory location
	
.text
        lw   $1, xAddr($0)      # Read the value at memory location xAddr into $1
        
        mult $1, $1             # Get the square of the number x
        mflo $2                 # Store it in $2    
        sw $2, SQAddr($0)           # Store it in SQAddr

        addi $3, $0, 10         # Store 10 in a register
        div $1, $3              # Divide x/10
        mfhi $4                 # The last digit or x%10
        mflo $5                 # The first few digits or x/10
        
        mult $4, $4             # Square Xlo
        mflo $4                 # Store in $4

        mult $5, $5             # Square Xhi
        mflo $6                 # Store in $6 
        add $5, $5, $6          # Add itself to the square and store back in $5

        addi $6, $0, 100        # Store 100 in a register
        mult $5, $6             # Mult the square by 100 
        mflo $7                 # Store it in $7
        add $7, $7, $4          # Add Xlo squared to it, this is A value

        sw $7, AAddr($0)            # Store it in AAddr  

        beq $2, $7, Then        # Check if SqAddr is equal to AAddr
Else:   addi $1, $0, 0          # The result is 0 and stored in $1  
        j End 
Then:   addi $1, $0, 1          # The result is 1 and stored in $1

                                # Put all your constants / initializations here. 
                                # Think what you instructions you can use to achieve the HW1 task.
                                # Feel free to change the given instructions and use different
                                # registers.  You may use the same register for more than one value.
				
End:    sw $1, ResultAddr($0)   # This stores the contents of $1 at the ResultAddr memory location
        jr $31                  # return to OS, This needs to be at the end of the program

