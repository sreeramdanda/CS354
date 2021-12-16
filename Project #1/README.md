# Project #1: Username, Email, and Password Verification

In this project, I write basic code for verifying the correct formatting of a username, email address, and password for registration to a website.
The files written by me include:
- functions.c

The other files were provided as a foundation for the rest of the program or files for testing.
If the user enters an invalid username, email address, or password the function should print the appropriate error message and return 0.  We have written all the print statements for you.  The grading script uses exact output text matching.  If you change the error messages or print extra text your code will fail the tests in the grading script.

## Specifications
The code should test the username, email address, and password and only report the first error message.  Do not report everything wrong with an item, only the first error.  The error messages are listed in order for you in the functions.h file.

For example, the username must begin with a letter [A-Z, a-z], have a maximum of 32 characters, and may only contain letters, digits, or the underscore [A-Z, a-z, 0-9, _].  These conditions are tested in this order, so if the username is “CS354isThe_Best_Most_AwesomeClass!@#$%^&*(Ever)!!!”. The first test will pass (this should not generate any output), but the second test will fail because the username has 50 characters. When the second test fails, the output “Max 32 characters” is printed, the function returns 0.  The “Invalid character in username” error message is never printed.
