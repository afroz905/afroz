#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to check if the character is an operand
bool isOperand(char ch) {
    return isalnum(ch); // Check if it's an alphanumeric character (operand)
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string expression) {
    stack<char> s;
    string postfix;

    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];

        // If the character is an operand, add it to the output
        if (isOperand(ch)) {
            postfix += ch;
        }
        // If the character is '(', push it onto the stack
        else if (ch == '(') {
            s.push(ch);
        }
        // If the character is ')', pop from the stack until '(' is found
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();  // Pop '(' from the stack
        }
        // If an operator is encountered
        else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);  // Push the current operator to the stack
        }
    }

    // Pop all the remaining operators from the stack
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int main() {
    string infix_expression = "(A + B) * (C - D) / E + F * G";

    // Remove spaces from the infix expression
    infix_expression.erase(remove(infix_expression.begin(), infix_expression.end(), ' '), infix_expression.end());

    string postfix_expression = infixToPostfix(infix_expression);
    cout << "Postfix Expression: " << postfix_expression << endl;

    return 0;
}

