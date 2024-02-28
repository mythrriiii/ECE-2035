Joy2:  addiu $1, $0, 42    	   # set $1 to 42 (input to program)
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $2, $0, 0		   # initialize loop counter
       addi  $3, $0, 32		   # set upper limit
Loop:  bne   $2, $3, Exit	   # if counter reaches upper limit, exit loop
       
       addi  $2, $2, 1		   # update the loop counter
       j     Loop    		   # loop back
Exit:  jr    $31		   # return to caller