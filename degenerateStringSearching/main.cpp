//
//  main.cpp
//  degenerateStringSearching
//
//  Created by Wenyao Zhu on 22/07/2022.
//

#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;
#include "degenerateString.hpp"

// Compute maximal suffix for <=
int maxSuf(char *x, int m, int *p) {
   int ms, j, k;
   char a, b;

   ms = -1;
   j = 0;
   k = *p = 1;
   while (j + k < m) {
      a = x[j + k];
      b = x[ms + k];
      if (a < b) {
         j += k;
         k = 1;
         *p = j - ms;
      }
      else
         if (a == b)
            if (k != *p)
               ++k;
            else {
               j += *p;
               k = 1;
            }
         else { /* a > b */
            ms = j;
            j = ms + 1;
            k = *p = 1;
         }
   }
   return(ms);
}

// Compute maximal suffix >=
int maxSufTilde(char *x, int m, int *p) {
   int ms, j, k;
   char a, b;

   ms = -1;
   j = 0;
   k = *p = 1;
   while (j + k < m) {
      a = x[j + k];
      b = x[ms + k];
      if (a > b) {
         j += k;
         k = 1;
         *p = j - ms;
      }
      else
         if (a == b)
            if (k != *p)
               ++k;
            else {
               j += *p;
               k = 1;
            }
         else { /* a < b */
            ms = j;
            j = ms + 1;
            k = *p = 1;
         }
   }
   return(ms);
}

// Compute prefixArray for degenerate
int* computePrefixDegenerate(degenerateString d_str) {
    int num=0, i_prev=0;
    int* prefixArray=new int [d_str.length];
    for (int i=0; i<d_str.length; i++) {
        degenerateString tmp_d_str=d_str.d_substr(i);
        i_prev=i;
        i=0;
        while (i<tmp_d_str.length && tmp_d_str.d_string[i].find_first_of(d_str.d_string[i])!=string::npos) {
            ++num;
            i++;
        }
        i=i_prev;
        prefixArray[i]=num;
        num=0;
    }
    return prefixArray;
}

// Compute period and local period array for degenerate
int* computePeriodDegenerate(degenerateString d_str) {
    int* borderArray=new int [d_str.length];
    int* periodArray=new int [d_str.length];
    periodArray[d_str.length - 1] = 1;
    int border = 0;
    
    for (int i=0; i<d_str.length; i++) {
        if (i == 0) {
            borderArray[i] = 0;
        } else {
            border = i;
            degenerateString tmp_x = d_str.d_substr(0, border - 1);
            degenerateString tmp_y = d_str.d_substr(i - border + 1, i);
            while (border > 0) {
                int num = 0;
                for (int j=0; j<border; j++) {
                    degenerateString tmp_x = d_str.d_substr(0, border - 1);
                    degenerateString tmp_y = d_str.d_substr(i - border + 1, i);
                    if (tmp_x.d_string[j].find(tmp_y.d_string[j]) != string::npos || tmp_y.d_string[j].find(tmp_x.d_string[j]) != string::npos) {
                        num ++;
                    }
                }
                if ( num == border ) {
                    borderArray[i] = num;
                    break;
                } else {
                    border --;
                }
            }
        }
    }
    for (int i=1; i<d_str.length; i++) {
        periodArray[i-1] = i + 1 - borderArray[i];
    }
    return periodArray;
}

// Mismatch happens on right
int computeShiftRight(degenerateString d_x, degenerateString d_t, bool degenerate_t, int k, int j, int position) {
    if (degenerate_t) {
        degenerateString next=d_x.d_substr(position+1, k-2)+d_t.d_substr(position+j+2, k+j-1);
        int* next_prefixArray=computePrefixDegenerate(next);
        int max=0;
        
        for (int idx=k-position-2; idx<2*(k-position-2); idx++) {
            if (max < next_prefixArray[idx] && next_prefixArray[idx]==2*(k-position-2)-idx) {
                max=next_prefixArray[idx];
            }
        }
        // cout << max << endl;
        if (max==0) {
            max=1;
        }
        j=j+max;
    } else {
        j=j+(k-position);
    }
    return j;
}

