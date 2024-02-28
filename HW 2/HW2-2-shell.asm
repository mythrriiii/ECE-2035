#=================================================================
# Copyright 2023 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# HW2-2
# Student Name:
# Date:
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
# <insert date>					<student name here>
	
.data
Harry:  .alloc  10               # allocate static space for 5 moves
Sally:  .alloc  10               # allocate static space for 5 moves

.text
WhereMet:	addi  $1, $0, Harry     # set memory base
        	swi     586             # create timelines and store them
	
		# add more code here.

		addi    $2, $0, 777	# guess 777 (TEMP: replace this)

		swi   594		# give answer
                jr    $31               # return to caller
