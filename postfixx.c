//Program to convert from infix to postfix.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function to set the precedence.
int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to return the associativity of the operators.
char associativity(char c)
{
    if (c == '^')
        return 'R';
    return 'L'; // Default to left-associative
}

// Function to convert infix to postfix.
void infixToPostfix(char S[])
{
    char result[1000];
    int resultIndex = 0;
    int len = strlen(S);
    char stack[1000];
    int stackIndex = -1;
    int i;

    for (i = 0; i < len; i++)
    {
        char c = S[i];

        // If the scanned character is an operand, add it to the output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            result[resultIndex++] = c;
        }
        // If the scanned character is '(', push it to the stack.
        else if (c == '(')
        {
            stack[++stackIndex] = c;
        }
        // If the scanned character is ')', pop and add to the output string from the stack.
        else if (c == ')')
        {
            while (stackIndex >= 0 && stack[stackIndex] != '(')
            {
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop '('
        }
        // If an operator is scanned.
        else
        {
            while (stackIndex >= 0 && (precedence(S[i]) < precedence(stack[stackIndex]) ||
                                       (precedence(S[i]) == precedence(stack[stackIndex]) &&
                                        associativity(S[i]) == 'L')))
            {
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    // Pop all the remaining elements from the stack.
    while (stackIndex >= 0)
    {
        result[resultIndex++] = stack[stackIndex--];
    }

    result[resultIndex] = '\0'; // Null-terminate the result string.
    printf("%s\n", result);
}

// Main function
int main()
{
    char expression[] = "a=b/c*d";
    infixToPostfix(expression); // Function call.
    return 0;
}
