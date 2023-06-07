#include <iostream>
#include <cmath>

using namespace std;
int azat = 0;
struct Stack {
    double number;
    char znak;
    Stack* next;
};
Stack* top1, * top2;

void replace_ALL(string& s, string ss, string ch) {
    int pos = s.find(ss);
    while (pos != string::npos) {
        s.replace(pos, ss.length(), ch);
        pos = s.find(ss);
    }
}

void push(Stack*& t, double num, char znak) {
    Stack* p = (Stack*)malloc(sizeof(Stack));
    (*p).number = num;
    (*p).znak = znak;
    (*p).next = t;
    t = p;
}
Stack pop(Stack*& t) {
    Stack temp = *t;
    t = (*t).next;
    return temp;
}
int Error(string s) {
    int balance = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            balance++;
        } else if (s[i] == ')') {
            balance--;
        }

        if (balance < 0) {
            return -1;
        }
    }
    for (int j = 0; j < s.length(); j++) {
        if (s[j] >= 'a' && s[j] <= 'z') return -1;
    }
        if (s[0] == '*' || s[0] == '/') {
            return -1;
        }
        if (s[s.length()-1] == '*' || s[s.length()-1] == '/') {
            return -1;
            }

        for  (int i = 0; i <= s.length()-1; i++) {
            if (s[i] == '+' &&
                (s[i + 1] == '+' || s[i + 1] == '/' || s[i + 1] == '-' || s[i + 1] == '*') ||
                s[i] == '*' &&
                (s[i + 1] == '+' || s[i + 1] == '/' || s[i + 1] == '-' || s[i + 1] == '*') ||
                s[i] == '-' &&
                (s[i + 1] == '+' || s[i + 1] == '/' || s[i + 1] == '-' || s[i + 1] == '*') ||
                s[i] == '/' &&
                (s[i + 1] == '+' || s[i + 1] == '/' || s[i + 1] == '-' || s[i + 1] == '*')) {
                return -1;
                }
        }
        for (int i = 0; i < s.length()-1; i++) {
            if (s[i] == '(' && s[i+1] == '*' ||
                s[i] == '(' && s[i+1] == '/' ||
                s[i] == '(' && s[i+1] == '+') {
                return -1;
                }
        }
        for (int i = 0; i < s.length()-1; i++) {
           if (s[i] == '/' && s[i+1] == '0')
           return -1;
    }
        for (int i = 0; i < s.length()-1; i++) {
            if (s[i] == '*' && s[i+1] == ')' ||
                s[i] == '/' && s[i+1] == ')' ||
                s[i] == '+' && s[i+1] == ')' ||
                s[i] == '-' && s[i+1] == ')') {
                return -1;
                }
        }
    return 0;
}
void apply(char znak) {
    double a = pop(top1).number;
    if (znak == 'S'){
        push(top1, sin(a), '@');
        return;
    }
    if (znak == 'C'){
        push(top1, cos(a), '@');
        return;
    }
    if (znak == 'T') {
        push(top1, tan(a), '@');
        return;
    }
    if (znak == 'Q') {
        if (a < 0) {
            azat++;
        } else {
            push(top1, sqrt(a), '@');
        }
            return;
    }
    if (znak == 'L') {
        if (a <= 0) {
            azat++;
        } else {
            push(top1, log(a), '@');
        }
        return;
    }
    double b = pop(top1).number;
    if (znak == '+') push(top1, a + b, '@');
    if (znak == '-') push(top1, b - a, '@');
    if (znak == '^') push(top1, pow(b, a), '@');
    if (znak == '*') push(top1, a * b, '@');
    if (znak == '/') {
        if (a == 0) {
            azat++;
        }
    push(top1, b / a, '@');
    }
}

int prior(char d) {
    if (d == '(') return 0;
    if (d == '+' || d == '-')  return 1;
    if (d == '*' || d == '/')  return 2;
    if (d == '^' || d == 'Q') return 3;
    if (d == 'S' || d == 'C' || d == 'T'  || d == 'L') return 4;
}

int calc(string s, double &ans) {
    string ss;
    azat = 0;
    replace_ALL(s, "sin", "S");
    replace_ALL(s, "cos", "C");
    replace_ALL(s, "tg", "T");
    replace_ALL(s, "ln", "L");
    replace_ALL(s, "sqrt", "Q");
    int pr = Error(s);
    if (pr == -1) return -1;
    if (s[0] == '-') s = '0' + s;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss = ss + "(0";
        } else {
            ss = ss + s[i];
        }
    }
    ss = ss + s[s.length() - 1];
    s = ss;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            double temp = 0;
            while ((s[i] >= '0' && s[i] <= '9') && i < s.length()) {
                    temp = temp * 10 + (s[i] - '0');
                    i++;
                    }
            if (s[i] == '.') {
                i++;
                double st = 10;
                while ((s[i] >= '0' && s[i] <= '9') && i < s.length()) {
                temp = temp*st + (s[i]- '0');
                temp = temp / st;
                st = st* 10;
                i++;
            }
       }
           //printf("%f  ", temp);

            i--;
            push(top1, temp, '@');
            temp = 0;
        }
        if (s[i] == '(') push(top2, 0.0, s[i]);

        if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
                if(azat){
                    return -1;
                }
            }
            pop(top2);
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == 'S' || s[i] == 'C' || s[i] == 'L' || s[i] == '^' || s[i] == 'T' || s[i] == 'Q') {
            while (top2 != nullptr && prior(s[i]) <= prior((*top2).znak)) {
                apply(pop(top2).znak);
                if(azat){
                    return -1;
                }
            }
            push(top2, 0, s[i]);
        }
    }
    while (top2 != nullptr) {
        apply(pop(top2).znak);
        if(azat){
            return -1;
        }
    }
       ans = pop(top1).number;
    printf("%f ", ans);
    if (azat != 0) return -1; else return 0;
}

