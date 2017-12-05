/*
Redundant Braces

Write a program to validate if the input string has redundant braces?
Return 0/1

0 -> NO
1 -> YES

Input will be always a valid expression

and operators allowed are only + , * , - , /

Example:

((a + b)) has redundant braces so answer will be 1
(a + (a + b)) doesn't have have any redundant braces so answer will be 0
*/

int Solution::braces(string A) {
    std::stack<char> subop;
    int len = A.length();
    
    for(int i=0; i<len; i++) {
        char c = A[i];
        
        if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(')
            subop.push(c);
        else if(c==')') {
            if(subop.top() == '(') return 1;
            else while(!subop.empty() && subop.top() != '(') subop.pop();
            subop.pop();
        }
    }
    
    return 0;
}

