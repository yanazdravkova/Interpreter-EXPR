#include<iostream>
#include<rpnConverter.h>
using namespace std;
//used https://gist.github.com/mycodeschool/7867739
//идея - за да работим не само с цифри като числа, разделяме всеки елемент (число или операция) от RPN записа със запетая
bool isOperator(const char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c== '%')
		return true;
	return false;
}
bool isOperand(const char c)
{
	if(c >= '0' && c <= '9') return true;
	if(c >= 'a' && c <= 'z') return true;
	return false;
}
//ако операциите са с еднакъв приоритет, изпълнява се по-лявата в записа
string RPNConverter::toPostfix()
{
	string result = ""; // Initialize result as empty string.
	for(int i = 0;i< str.length();i++) {

		// opStackcanning each character from left.
		// If character is a delimitter, move on.
		if(str[i] == ' ') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(isOperator(str[i]))
		{
		    result += ',';
			while(!opStack.empty() && opStack.top() != '(' && (priority(opStack.top()) > priority(str[i])))
			{

				result += opStack.top();
				opStack.pop();
			}

			if(!opStack.empty() && opStack.top() != '(' && (priority(opStack.top()) == priority(str[i])))
            {
                char prev = opStack.top();
                opStack.pop();
                opStack.push(str[i]);
                opStack.push(prev);
            }
            else
                opStack.push(str[i]);

		}
		// Else if character is an operand
		else if(isOperand(str[i]))
		{

			result += str[i];
		}

		else if (str[i] == '(')
		{
			opStack.push(str[i]);
		}

		else if(str[i] == ')')
		{

			while(!opStack.empty() && opStack.top() !=  '(') {
              result += ',';
				result += opStack.top();
				opStack.pop();
			}
			opStack.pop();
		}
	}

	while(!opStack.empty())
	{
	    result += ',';
		result += opStack.top();
		opStack.pop();
	}

	return result;
}
