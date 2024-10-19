#include <iostream>
#include <cstring>
using namespace std;

// Template Node class for Linked List
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T d) : data(d), next(NULL) {}
};

// Template Stack class using linked list
template <typename T>
class Stack {
private:
    Node<T>* top;

public:
    Stack() { top = NULL; }

    bool isEmpty() {
        return top == NULL;
    }

    void push(T x) {
        Node<T>* temp = new Node<T>(x);
        temp->next = top;
        top = temp;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        } else {
            T x = top->data;
            Node<T>* temp = top;
            top = top->next;
            delete temp;
            return x;
        }
    }

    T peek() {
        if (!isEmpty())
            return top->data;
        else
            return -1;
    }
};

// Template class for Expression
template <typename T>
class Expression {
private:
    char infix[100];
    char postfix[100];
    char prefix[100];

    int precedence(char ch) {
        if (ch == '+' || ch == '-') return 1;
        if (ch == '*' || ch == '/') return 2;
        return 0;
    }

    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    void reverse(char* exp) {
        int n = strlen(exp);
        for (int i = 0; i < n / 2; i++) {
            swap(exp[i], exp[n - i - 1]);
        }
    }

    string infixToPostfixHelper() {
        Stack<char> s;
        int k = 0;
        for (int i = 0; infix[i] != '\0'; i++) {
            if (isalnum(infix[i])) {
                postfix[k++] = infix[i];
            } else if (infix[i] == '(') {
                s.push('(');
            } else if (infix[i] == ')') {
                while (!s.isEmpty() && s.peek() != '(') {
                    postfix[k++] = s.pop();
                }
                s.pop(); // Remove '(' from stack
            } else {
                while (!s.isEmpty() && precedence(s.peek()) >= precedence(infix[i])) {
                    postfix[k++] = s.pop();
                }
                s.push(infix[i]);
            }
        }
        while (!s.isEmpty()) {
            postfix[k++] = s.pop();
        }
        postfix[k] = '\0';
        return postfix;
    }

    string infixToPrefixHelper() {
        reverse(infix);
        for (int i = 0; infix[i] != '\0'; i++) {
            if (infix[i] == '(') infix[i] = ')';
            else if (infix[i] == ')') infix[i] = '(';
        }
        infixToPostfixHelper();
        strcpy(prefix, postfix);
        reverse(prefix);
        return prefix;
    }

    T evaluatePostfixHelper() {
        Stack<T> s;
        for (int i = 0; postfix[i] != '\0'; i++) {
            if (isdigit(postfix[i])) {
                s.push(postfix[i] - '0');
            } else {
                T val1 = s.pop();
                T val2 = s.pop();
                switch (postfix[i]) {
                    case '+': s.push(val2 + val1); break;
                    case '-': s.push(val2 - val1); break;
                    case '*': s.push(val2 * val1); break;
                    case '/': s.push(val2 / val1); break;
                }
            }
        }
        return s.pop();
    }

    T evaluatePrefixHelper() {
        Stack<T> s;
        reverse(prefix);  // Evaluate prefix in reverse order
        for (int i = 0; prefix[i] != '\0'; i++) {
            if (isdigit(prefix[i])) {
                s.push(prefix[i] - '0');
            } else {
                T val1 = s.pop();
                T val2 = s.pop();
                switch (prefix[i]) {
                    case '+': s.push(val1 + val2); break;
                    case '-': s.push(val1 - val2); break;
                    case '*': s.push(val1 * val2); break;
                    case '/': s.push(val1 / val2); break;
                }
            }
        }
        return s.pop();
    }

public:
    void readExpression() {
        cout << "Enter the infix expression: ";
        cin >> infix;
    }

    void convertInfixToPostfix() {
        cout << "Postfix expression: " << infixToPostfixHelper() << endl;
    }

    void convertInfixToPrefix() {
        cout << "Prefix expression: " << infixToPrefixHelper() << endl;
    }

    void evaluatePostfix() {
        cout << "Evaluated result of postfix: " << evaluatePostfixHelper() << endl;
    }

    void evaluatePrefix() {
        cout << "Evaluated result of prefix: " << evaluatePrefixHelper() << endl;
    }
};

int main() {
    Expression<int> expr;
    int choice;
    do {
        cout << "\nMenu\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Convert Infix to Prefix\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Evaluate Prefix Expression\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                expr.readExpression();
                expr.convertInfixToPostfix();
                break;
            case 2:
                expr.readExpression();
                expr.convertInfixToPrefix();
                break;
            case 3:
                expr.readExpression();
                expr.convertInfixToPostfix();
                expr.evaluatePostfix();
                break;
            case 4:
                expr.readExpression();
                expr.convertInfixToPrefix();
                expr.evaluatePrefix();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}