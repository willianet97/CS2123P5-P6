# Define the machine object files for your program
  2 OBJECTS = driver.o insert.o print.o chain.o
  3 # Define your include file
  4 INCLUDES = cs2123p5.h
  5
  6 # make for the executable
  7 p5: ${OBJECTS}
  8         gcc -g -o p5 ${OBJECTS}
  9
 10 # Simple suffix rules for the .o
 11 %.o: %.c ${INCLUDES}
 12         gcc -g -c $<
 13
 14 # Clean the .o files
 15 clean:
 16         rm -f ${OBJECTS}
