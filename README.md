# Two-way Algorithm on Degenerate Strings
Two-way algorithm is an searching algorithm that finds out occurrences of both regular and degenerate patterns in an regular or degenerate text. 

> A degenerate string of length $n$ which is defined by the existence of one or more positions that can be represented as a sequence of $x=x[1]x[2]\dots x[n]$ where $\Sigma$ is an given alphabet and $\forall i\in [1\dots i],\ x[i]\subset \Sigma$. For instance, $\lbrace a,b\rbrace ab\lbrace a,b\rbrace$ is a degenerate string of length 4 over $\Sigma=\lbrace a,b\rbrace$.

Algorithms in this project is based on the terminology described in the final project by Wenyao Zhu, supervised by *Costas S. Iliopoulos*. 

The project is developed by C++.

## Data Structures
A class called `degenerateString` is created to have a series of attributes. This class is used to define all regular or degenerate strings in this project (file `degenerateString.h`). A string array declared as a string pointer (`*d_string`) is used to store all letters of the input strings. Other attributes such as `length` and `*degenerate` are defined to make code tidy and easy to follow, having the potential to be further developed.

## Main Function
Several functions having close connections with the fundamental operations of degenerate strings have been defined and implemented within the class `degenerateString`(file `degenerateString.h` and `degenerateString.cpp`). Other methods that are widely used in the searching algorithm are created explicitly above the final `main()` function (file `main.cpp`). Brief comments have been added to the code which should be easy to understand.

## Usage
The algorithms execute on randomly generated data in real-time. The modified generating method can generate those strings as random as possible. The implementation can refer to function `gen_random` and `gen_ds_random`.

+ Set the alphabet. Elements of the alphabet can be listed directly in function `gen_random`, and degenerate symbols can be specified in `gen_ds_random`. There is a sample showing how to organise the degenerate symbols by considering all the non-empty subsets of an alphabet. The length of generation time depends on the number of degenerate letters it generates.

+ Define the pattern and text. 

  + Through generation. For example, the code to generate a random degenerate text of length 1000 which has 60 degenerate symbols is written as `degenerateString rand_ds_t=gen_ds_random(1000, 60)`.
  + Through assignment. For instance, the following code assign a degenerate string $\lbrace a,b\rbrace baba$ to the variable `rand_ds_x`: 
```c++
		// Pattern preparation
    degenerateString rand_ds_x;
    // Degenerate (by using "[" and "]" to express a degenerate symbol) e.g.,
    rand_ds_x.setDegenerateString("[ab]baba");
    // Essential initialisation for degenerate strings
    // Only applied when assignment
    rand_ds_x.setori_string();
```

+ Run the program.

## Output
The output of this algorithm should be similar to the results in the screenshot below.

![Execution Results](https://i0.wp.com/tva1.sinaimg.cn/large/e6c9d24egy1h4zn9mm3cqj21c00u0te2.jpg)



In the screenshot, the degenerate pattern is `{a,b}abab` of length 5, and the text of length $100$ contains $6$ degenerate symbols. The same result from both TW_de and BF algorithms proves that all occurrences of the pattern can be found in the text by TW_de. The execution time of TW_de is $5.5\times 10^{-5}$ (sec), and the time of BF is $8.4\times10^{-5}$ (sec), meaning TW_de tends to be more efficient in the current example. 




