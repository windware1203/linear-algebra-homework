#include <iostream>
#include <vector>

#include "../include/formula.h"

using namespace std;

std::ostream& operator<<(std::ostream &o, Number n){
    if(n.lower == 1){
        return o << n.upper;
    }
    return o << n.upper << '/' << n.lower;
}

void swap(Formula &f1, Formula &f2){
    Formula temp = f1;
    f1 = f2;
    f2 = temp;
}

void print_marix(vector<Formula> &v){
    for(auto f : v){
        for(auto n : f.vars){
            cout << n << " ";
        }
        cout << f.left << endl;
    }
    cout << endl;
}

void sort_row(vector<Formula> &v, int start, int end, int col){
    if(col >= (int)v[0].vars.size()){
        return;
    }
    cout << "sorting" << endl;
    for(int i = end - 1 ; i > 0 ; i--){
        for(int j = 0 ; j < i ; j++){
            if(v[j].vars[col].upper == 0 && v[j].vars[col].upper != 0){
                cout << "swap (row " << j + 1 << ") and (row " << j + 2 << ")" << endl;
                swap(v[j], v[j+1]);
            }
        }
    }
    cout << "sort finish" << endl << endl;
}

void toRef(vector<Formula> &v){
    cout << "origin: " << endl;
    print_marix(v);

    int begin = 0;
    for(int i = 0 ; i < (int)v[0].vars.size() ; i++){
        sort_row(v, begin, v.size(), i);
        while(i < (int)v[0].vars.size() && begin < (int)v.size() && v[begin].vars[i].upper == 0){
            i++;
            sort_row(v, begin, v.size(), i);
        }
        if(i >= (int)v[0].vars.size()){
            break;
        }
        for(int j = begin + 1 ; j < (int)v.size() && v[j].vars[i].upper != 0 ; j++){
            Number temp = v[j].vars[i] / v[begin].vars[i];
            
            cout << "(row " << j + 1 << ") - (row " << begin + 1 << ") * " << temp << endl;
            
            v[j] = v[j] - v[begin] * temp.upper / temp.lower;
            print_marix(v);
        }

        begin++;
    }

    for(int i = 0 ; i < (int)v.size() ; i++){
        for(Number j : v[i].vars){
            if(j.upper != 0){
                cout << "(row " << i << ") / " << j << endl;
                v[i] = v[i] / j;
                break;
            }
        }
    }
    cout << "ref: " << endl;
    print_marix(v);

}

void toRref(vector<Formula> &v){
    toRef(v);
    for(int i = (int)v.size() - 1 ; i > 0 ; i--){
        for(int j = 0 ; j < i ; j++){
            int temp;
            for(temp = 0 ; temp < (int)v[i].vars.size() && v[i].vars[temp].upper == 0 ; temp++){
            };
            if(temp == (int)v[i].vars.size()){
                continue;
            }
            cout << "(row " << j + 1 << ") - (row " << i + 1 << ") * " << v[j].vars[temp] * v[i].vars[temp] << endl;
            v[j] = v[j] - v[i] / v[i].vars[temp] * v[j].vars[temp];
            print_marix(v);
        }
    }

    cout << "rref: " << endl;
    print_marix(v);
}

void solveRrefAndPrint(vector<Formula> &v){
    int length = (int)v[0].vars.size();
    int map[length] = {0};
    int count = 0;
    for(int i = 0 ; i < (int)v.size() ; i++){
        while(v[i].vars[i + count].upper != 1){
            map[i + count] = count+1;
            count++;
        }
        if(i == (int)v.size() - 1){
            i++;
            while(i + count < length){
                map[i + count] = count+1;
                count++;
            }
        }
    }
    
    cout <<"map: ";
    for(int a : map){
        cout << a << " ";
    }
    cout <<endl;

    count = 0;
    for(int i = 0 ; i < length ; i++){
        if(map[i] != 0){
            cout << "a" << i << " = s" << map[i]-1 << endl;
            continue;
        }
        cout << "a" << i << " = " << v[count].left;
        for(int j = i + 1 ; j < length ; j++){
            if(v[count].vars[j].upper != 0){
                Number n = v[count].vars[j];
                if(n.upper < 0){
                    cout << " + " << n.upper * -1;
                }
                else{
                    cout << " - " << n.upper;
                }
                if(n.lower != 1){
                    cout << "/" << n.lower;
                }
                cout << "s" << map[j] - 1;
            }
        }
        cout << endl;
        count++;
    }
}

int main(int argc, char const *argv[])
{
    vector<Formula> v;                   // ans:  1, 2, 3
    int row;
    int col;
    cout << "Please enter row   : ";
    cin >> row;
    cout << "Please enter column: ";
    cin >> col;
    cout << "Please enter matrix: \n";
    for(int i = 0 ; i < row ; i++){
        vector<Number> temp;
        int left;
        for(int j = 0 ; j < col ; j++){
            int temp2;
            cin >> temp2;
            temp.push_back({temp2});
        }
        cin >> left;
        v.push_back({temp, left});
    }
    toRref(v);
    solveRrefAndPrint(v);

    return 0;
}