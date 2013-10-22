#!/bin/bash

# Run this like so:
#
# > ./runner.sh ./pa06 images/02-unnormalized-cat-chess.ee264 outputs/output-2.ppm
#

# In this line, we run make, and if it _doesn't_ succeed,
# print an error message, and then exit with exit code "1"
printf "\nCompiling answer07.c\n"
! gcc -g -Wall -Wshadow -DMYTEST -o answer07 answer07.c && echo "Failed to build, aborting" && exit 1

# If the user failed to pass any arguments, or if the _first_ argument
# is not an executable file, then we want to print a nice
# friendly and soothing error message, to ease the user's disappointment,
# before we exit with an error code.
(( $# == 0 )) && echo "You forgot to pass me some arguments, aborting" && exit 1
! [ -x "$1" ] && \
    echo "Argument 1: '$1' is not a computer program, aborting" && \
    exit 1

# Here we explain what we're about to do...
echo
echo -n "Running valgrind with arguments: " 
echo "$@"
echo

# Run the program under valgrind with the passed arguments
valgrind --tool=memcheck --leak-check=full --verbose --log-file=valgrind-log.text "$@"

# Here we look at the log file, scan it for lines that say "ERROR SUMMARY"
# and then print out the last line that we find
printf "\nValgrind says: "
cat valgrind-log.text | grep "ERROR SUMMARY" | tail -n 1

