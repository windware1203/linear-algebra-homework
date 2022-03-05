
#include "../include/formula.h"
Formula Formula::operator+(const Formula &f){
    if(this->vars.size() != f.vars.size()){
        return {{}, 0};
    }
    std::vector<Number> v;
    for(int i = 0 ; i < (int)vars.size() ; i++){
        v.push_back(this->vars[i] + f.vars[i]);
    }
    return {v, this->left + f.left};
}
Formula Formula::operator-(const Formula &f){
    if(this->vars.size() != f.vars.size()){
        return {{}, 0};
    }
    std::vector<Number> v;
    for(int i = 0 ; i < (int)vars.size() ; i++){
        v.push_back(this->vars[i] - f.vars[i]);
    }
    return {v, this->left - f.left};
}
Formula Formula::operator*(const int i){
    return (*this) * Number{i};
}
Formula Formula::operator/(const int i){
    return (*this) / Number{i};
};

Formula Formula::operator*(const Number i){
    std::vector<Number> v = this->vars;
    for(Number &n : v){
        n *= i;
    }

    return {v, this->left * i};
}
 
Formula Formula::operator/(const Number i){
    std::vector<Number> v = this->vars;
    for(Number &n : v){
        n /= i;
    }
    return {v, this->left / i};
};

std::string  Formula::to_string(){
    std::string ret = "";
    for(int i = 0 ; i < (int)vars.size() ; i++){
        if(i != 0 && vars[i].upper < 0){
            ret += "+";
        }
        ret += " " + vars[i].to_string();
    }
    ret += " =" + left.to_string();
    return ret;
}