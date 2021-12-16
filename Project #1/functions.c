/******************************************************************************
 * @file: functions.c
 *
 * sdanda
 * Sreeram Danda
 * 9081904576
 *
 * @creator: Sreeram Danda (sdanda@wisc.edu)
 * @modified: 10/7/2021
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you
#define MAX_USERNAME_LEN 32
#define MAX_EMAIL_LEN 32
#define MAX_DOMAIN_LEN 64
#define MIN_PASSWORD_LEN 8
#define MAX_PASSWORD_LEN 16
#define NEW_LINE_CHAR 10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0
// before submitting!
#define DEBUG 0
#define dbgprintf(...)       \
    if (DEBUG)               \
    {                        \
        printf(__VA_ARGS__); \
    }

/******************************************************************************
 * Helper functions
 *****************************************************************************/
//Returns 1 if char is 'A-Z' or 'a-z', 0 otherwise
int isFirstLetterValid(char firstLetter)
{
    int decValueOfChar = firstLetter;

    if (decValueOfChar >= 65 && decValueOfChar <= 90)
    {
        return 1;
    }
    else if (decValueOfChar >= 97 && decValueOfChar <= 122)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Returns the length of a given character array
int getLength(char s[], int lim)
{
    int i;
    for (i = 0; i < lim; i++)
    {
        if (s[i] == '\0' || s[i] == '\n')
        {
            break;
        }
    }
    return i;
}

//Returns 1 if char is only numbers, letters, or underscore
int isValidLetters(char user[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int decValue = user[i];
        if ((decValue >= 65 && decValue <= 90) || (decValue >= 97 && decValue <= 122) || (decValue == 95) || (decValue >= 48 && decValue <= 57))
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

//Returns 1 if char array is only numbers and letters
int isOnlyLettersAndNums(char name[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int decValue = name[i];
        if ((decValue >= 65 && decValue <= 90) || (decValue >= 97 && decValue <= 122) || (decValue >= 48 && decValue <= 57))
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

//Returns index of first occurence of a given key in a char array
int search(char email[], char searchFor, int length)
{
    int key = searchFor;
    for (int i = 0; i < length; i++)
    {
        if (email[i] == key)
        {
            return i;
        }
    }
    return -1;
}

//Returns index of the last occurence of a given key in a char array
int searchBackwards(char email[], char searchFor, int length)
{
    int key = searchFor;
    for (int i = length - 1; i >= 0; i--)
    {
        if (email[i] == key)
        {
            return i;
        }
    }
    return -1;
}

//Returns 1 if the 4 given character are equal to ".com",".edu",".net"
int checkTopLevelDomain(char a, char b, char c, char d)
{
    int decValueA = a;
    int decValueB = b;
    int decValueC = c;
    int decValueD = d;

    if (decValueA == 46)
    {
        if (decValueB == 99 && decValueC == 111 && decValueD == 109)
        {
            return 1;
        }
        else if (decValueB == 101 && decValueC == 100 && decValueD == 117)
        {
            return 1;
        }
        else if (decValueB == 110 && decValueC == 101 && decValueD == 116)
        {
            return 1;
        }
    }

    return 0;
}

//Returns 1 if char is capital letter
int checkForCapital(char c)
{
    int decimalValue = c;
    if (decimalValue >= 65 && decimalValue <= 90)
    {
        return 1;
    }
    return 0;
}

//Returns 1 if char is lower case
int checkForLower(char c)
{
    int decimalValue = c;
    if (decimalValue >= 97 && decimalValue <= 122)
    {
        return 1;
    }
    return 0;
}

//Returns 1 if a character is a letter or a number
int isLetterOrNumber(char c)
{
    int decimalValue = c;
    if ((decimalValue >= 97 && decimalValue <= 122) || (decimalValue >= 65 && decimalValue <= 90) || (decimalValue >= 48 && decimalValue <= 57))
    {
        return 1;
    }
    return 0;
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len)
{

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");
    int lengthOfUsername = getLength(user, len);

    if (!isFirstLetterValid(user[0])) //Check first letter in username
    {
        printf(ERROR_01_USER_START_INVALID);
        return 0;
    }

    if (lengthOfUsername > MAX_USERNAME_LEN) //Check length of username
    {
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }

    if (!isValidLetters(user, lengthOfUsername)) //Check username validity
    {
        printf(ERROR_03_USER_CHARS_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len)
{
    /* BEGIN MODIFYING CODE HERE */
    int lengthOfEmail = getLength(email, len);                // length of the email address
    int posOfAt = search(email, '@', lengthOfEmail);          // index of the '@'
    int lastDot = searchBackwards(email, '.', lengthOfEmail); // index of the last '.'
    int sizeOfName = 0;                                       //Size of name part in email
    int topLevelDomainIsValid = checkTopLevelDomain(email[lengthOfEmail - 4], email[lengthOfEmail - 3], email[lengthOfEmail - 2], email[lengthOfEmail - 1]);
    int lengthOfDomain = lastDot - posOfAt - 1; //Length of domain

    //if top level domain does not exist
    if (!topLevelDomainIsValid)
    {
        if (posOfAt < 0) // @ doesnt exist
        {
            Verify_Username(email, len);
        }
        else if (posOfAt > 0) // @ exists
        {
            sizeOfName = posOfAt;
        }
        else // @ is first in the email
        {
            printf(ERROR_04_EMAIL_MISSING_NAME);
            return 0;
        }
    }
    else // top level domain exists
    {
        if (posOfAt < 0) // @ doesnt exist
        {
            sizeOfName = lastDot;
        }
        else if (posOfAt > 0) // @ exists
        {
            sizeOfName = posOfAt;
        }
        else //@ is first in the email
        {
            printf(ERROR_04_EMAIL_MISSING_NAME);
            return 0;
        }
    }

    // Separate name into its own array
    char name[sizeOfName];
    for (int i = 0; i < sizeOfName; i++)
    {
        name[i] = email[i];
    }

    // Is the first letter of name valid?
    if (!isFirstLetterValid(name[0]))
    {
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }

    // Is the size of the name valid?
    if (sizeOfName > 32)
    {
        printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
        return 0;
    }

    // Is the name made of valid characters?
    if (!isOnlyLettersAndNums(name, sizeOfName))
    {
        printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
        return 0;
    }

    // @ symbol missing
    if (posOfAt < 0)
    {
        printf(ERROR_08_EMAIL_MISSING_SYMBOL);
        return 0;
    }

    // no domain
    if (lengthOfDomain == 0)
    {
        printf(ERROR_09_EMAIL_MISSING_DOMAIN);
        return 0;
    }

    // domain exceeds maximum characters
    if (lengthOfDomain > 64)
    {
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }

    // separate domain into own array
    char domain[lengthOfDomain];
    for (int i = 0; i < lengthOfDomain; i++)
    {
        domain[i] = email[posOfAt + 1 + i];
    }

    // check subdomains are all valid
    for (int i = 0; i < lengthOfDomain; i++)
    {
        int decimalValue = domain[i];

        if (i == 0) // decimal at beginning of domain is invalid
        {
            if (!isFirstLetterValid(domain[i]))
            {
                printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                return 0;
            }
        }
        else if (i == lengthOfDomain - 1) // decimal at end of domain is invalid
        {
            if (!isLetterOrNumber(domain[i]))
            {
                printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
                return 0;
            }
        } // if a decimal is in middle of the domain
        else if (i != 0 || i != lengthOfDomain - 1)
        {
            if (decimalValue == 46)
            {
                if (!isFirstLetterValid(domain[i + 1])) // check the next letter is valid
                {
                    printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                    return 0;
                }
            }
            else
            {
                if (!isLetterOrNumber(domain[i])) // letter is not first letter of a subdomain so check it is valid
                {
                    printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
                    return 0;
                }
            }
        }
    }

    // Ensure top level domain exists and is valid
    if (!topLevelDomainIsValid)
    {
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len)
{

    /* BEGIN MODIFYING CODE HERE */
    int passwordLength = getLength(pwd, len);

    // Check for spaces
    for (int i = 0; i < passwordLength; i++)
    {
        int decimalValue = pwd[i];
        if (decimalValue == 32)
        {
            printf(ERROR_14_PWD_SPACES_INVALID);
            return 0;
        }
    }

    // Check min length
    if (passwordLength < 8)
    {
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }

    // Check max length
    if (passwordLength > 16)
    {
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }

    // Check for one capital and one lowercase
    int atLeastOneCapital = 0;
    int atLeastOneLower = 0;
    for (int i = 0; i < passwordLength; i++)
    {
        if (checkForCapital(pwd[i]))
        {
            atLeastOneCapital = 1;
        }
        else if (checkForLower(pwd[i]))
        {
            atLeastOneLower = 1;
        }
    }

    if (atLeastOneCapital == 0)
    {
        printf(ERROR_17_PWD_MIN_UPPER_INVALID);
        return 0;
    }

    if (atLeastOneLower == 0)
    {
        printf(ERROR_18_PWD_MIN_LOWER_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */
    return 1;
}

/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2)
{

    /* BEGIN MODIFYING CODE HERE */
    int pw1Length = getLength(pwd1, len1);
    int pw2Length = getLength(pwd2, len2);

    // Check both strings are same length and equalivalent to eachother
    if (pw1Length == pw2Length)
    {
        for (int i = 0; i < pw1Length; i++)
        {
            int decimalValue1 = pwd1[i];
            int decimalValue2 = pwd2[i];
            if (decimalValue1 != decimalValue2)
            {
                printf(ERROR_19_PWD_MATCH_INVALID);
                return 0;
            }
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH)
{
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */
    //Replace \n with \0
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        int decimalValue = data[i];
        if (decimalValue == 10)
        {
            data[i] = '\0';
        }
    }
    /* END MODIFYING CODE HERE */
    return;
}
