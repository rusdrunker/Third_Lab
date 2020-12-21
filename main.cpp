#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

void getToStack(stack<char>& operations, char& current, string& output) {
    if (current == '+' || current == '-') {
        operations.push(current);
    } else if (current == ')') {
        while (operations.top() != '(') {
            output.push_back(operations.top());
            output.push_back(' ');
            operations.pop();
        }
        operations.pop();

    } else {
        if (!operations.empty()) {
            if (current != '(' && (operations.top() == '*' || operations.top() == '/')) {
                output.push_back(operations.top());
                output.push_back(' ');
                operations.pop();
            }
        }
        operations.push(current);
    }
}

bool isOperator(const string& input) {
    if (input == "+" || input == "-" || input == "/" || input == "*") {
        return true;
    }
    return false;
}

void executeExpression(stack<int>& numbers, const string& operation) {
    int left, right, result;

    right = numbers.top();
    numbers.pop();

    left = numbers.top();
    numbers.pop();

    if (operation == "+") {
        result = left + right;
    } else if (operation == "-") {
        result = left - right;
    } else if (operation == "*") {
        result = left * right;
    } else {
        if (right == 0) {
            throw invalid_argument("Division by zero");
        }
        result = left / right;
    }

    numbers.push(result);
}

int main() {
    string output;
    stack<char> operations;
    string input;

    getline(cin, input);

    istringstream expression(input);

    while (!expression.eof()) {
        char tmp = ' ';
        expression >> tmp;
        if (tmp != '+' && tmp != '-' && tmp != '*' && tmp != '/'
            && tmp != '(' && tmp != ')' &&tmp != ' ') {
            output.push_back(tmp);
            output.push_back(' ');
        } else if (tmp != ' ') {
            getToStack(operations, tmp, output);
        }

    }

    while (!operations.empty()) {
        output.push_back(operations.top());
        output.push_back(' ');
        operations.pop();
    }

    cout << output << " Reverse Polish notation" << endl;

    stack<int> result;

    int number;
    stringstream prev_output(output);
    while (!prev_output.eof()) {
        string new_input = " ";
        prev_output >> new_input;

        if (isOperator(new_input)) {
            try {
                executeExpression(result, new_input);
            } catch (exception& e) {
                cerr << e.what();
            }
        } else if (new_input != " "){
            istringstream(new_input) >> number;
            result.push(number);
        }
    }

    cout << result.top();


    return 0;
}
