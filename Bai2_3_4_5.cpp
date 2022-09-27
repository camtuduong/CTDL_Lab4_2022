#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

#define MAX 100

typedef struct stack
{
    char data[MAX];
    int length = 0;
} Stack;

bool isEmpty(Stack stack)
{
    return stack.length == 0;
}

bool isFull(Stack stack)
{
    return stack.length == MAX - 1;
}

bool push(Stack &stack, char value)
{
    if (isFull(stack))
    {
        return false;
    }
    stack.data[stack.length++] = value;
    return true;
}

char pop(Stack &stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack.data[--stack.length];
}

char getLast(Stack stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack.data[stack.length - 1];
}

int prec(char c)
{
    if (c == '^')
    {
        return 3;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return NULL;
    }
}

string infixToPostfix(string infix)
{
    string postfix;
    char token;
    Stack stack;
    int i;

    for (i = 0; i < infix.length(); i++)
    {
        token = infix[i];
        if (token >= '0' && token <= '9')
        {
            postfix += token;
            continue;
        }
        else if (token == '(')
        {
            push(stack, token);
            continue;
        }
        else if (token == ')')
        {
            while (!isEmpty(stack) && getLast(stack) != '(')
            {
                postfix += pop(stack);
            }
            if (!isEmpty(stack))
            {
                pop(stack);
            }
            continue;
        }
        else
        {
            while (!isEmpty(stack) && prec(getLast(stack)) >= prec(token))
            {
                postfix += pop(stack);
            }
            push(stack, token);
        }
    }
    while (!isEmpty(stack))
    {
        postfix += pop(stack);
    }
    return postfix;
}

string infixToPrefix(string infix)
{
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.length(); i++)
    {

        if (infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
        }
    }
    string prefix = infixToPostfix(infix);
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

float scanNum(char ch)
{
    int value;
    value = ch;
    return float(value - '0');
}
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return 1;
    return -1;
}
int isOperand(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return -1;
}
float operation(int a, int b, char op)
{

    if (op == '+')
        return b + a;
    else if (op == '-')
        return b - a;
    else if (op == '*')
        return b * a;
    else if (op == '/')
        return b / a;
    else if (op == '^')
        return pow(b, a);
    else
        return INT_MIN;
}
float postfixEval(string postfix)
{
    int a, b;
    Stack stack;
    string::iterator it;
    for (it = postfix.begin(); it != postfix.end(); it++)
    {
        if (isOperator(*it) != -1)
        {
            a = pop(stack);
            b = pop(stack);
            push(stack, operation(a, b, *it));
        }
        else if (isOperand(*it) > 0)
        {
            push(stack, scanNum(*it));
        }
    }
    return getLast(stack);
}

float prefixToEval(string prefix)
{
    reverse(prefix.begin(), prefix.end());
    return postfixEval(prefix);
}

int main()
{
    return 0;
}