#=================================================================
# Copyright 2023 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# HW2-2
# Student Name: Mythri Muralikannan
# Date:10/03/2023
#
#     Find George Variably Scaled
#
# This routine finds an exact match of George's face which may be
# scaled in a crowd of faces.
#
#===========================================================================
# CHANGE LOG: brief description of changes made from P1-2-shell.asm
# to this version of code.
# Date  Modification
# 10/02 Copied the C Code to MIPS 
# 10/03 Reduced number of match conditions from 5 to 4
# 10/03 Working on changing the code from Row and column to just the index 
# 10/03 Working on using load word instead of load byte
#===========================================================================

.data
Array:  .alloc	1024

.text

FindGeorge:	addi	$1, $0, Array		# point to array base
        # addi $2,$0, -1  #COMMENT OUT IN THE END!!!
		swi	592			# generate crowd



	    # your code goes here


		addi $2, $0, 0   #topLeft in $2
		addi $3, $0, 0   #bottomRight in $3

        #future variables for the 4 match conditions
		addi $4, $0, 0x08 #checks (77) mouth is a smile and right color
		addi $5, $0, 0x03 #checks (56) eye color
		addi $6, $0, 0x05 #checks (57) skincolor and for no sunglasses 
        addi $7, $0, 0x01 #checks (37) hat design 

        addi $8, $0, 0x07 #shirt color

		#Current index 
		addi $9, $1, 4095 #start at lastindex

IndLoop:	slt $10, $9, $1   
        bne $10, $0, Exit       #If current index is less than base address exit loop 

		lb $11, 0($9)           #load current byte
		beq $11, $8, MatchCheck #if current byte is green, possible match

		addi $9, $9, -5         #decrement index by 5
		j IndLoop               #enter outer loop again

MatchCheck:	addi $13, $9, 64    #check if old scaled 
        lb $11, 0($13)          #load current byte $13
		beq $11, $8, SkipOld  #stop checking

        addi $12, $0, 1          #store the scaling factor
        addi $13, $9, -64        #get temp index for calc

SfLoop:	lb $11, 0($13)          #load current byte $13
        bne $11, $8, SfExit     #if not green exit loop
		addi $12, $12, 1        #increment scaling factor
		addi $13, $13, -64      #check upper row 
		j SfLoop                #enter scaling factor loop again     


SfExit: addi $10, $0, 1         #check if scaling factor is 1
        beq $12, $10, Sf1

		addi $10, $0, 2         #check if scaling factor is 2
        beq $12, $10, Sf2

		addi $10, $0, 3         #check if scaling factor is 3
        beq $12, $10, Sf3

		addi $10, $0, 4         #check if scaling factor is 4
        beq $12, $10, Sf4

		addi $10, $0, 5         #check if scaling factor is 5
        beq $12, $10, Sf5

Sf1:    addi $9, $9, 1          #increment by one pixel
        lb $11, 0($9)           #load current byte 
		beq $11, $8, Sf1        #check if reached end of hat  

		addi $9, $9, 3 		    #bottom index sF*4 -1
		add $3, $9, $0          #store in bottom index

		#check george[7][7]
		addi $13, $3, -260
		lb $11, 0($13)
		bne $11, $4, ExitCheck    #if the mouth isnt a smile or black exit

		#check george[3][7]
		addi $13, $3, -516
		lb $11, 0($13)
		bne $11, $7, ExitCheck    #if the hat is the right type

		#check george[5][6]
		addi $13, $3, -389
		lb $11, 0($13)
		bne $11, $5, ExitCheck    #if eye color is right

		#check george[5][7]
		addi $13, $3, -388
		lb $11, 0($13)
		bne $11, $6, ExitCheck    #if skin color is right and for sunglasses


        addi $2, $3, -715          #Match found store top left
		j Exit


Sf2:    addi $9, $9, 1          #increment by two pixels
        lb $11, 0($9)           #load current byte 
		beq $11, $8, Sf2        #check if reached end of hat  

		addi $9, $9, 7 		    #bottom index
		add $3, $9, $0          #store in bottom index

		#check george[7][7]
		addi $13, $3, -520
		lb $11, 0($13)
		bne $11, $4, ExitCheck    #if the mouth isnt a smile or black exit

		#check george[3][7]
		addi $13, $3, -1032
		lb $11, 0($13)
		bne $11, $7, ExitCheck    #if the hat is the right type

		#check george[5][6]
		addi $13, $3, -778
		lb $11, 0($13)
		bne $11, $5, ExitCheck    #if eye color is right

		#check george[5][7]
		addi $13, $3, -776
		lb $11, 0($13)
		bne $11, $6, ExitCheck    #if skin color is right and for sunglasses


        addi $2, $3, -1495          #Match found store top left
		j Exit

