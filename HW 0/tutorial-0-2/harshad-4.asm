Joy2:  addiu $1, $0, 42    	   # set $1 to 42 (input to program)
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $5, $0, 0		   # initialize running sum to 0
Loop:  andi  $4, $1, 1		   # extract least significant bit
       add   $5, $5, $4		   # add it to the running sum
       sra   $1, $1, 1		   # shift x right by 1 bit
       bne   $1, $0, Loop	   # if x still has non-zero bits, keep looping
Exit:  div   $11, $5		   # divide original value of x by sum
       mfhi  $6			   # transfer the remainder to $6
       beq   $6, $0, Yes	   # is remainder = 0? (sum is a factor?)
       addi  $8, $0, 0		   # if not, $8 = 0
       j     End    		   # and jump to the End return statement
Yes:   addi  $8, $0, 1		   # if so, x is a Harshad: $8 = 1
End:   jr    $31		   # return to caller
