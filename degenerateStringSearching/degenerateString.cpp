//
//  degenerateString.cpp
//  degenerateStringSearching
//
//  Created by Wenyao Zhu on 22/07/2022.
//

#include "degenerateString.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void degenerateString::setDegenerateString(string inputString){
//    ori_string=inputString;
    d_string=new string[inputString.length()];
    degenerate=new bool[inputString.length()];
    bool flag=false;
    int j=0;
    for (int i=0; i<inputString.length(); i++, j++) {
        if (inputString[i]=='[') {
            flag=true;
            degenerate[j]=true;
            while (flag) {
                if (inputString[i+1]!=']') {
                    d_string[j]=d_string[j]+inputString[i+1];
                    i++;
                } else {
                    flag=false;
                }
            }
            i++;
        } else {
            d_string[j]=inputString[i];
            degenerate[j]=false;
        }
    }
    length=j;
}

void degenerateString::get(void) {
    for (int i=0; i<length; i++) {
        cout << d_string[i];
    }
}

degenerateString degenerateString::d_substr(int idx) {
    int j=0;
    degenerateString d_str;
    d_str.d_string = new string[length];
    for (int i=idx; i<length; i++, j++) {
        d_str.d_string[j]=d_string[i];
    }
    d_str.length=j;
    return d_str;
}

degenerateString degenerateString::d_substr(int startIdx, int endIdx) {
    int j=0;
    degenerateString d_str;
    d_str.length=endIdx-startIdx+1;
    d_str.d_string = new string[d_str.length];
    d_str.degenerate = new bool[d_str.length];
    if (endIdx>length) {
        for (int i=startIdx; i<length; i++, j++) {
            d_str.d_string[j]=d_string[i];
        }
        d_str.length=j;
    } else {
        for (int i=startIdx; i<endIdx+1; i++, j++) {
            d_str.d_string[j]=d_string[i];
        }
        d_str.length=j;
    }
    return d_str;
}

degenerateString degenerateString::d_reverse(void) {
    degenerateString r_d_str;
    r_d_str.length=length;
    r_d_str.d_string=new string[r_d_str.length];
    
    for (int i=0, j=length-1; i<r_d_str.length && j>=0; i++, j--) {
        r_d_str.d_string[i]=d_string[j];
    }
    return r_d_str;
}

void degenerateString::setori_string(void) {
    if (length!=0 && ori_string == "") {
        for (int i=0; i<length; i++) {
            if (d_string[i].length()==1) {
                ori_string += d_string[i];
            } else {
                if (d_string[i]=="ab") {
                    ori_string += "A";
                } else if (d_string[i]=="ac") {
                    ori_string += "B";
                } else if (d_string[i]=="ad") {
                    ori_string += "C";
                } else if (d_string[i]=="bc") {
                    ori_string += "D";
                } else if (d_string[i]=="bd") {
                    ori_string += "E";
                } else if (d_string[i]=="cd") {
                    ori_string += "F";
                } else if (d_string[i]=="abc") {
                    ori_string += "G";
                } else if (d_string[i]=="abd") {
                    ori_string += "H";
                } else if (d_string[i]=="acd") {
                    ori_string += "I";
                } else if (d_string[i]=="bcd") {
                    ori_string += "J";
                } else if (d_string[i]=="abcd") {
                    ori_string += "K";
                } else if (d_string[i]=="[ab]") {
                    ori_string += "A";
                } else if (d_string[i]=="[ac]") {
                    ori_string += "B";
                } else if (d_string[i]=="[ad]") {
                    ori_string += "C";
                } else if (d_string[i]=="[bc]") {
                    ori_string += "D";
                } else if (d_string[i]=="[bd]") {
                    ori_string += "E";
                } else if (d_string[i]=="[cd]") {
                    ori_string += "F";
                } else if (d_string[i]=="[abc]") {
                    ori_string += "G";
                } else if (d_string[i]=="[abd]") {
                    ori_string += "H";
                } else if (d_string[i]=="[acd]") {
                    ori_string += "I";
                } else if (d_string[i]=="[bcd]") {
                    ori_string += "J";
                } else if (d_string[i]=="[abcd]") {
                    ori_string += "K";
                }
            }
        }
    }
}

void degenerateString::setDegenerate(void) {
    for (int i=0; i<length; i++) {
        if (d_string[i].length()!=1) {
            degenerate[i]=true;
        } else {
            degenerate[i]=false;
        }
    }
}

void degenerateString::getFactor(void) {
    for (int i=0; i<factor_num; i++) {
        cout << factor_str[i] << endl;
    }
}