// Mismatch happens on left
int computeShiftLeft(degenerateString d_x, degenerateString d_t, int k, int j) {
    int shift=0, t_len=0, m=d_x.length;
    
    if (k==-1) {
        t_len=d_x.length-1;
    } else {
        t_len=d_x.length-k-1;
    }
    degenerateString next=d_t.d_substr(m+j-t_len, m+j-1).d_reverse()+d_x.d_substr(0, m-2).d_reverse();
    int* next_prefixArray=computePrefixDegenerate(next);
    int idx=t_len, rindex=t_len-1;
    
    while (idx<next.length) {
        if (next_prefixArray[idx]>next_prefixArray[rindex]) {
            rindex=idx;
        }
        idx++;
    }
    if (next_prefixArray[rindex]==0) {
        shift=t_len+1;
    } else {
        shift=m+rindex-next.length;
    }
    return shift;
}

// If contains degenerate symbol
bool isDegenerate(degenerateString d_str) {
    for (int i=0; i < d_str.length; i++) {
        if (d_str.d_string[i].length() > 1) {
            return true;
        }
    }
    return false;
}

// S-factorisation
void defactor(degenerateString &d_str) {
    bool *position= new bool [d_str.length];
    int num=0;
    
    for (int i=0; i<d_str.length; i++) {
        if (i==0) {
            position[i]=true;
        } else {
            string tmp_factor="";
            tmp_factor.append(d_str.d_string[i]);
            string cmp_object=d_str.ori_string.substr(0, i);
            int flag=0;
            
            while (cmp_object.find(tmp_factor)!=string::npos) {
                flag=1;
                i++;
                if (i >= d_str.length) {
                    break;
                }
                tmp_factor.append(d_str.d_string[i]);
            }
            if (flag) {
                i--;
                position[i]=true;
            } else {
                position[i]=true;
            }
        }
    }
    
    for (int i=0; i<d_str.length; i++) {
        if (position[i]) {
            num++;
        }
    }
    
    d_str.factor_num = num;
    d_str.factor_str = new string[num];

    for (int i=0, j=0; i<d_str.length; i++, j++) {
        string tmp_str="";
        if (position[i]){
            tmp_str.append(d_str.d_string[i]);
            d_str.factor_str[j]=tmp_str;
        } else {
            while (!position[i]) {
                tmp_str.append((d_str.d_string[i]));
                i++;
            }
            tmp_str.append((d_str.d_string[i]));
            d_str.factor_str[j]=tmp_str;
        }
    }
}

