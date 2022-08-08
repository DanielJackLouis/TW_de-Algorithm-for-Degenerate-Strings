//
//  degenerateString.hpp
//  degenerateStringSearching
//
//  Created by Wenyao Zhu on 22/07/2022.
//

#ifndef degenerateString_hpp
#define degenerateString_hpp

#include <iostream>
using namespace std;

class degenerateString {
public:
    string *d_string;           // degenerate string pointer
    int length;                 // Keep the degenerate length
    bool *degenerate;           // degenerate tag
    string ori_string;          // original string
    string *factor_str;         // factorisation
    int factor_num;             // number of factors
    
    
public:
    void setDegenerate(void);                                  // initial all tags
    void setDegenerateString(string inputString);              // assign string to degenerate string
    void get(void);                                            // print
    void setori_string(void);                                  // set original string include mapping
    void getFactor(void);                                      // get Factors
    degenerateString d_substr(int idx);                        // substring suffix
    degenerateString d_substr(int startIdx, int endIdx);       // substring from startIdx to endIdx
    degenerateString d_reverse(void);                          // reverse the string
    
    
    // operation + for degenerate strings
    degenerateString operator+(const degenerateString &d_str)
    {
        degenerateString new_d_str;
        new_d_str.length=this->length + d_str.length;
        new_d_str.d_string=new string[new_d_str.length];
        new_d_str.degenerate=new bool[new_d_str.length];
        
        for (int i=0; i<this->length; i++) {
            new_d_str.d_string[i]=this->d_string[i];
            new_d_str.degenerate[i]=this->degenerate[i];
        }
        for (int i=this->length, j=0; j<d_str.length; i++, j++) {
            new_d_str.d_string[i]=d_str.d_string[j];
            new_d_str.degenerate[i]=this->degenerate[j];
        }
        return new_d_str;
    }
    
};

#endif /* degenerateString_hpp */
