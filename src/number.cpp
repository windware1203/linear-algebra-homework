#include "../include/number.h"

int abs(int a){
    return a < 0 ? a * -1 : a;
}

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

void check(Number &n){
    if(n.lower < 0){
        n.upper *= -1;
        n.lower *= -1;
    }
    int upper = n.upper;
    int lower = n.lower;
    int fac = gcd(abs(upper), lower);
    n.upper /= fac;
    n.lower /= fac;
}

int Number::lcm(int a, int b){
    return a / gcd(a, b) * b;
}
Number::Number(std::string s){
    this->upper = 0;
    this->lower = 1;
    bool isDecimal = false;
    for(auto i : s){
        if(isdigit(i)){
            upper *= 10;
            upper += i - '0';
            if(isDecimal){
                lower *= 10;
            }
        }
    }
    if(s[0] == '-'){
        upper *= -1;
    }
}
Number::Number(int upper, int lower):upper(upper), lower(lower){}
Number Number::upside_down(){
    Number ret{this->lower, this->upper};
    check(ret);
    return ret;
}
Number Number::operator+(Number n){
    check(n);
    check(*this);
    int upper = this->upper * n.lower + n.upper * this->lower;
    int lower = this->lower * n.lower;
    Number ret = {upper, lower};
    check(ret);
    return ret;
}
Number Number::operator-(Number n){
    n.upper *= -1;
    return *this + n;
}
Number Number::operator*(Number n){
    check(n);
    check(*this);
    Number ret{upper * n.upper, lower * n.lower};
    check(ret);
    return ret;
}
Number Number::operator/(Number n){
    return *this * n.upside_down();
}

void Number::operator+=(Number n){
    *this = *this + n;
}
void Number::operator-=(Number n){
    *this = *this - n;
}
void Number::operator*=(Number n){
    *this = *this * n;
}
void Number::operator/=(Number n){
    *this = *this / n;
}

