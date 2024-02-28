Joy2:  addiu $1, $0, 42    	   # set $1 to 42 (input to program)
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $2, $0, 0		   # initialize loop counter
       addi  $3, $0, 32		   # set upper limit
       addi  $5, $0, 0		   # initialize running sum to 0
Loop:  beq   $2, $3, Exit	   # if counter reaches upper limit, exit loop
       andi  $4, $1, 1		   # extract least significant bit
       add   $5, $5, $4		   # add it to the running sum
       srl   $1, $1, 1		   # shift x right by 1 bit
       addi  $2, $2, 1		   # update the loop counter
       j    Loop    		   # loop back
Exit:  jr    $31		   # return to caller

