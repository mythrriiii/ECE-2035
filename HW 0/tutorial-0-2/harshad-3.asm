Joy2:  addiu $1, $0, 42    	   # set $1 to 42 (input to program)
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $5, $0, 0		   # initialize running sum to 0
Loop:  andi  $4, $1, 1		   # extract least significant bit
       add   $5, $5, $4		   # add it to the running sum
       sra   $1, $1, 1		   # shift x right by 1 bit
       bne   $1, $0, Loop	   # if x still has non-zero bits, keep looping
Exit:  jr    $31		   # return to caller
