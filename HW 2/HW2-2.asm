#=================================================================
# Copyright 2023 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# HW2-2
# Student Name: Mythri Muralikannan
# Date: 09/10/2023
#
#     Where Harry Met Sally
#
#
# This program determines when Harry and Sally first resided in the same city
# and reports the ID of that city.
#
#  required output register usage:
#  $2: common city ID
#
# 09/10/2023					Mythri Muralikannan
	
.data
Harry:  .alloc  10               # allocate static space for 5 moves
Sally:  .alloc  10               # allocate static space for 5 moves

.text
WhereMet:	addi  $1, $0, Harry     # set memory base
        	swi     586             # create timelines and store them
	

# Register Tracker
#0 just 0
#1 Memory base, Harry i equivalent 
#2 Value to be returned
#3 Memory base, Sally j equivalent
#4 Harry timeline current date / city
#5 Sally timeline current date / city
#6 slt register
#7 Harry loop end index
#8 Sally loop end index
#9 slt register
#10 set to 0 to to debug the no work statements

		# add more code here.
            addi $2, $0, -99        # value to return if there is no match	 
			
			addi $3, $0, Sally      # set memory base for sally

Loop1:      lw $4, 8($1)			# load Harry[i+2] 
            lw $5, 0($3)            # load Sally[j]

			slt $6, $5, $4          # compare Sally[j] < Harry[i+2] 

			bne $6, $0, endLoop1    # if Harry[i+2] > Sally[j], exit loop
			addi $1, $1, 8          # set current harry date pointer from i to i+2

			j Loop1


endLoop1: 	add $9, $0, $0

Loop2:      lw $5, 8($3)            # load Sally[j+2]
            lw $4, 0($1)            # load Harry[i]

			slt $6, $4, $5          # compare Harry[i] < Sally[j+2]

			bne $6, $0, endLoop2    # if Harry[i] < Sally[j+2], exit loop
			addi $3, $3, 8          # set current sally date pointer from j to j+2

			j Loop2

endLoop2:   add $9, $0, $0
			addi $7, $0, Harry      
			addi $7, $7, 36          # loop terminating condition value

			addi $8, $0, Sally
			addi $8, $8, 36          # loop terminating condition value


Loop3:      lw $4, 4($1)            # load harry current city using current date in $1
            lw $5, 4($3)            # load sally current city using current date in $3

            slt $6, $1, $7          # check if i < 9
            slt $9, $3, $8          # check if j < 9

			and $6, $6, $9          # set 6 to (i < 9 && j < 9)

			beq $6, $0, Leave    # if (i < 9 && j < 9) is not true end loop

			bne $4, $5, Update
			add $2, $4, $0
			j Leave

Update:     lw $4, 8($1)            # load harry [i + 2]
            lw $5, 8($3)            # load sally [j + 2]

			bne $4, $5, compareUp
			addi $1, $1, 8
			addi $3, $3, 8
			j Loop3

compareUp: 	slt $6, $4, $5         #check if harry [i + 2] < sally [j + 2]
            beq $6, $0, sallyUp 
			addi $1, $1, 8
			j Loop3	

sallyUp:    addi $3, $3, 8
            j Loop3			

		#addi    $2, $0, 777	# guess 777 (TEMP: replace this)

Leave:		swi   594		# give answer
                jr    $31               # return to caller
