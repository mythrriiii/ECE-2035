.data
XLoc:  .word  42
ALoc:  .alloc 1

.text
Joy2:  lw    $1, XLoc($0)    	   # read input to program from memory into $1
       addiu $11, $1, 0		   # save a copy of x in $11
       addi  $5, $0, 0		   # initialize running sum to 0
Loop:  andi  $4, $1, 1		   # extract least significant bit
       add   $5, $5, $4		   # add it to the running sum
       srl   $1, $1, 1		   # shift x right by 1 bit
       bne   $1, $0, Loop	   # if x still has non-zero bits, keep looping
Exit:  div   $11, $5		   # divide original value of x by sum
       mfhi  $6			   # transfer the remainder to $6
       beq   $6, $0, Yes	   # is remainder = 0? (sum is a factor?)
       addi  $8, $0, 0		   # if not, $8 = 0
       j     End    		   # and jump to the End to store result (0)
Yes:   addi  $8, $0, 1		   # if so, x is a Harshad: $8 = 1
End:   sw    $8, ALoc($0)	   # store result ($8) at memory location ALoc
       jr    $31		   # return to caller