// Two-way string matching algorithm on degenerate strings (TW_de)
void TW_de(degenerateString x, degenerateString t) {
    int i_x, j_x, p, q, period = 0, position = 0, nextStart, k, j;
    int m=x.length;
    int n=t.length;
    int shift=1;
    bool degenerate_t=false;
    
    // Preprocessing
    if (isDegenerate(x)) {
        int *periodArray=computePeriodDegenerate(x);
        for (int i=0; i<m; i++) {
            if (period < periodArray[i]) {
                period = periodArray[i];
                position = i;
            }
        }
    } else {
        i_x = maxSuf((char *)x.ori_string.data(), m, &p);
        j_x = maxSufTilde((char *)x.ori_string.data(), m, &q);
        if (i_x > j_x) {
            position = i_x;
            period = p;
        }
        else {
            position = j_x;
            period = q;
        }
    }

    // Timer initialised
    clock_t start, end;
    start = clock();
    cout << "=============================================================" << endl;
    cout << "Searching run by TW_de, find the following positions in text:" << endl;
    
    // Searching
    if (memcmp((char *)x.ori_string.data(), (char *)x.ori_string.data() + period, position + 1) == 0) {
       j = 0;
       nextStart = -1;
       while (j <= n - m) {
           k = max(position, nextStart) + 1;
           while (k < m && t.d_string[k+j].find_first_of(x.d_string[k])!=string::npos) {
              if (x.degenerate[k] || t.degenerate[k+j]) {
                  degenerate_t=true;
              }
              ++k;
           }
           
           if (k>=m) {
               k=position;
               while (k > nextStart && t.d_string[k+j].find_first_of(x.d_string[k])!=string::npos) {
                   if (x.degenerate[k] || t.degenerate[k+j]) {
                       degenerate_t=true;
                   }
                   k--;
               }
               if (k <= nextStart) {
                   cout<<j<<endl;
               }
               if (degenerate_t) {
                   int c_shift=computeShiftLeft(x, t, k, j);
                   shift=max(c_shift, shift);
                   j=j+shift;
                   degenerate_t=false;
                   nextStart=-1;
               } else {
                   j += period;
                   nextStart = m - period - 1;
               }
           } else if (k-position < 3) {
               j += 1;
               degenerate_t=false;
               nextStart=-1;
           } else {
               j=computeShiftRight(x, t, degenerate_t, k, j, position);
               degenerate_t=false;
               nextStart=-1;
           }
       }
    }
    else {
        j=0;
        period=max(position+1, m-position-1)+1;
//        cout << period << endl;
        while (j <= n - m) {
            k=position+1;
            while (k < m && t.d_string[k+j].find_first_of(x.d_string[k])!=string::npos) {
                if (x.degenerate[k] || t.degenerate[k+j]) {
                    degenerate_t=true;
                }
                ++k;
            }
            if (k >= m) {
                k=position;
                while (k >= 0 && t.d_string[k+j].find_first_of(x.d_string[k])!=string::npos) {
                    if (x.degenerate[k] || t.degenerate[k+j]) {
                        degenerate_t=true;
                    }
                    k--;
                }
                if (k < 0) {
                    cout<<j<<endl;
                }
                if (degenerate_t) {
                    int c_shift=computeShiftLeft(x, t, k, j);
                    shift=max(c_shift, shift);
                    j=j+shift;
                    degenerate_t=false;
                } else {
                    j += period;
                }
            } else if (k-position < 3) {
                j += 1;
                degenerate_t=false;
                nextStart=-1;
            } else {
                j=computeShiftRight(x, t, degenerate_t, k, j, position);
                degenerate_t=false;
            }
        }
    }
    
    end = clock(); // Timer closed
    cout << "Execution time of TW_de: " << double(end - start)/CLOCKS_PER_SEC << endl; // Print out the time
    cout << "-----------------------------------------------------" << endl;
}

//========================================
// Random degenerate letter generation
string gen_random(const int len) {
    static const char alphabet[] = "abcd";
        // "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    
    return tmp_s;
}

// Generate according to assignments (length: the string length; num_dl: the number of degenerate letters)
degenerateString gen_ds_random(const int length, const int num_dl) {
    degenerateString tmp_ds;
    tmp_ds.length=length;
    tmp_ds.d_string=new string[length];
    tmp_ds.degenerate=new bool[length];
    int i=0;
    
    while (i < num_dl) {
        srand((unsigned)time(NULL) * getpid());
        int rand_pos=(rand() % (length));
        if (tmp_ds.d_string[rand_pos].length()==0) {

// ============== alphabet size is 2 ================
//            tmp_ds.d_string[rand_pos]="ab";
//===================================================
            
// ================== alphabet size is 3 ===================
//           int rand_num = (rand() % (4))+ 1;
//           switch (rand_num) {
//               case 1:
//                   tmp_ds.d_string[rand_pos]="ab";
//                   break;
//
//               case 2:
//                   tmp_ds.d_string[rand_pos]="ac";
//                   break;
//
//               case 3:
//                   tmp_ds.d_string[rand_pos]="bc";
//                   break;
//
//               case 4:
//                   tmp_ds.d_string[rand_pos]="abc";
//                   break;
//
//               default:
//                   break;
//           }
// =========================================================
            
// ================== alphabet size is 4 ===================
            int rand_num = (rand() % (11))+ 1;
            switch (rand_num) {
                case 1:
                    tmp_ds.d_string[rand_pos]="ab";
                    break;

                case 2:
                    tmp_ds.d_string[rand_pos]="ac";
                    break;

                case 3:
                    tmp_ds.d_string[rand_pos]="ad";
                    break;

                case 4:
                    tmp_ds.d_string[rand_pos]="bc";
                    break;

                case 5:
                    tmp_ds.d_string[rand_pos]="bd";
                    break;

                case 6:
                    tmp_ds.d_string[rand_pos]="cd";
                    break;

                case 7:
                    tmp_ds.d_string[rand_pos]="abc";
                    break;

                case 8:
                    tmp_ds.d_string[rand_pos]="abd";
                    break;

                case 9:
                    tmp_ds.d_string[rand_pos]="acd";
                    break;

                case 10:
                    tmp_ds.d_string[rand_pos]="bcd";
                    break;

                case 11:
                    tmp_ds.d_string[rand_pos]="abcd";
                    break;

                default:
                    break;
                    
// ========================================================
            }
            tmp_ds.degenerate[rand_pos]=true;
            cout << "degenerate generated success!" << endl;
            i++;
        }
    }
    
    for (int j=0; j<length; j++) {
        if (tmp_ds.d_string[j].length()==0) {
            tmp_ds.d_string[j]=gen_random(1);
            tmp_ds.degenerate[j]=false;
        }
    }
    return tmp_ds;
}

