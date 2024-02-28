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
# 10/03 Worked on changing the code from Row and column to just the index 
# 10/03 Worked on using load word instead of load byte
# 10/05 Minor debugging
# 10/05 Changed sF*3 condition to sF*4 - 1 to get bottomRight
# 10/07 Skip by 1 and not sF
# 10/09 Remove if statements and invidual code blocks for each sF
# 10/10 Reduce register count to minimum -> 6
# 10/10 Trying to address post scaled skip, to get rid of infinite loop error

#===========================================================================

.data
Array:  .alloc	1024

.text

FindGeorge:	addi	$1, $0, Array		# point to array base
        # addi $2,$0, -1  #COMMENT OUT IN THE END!!!
		swi	592			# generate crowd



	    # your code goes here


		#topLeft in $2
		#bottomRight in $9

        addi $2, $0, 0x07 #shirt color

		#Current index 
		addi $4, $1, 4095 #start at lastindex

IndLoop:	slt $10, $4, $1   
        bne $10, $0, Exit       #If current index is less than base address exit loop 

		lb $10, 0($4)           #load current byte
		beq $10, $2, MatchCheck #if current byte is green, possible match

		addi $4, $4, -5         #decrement index by 5
		j IndLoop               #enter outer loop again

MatchCheck:	addi $5, $0, 1          #store the scaling factor
        addi $3, $4, -64        #get temp index for calc

SfLoop:	lb $10, 0($3)          #load current byte $13
        bne $10, $2, SfExit     #if not green exit loop
		addi $5, $5, 1        #increment scaling factor
		addi $3, $3, -64      #check upper row 
		j SfLoop                #enter scaling factor loop again     


SfExit: addi $4, $4, 1          #increment by one pixel
        lb $10, 0($4)           #load current byte 
		beq $10, $2, SfExit        #check if reached end of hat 

        sll $10, $5, 2         #sF*4
        addi $10, $10, -1       #sF*4 - 1
        add $4, $4, $10         #bottom index + sF*4 - 1

#TEST   
        #check george[7][7]           
    	addi $3, $0, -260       
        mult $3, $5
        mflo $3
        add  $3, $3, $4, 
        lb $10, 0($3)
        addi $2, $0, 0x08         #checks (77) mouth is a smile and right color
		bne $10, $2, ExitCheck    #if the mouth isnt a smile or black exit


        #check george[3][7]           
    	addi $3, $0, -516       
        mult $3, $5
        mflo $3
        add  $3, $3, $4, 
        lb $10, 0($3)
        addi $2, $0, 0x01         #checks (37) hat design 
		bne $10, $2, ExitCheck    #if the hat is the right type


        #check george[5][6]           
    	addi $3, $0, -389       
        mult $3, $5
        mflo $3
        add  $3, $3, $4, 
        lb $10, 0($3)
        addi $2, $0, 0x03         #checks (56) eye color
		bne $10, $2, ExitCheck    #if eye color is right


		#check george[5][7]
		addi $3, $0, -388       
        mult $3, $5
        mflo $3
        add  $3, $3, $4, 
        lb $10, 0($3)
        addi $2, $0, 0x05         #checks (57) skincolor and for no sunglasses 
		bne $10, $2, ExitCheck    #if skin color is right and for sunglasses

        #Match found
        addi $2, $4, -715
        addi $10, $0, 1          #store 1 in $10

TopLeft:    beq $5, $10, Exit   #calculate top left according to scaling factor
        addi $2, $2, -780
        addi $5, $5, -1
        j TopLeft

ExitCheck:	addi $10, $0, 12
           mult $10, $5      #multiply 12 by the scaling factor  
		   mflo $10
		   sub $4, $4, $10    #shift the current index from bottom left location to after the pattern
           addi $2, $0, 0x07  #shirt color

		   j IndLoop

Exit:	sub $2, $2, $1        #get topLeft index 
        sub $4, $4, $1        #get bottomRight index 
        sll $2, $2, 16   	  #shift top left to occupy the upper 8 blocks
        or $2, $2, $4         #or with the bottom right to submit final answer


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
