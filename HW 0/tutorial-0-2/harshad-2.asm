Joy2:  addiu $1, $0, 42    	   # set $1 to 42 (input to program)
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $5, $0, 0		   # initialize running sum to 0
Loop:  beq   $1, $0, Exit	   # if x has no non-zero bits, Exit
       andi  $4, $1, 1		   # extract least significant bit
       add   $5, $5, $4		   # add it to the running sum
       sra   $1, $1, 1		   # shift x right by 1 bit
       j     Loop    		   # loop back
Exit:  jr    $31		   # return to caller