// ================= end part of random generation===========

// Brute Force
double BF(degenerateString x, degenerateString t) {
    int i, j;
    
    clock_t start, end;
    start=clock();
    cout << "=============================================================" << endl;
    cout << "Searching run by BF, find the following positions in text:" << endl;
    // Searching
    for (j = 0; j <= t.length - x.length; ++j) {
        for (i = 0; i < x.length && t.d_string[i+j].find_first_of(x.d_string[i])!=string::npos; ++i);
        if (i >= x.length)
            cout << j << endl;
        
    }
    end=clock();
    cout <<  double(end - start)/CLOCKS_PER_SEC << endl;
    return double(end - start)/CLOCKS_PER_SEC;
}

// Main
int main(int argc, const char * argv[]) {
    
    // Data generation
    srand((unsigned)time(NULL) * getpid());  // Seed initialised
    
    // Text preparation
    degenerateString rand_ds_t=gen_ds_random(100, 6);
    
    // Pattern preparation
    degenerateString rand_ds_x;
    // Random generation (pattern)
    rand_ds_x=gen_ds_random(5, 1);

    // Special cases
    // 1. regular
//    rand_ds_x.setDegenerateString("aab"); // 3
//    rand_ds_x.setDegenerateString("aaabc");   // 5
//    rand_ds_x.setDegenerateString("cabca");   // 5
//    rand_ds_x.setDegenerateString("cabcd");   // 5
//    rand_ds_x.setDegenerateString("abcadb");  // 6
//    rand_ds_x.setDegenerateString("aacabda"); // 7
//    rand_ds_x.setDegenerateString("bcdbcdba"); // 8
//    rand_ds_x.setDegenerateString("bababacd"); // 8
//    rand_ds_x.setDegenerateString("badbadbac"); // 9
//    rand_ds_x.setDegenerateString("bcdcbadbac"); // 10
//    rand_ds_x.setDegenerateString("dbcccbbdba"); // 10
//    rand_ds_x.setDegenerateString("bcdbcdbcda"); // 10
//    rand_ds_x.setDegenerateString("bcdbcdbcdba"); // 11
//    rand_ds_x.setDegenerateString("ababcabcabbd"); // 12
    
    // 2. degenerate (by using "[" and "]" to express a degenerate symbol) e.g.,
//    rand_ds_x.setDegenerateString("[ab]baba");
//    rand_ds_x.setDegenerateString("[ab]abab");
    
    // Essential initialisation for degenerate strings
    rand_ds_x.setori_string();
    
    // S-factorisation
    cout << "s-factorisation: " << endl;
    defactor(rand_ds_x);
    rand_ds_x.getFactor();
    cout << "******************" << endl;
    
    // Experiments
    double time = BF(rand_ds_x, rand_ds_t);
    TW_de(rand_ds_x, rand_ds_t);
    
    cout << endl;
    cout << "Execution time of BF: " << time << endl;

    return 0;
}
