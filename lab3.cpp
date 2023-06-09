#include <iostream>
#include <string>
#include "queue.h"
#include "lab3_stack.h"

using namespace std;

int priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(char c) {
    return isdigit(c);
}

bool isValidExpression(const string& expression) {
    Stack<char> stack;
    Queue<char> queue;
    for (char c : expression) {
        if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            if (stack.empty() || stack.top() != '(') {
                return false;
            }
            stack.pop();
        }
        else if (isOperand(c)) {
            queue.push(c);
        }
        else if (isOperator(c)) {
            while (!stack.empty() && isOperator(stack.top()) && (
                (c == '+' || c == '-') && (stack.top() == '*' || stack.top() == '/') ||
                (c == '*' || c == '/')
                )) {
                queue.push(stack.top());
                stack.pop();
            }
            stack.push(c);
        }
        else {
            return false;
        }
    }
    while (!stack.empty()) {
        if (!isOperator(stack.top())) {
            return false;
        }
        queue.push(stack.top());
        stack.pop();
    }
    return true;
}


string to_postfix(string infix) {
    Stack<char> stack;
    Queue<char> queue;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isOperand(c)) {
            queue.push(c);
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                queue.push(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else {
            while (!stack.empty() && priority(c) <= priority(stack.top())) {
                queue.push(stack.top());
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty()) {
        queue.push(stack.top());
        stack.pop();
    }

    string postfix;
    while (!queue.empty()) {
        postfix += queue.front();
        queue.pop();
    }

    return postfix;
}

int evaluate(string postfix) {
    Stack<int> stack;
        for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (isOperand(c)) {
            stack.push(c - '0');
        }
        else {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            switch (c) {
            case '+':
                stack.push(a + b);
                break;
            case '-':
                stack.push(a - b);
                break;
            case '*':
                stack.push(a * b);
                break;
            case '/':
                stack.push(a / b);
                break;
            case '^':
                stack.push(pow(a, b));
                break;
            }
        }
    }

    return stack.top();
}

int main() {
    string infix = "1+2*3-4/4";
    string postfix = to_postfix(infix); 
    if (isValidExpression(infix)) {
        cout << "Infix: " << infix << endl;
        cout << "Postfix: " << postfix << endl;
        int result = evaluate(postfix);
        cout << "Result: " << result << endl;
        return 0;
    }
    else cout << "Invalid expression." << endl;
}