Sf3:	addi $9, $9, 1          #increment by three pixels
        lb $11, 0($9)           #load current byte 
		beq $11, $8, Sf3        #check if reached end of hat  

		addi $9, $9, 11 		    #bottom index
		add $3, $9, $0          #store in bottom index

		#check george[7][7]
		addi $13, $3, -780
		lb $11, 0($13)
		bne $11, $4, ExitCheck    #if the mouth isnt a smile or black exit

		#check george[3][7]
		addi $13, $3, -1548
		lb $11, 0($13)
		bne $11, $7, ExitCheck    #if the hat is the right type

		#check george[5][6]
		addi $13, $3, -1167
		lb $11, 0($13)
		bne $11, $5, ExitCheck    #if eye color is right

		#check george[5][7]
		addi $13, $3, -1164
		lb $11, 0($13)
		bne $11, $6, ExitCheck    #if skin color is right and for sunglasses


        addi $2, $3, -2275         #Match found store top left
		j Exit

Sf4:	addi $9, $9, 1          #increment by four pixels
        lb $11, 0($9)           #load current byte 
		beq $11, $8, Sf4        #check if reached end of hat  

		addi $9, $9, 15 		    #bottom index
		add $3, $9, $0          #store in bottom index

		#check george[7][7]
		addi $13, $3, -1040
		lb $11, 0($13)
		bne $11, $4, ExitCheck    #if the mouth isnt a smile or black exit

		#check george[3][7]
		addi $13, $3, -2064
		lb $11, 0($13)
		bne $11, $7, ExitCheck    #if the hat is the right type

		#check george[5][6]
		addi $13, $3, -1556
		lb $11, 0($13)
		bne $11, $5, ExitCheck    #if eye color is right

		#check george[5][7]
		addi $13, $3, -1552
		lb $11, 0($13)
		bne $11, $6, ExitCheck    #if skin color is right and for sunglasses


        addi $2, $3, -3055          #Match found store top left
		j Exit

Sf5:	addi $9, $9, 1          #increment by five pixels
        lb $11, 0($9)           #load current byte 
		beq $11, $8, Sf5        #check if reached end of hat  

		addi $9, $9, 19 		    #bottom index
		add $3, $9, $0          #store in bottom index

		#check george[7][7]
		addi $13, $3, -1300
		lb $11, 0($13)
		bne $11, $4, ExitCheck    #if the mouth isnt a smile or black exit

		#check george[3][7]
		addi $13, $3, -2580
		lb $11, 0($13)
		bne $11, $7, ExitCheck    #if the hat is the right type

		#check george[5][6]
		addi $13, $3, -1945
		lb $11, 0($13)
		bne $11, $5, ExitCheck    #if eye color is right

		#check george[5][7]
		addi $13, $3, -1940
		lb $11, 0($13)
		bne $11, $6, ExitCheck    #if skin color is right and for sunglasses


        addi $2, $3, -3835          #Match found store top left
		j Exit

SkipOld:	addi $9, $9, -5        #If old then skip 
        lb $11, 0($9)
        beq $11, $8, SkipOld
		j IndLoop 		    

ExitCheck:	addi $10, $0, 12
           mult $10, $12      #multiply 12 by the scaling factor  
		   mflo $10
		   sub $9, $9, $10    #shift the current index from bottom left location to after the pattern
		   j IndLoop

Exit:	sub $2, $2, $1        #get topLeft index 
        sub $3, $3, $1        #get bottomRight index 
        sll $2, $2, 16   	  #shift top left to occupy the upper 8 blocks
        or $2, $2, $3         #or with the bottom right to submit final answer


		# *****************************************************
		# The following instructions only demo the swi's.
	        # They should be replaced with your code.
        #        addi    $2, $0, 160             # mark the 160th pixel
		#swi	552			# with this swi
        #        addi    $2, $0, 161             # mark the 161th pixel
		#swi	552			# with this swi
	

    	#lui     $2, 300                 # guess the 300th pixel for top left corner
	    #    ori     $2, $2, 1015            # and the 1015th pixel for bottom right
		### The above instructions are temporary (replace them).
		# *****************************************************

		swi	593			# submit answer and check
	        # *****************************************************
		# This unpacks the answer given by the oracle into:
		# $4: top left pixel location
		# $5: bottom right pixel location
		# TEMPORARY (can omit):
		srl     $4, $3, 16              # top left pixel location
		andi    $5, $3, 0xFFFF		# bottom right pixel location
		# *****************************************************

		jr	$31			# return to caller
