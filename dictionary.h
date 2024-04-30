/*
* This file contains the dictionary array which is 
* an array of Word structs that hold words that could be
* potential secret words. You may add or remove from the Word
* struct as you see fit for your own implementation.
* You should add more potential secret words to the dictionary.
*/

struct Word {
   char* letters;
   int counts[5];
   char unique[5];
} word;  


Word dictionary[10] = {
    {"spade", {1,1,1,1,1}, {'s','p', 'a', 'd', 'e'}},
    {"crane", {1,1,1,1,1}, {'c', 'r', 'a', 'n', 'e'}},
    {"laugh", {1,1,2,1,0}, {'l','a','u','g','h'}},
    {"heart", {1,1,1,1,1}, {'h','e','a','r','t'}},
    {"house", {1,1,2,1,0}, {'h','o','u','s','e'}},
    {"mayor", {1,1,1,1,1}, {'m','a','y','o','r'}},
    {"model", {1,1,2,1,0}, {'m','o','d','e','l'}},
    {"paint", {1,1,1,1,1}, {'p','a','i','n','t'}},
    {"urban", {1,1,2,1,0}, {'u','r','b','a','n'}},
    {"above", {1,1,1,1,1}, {'a','b','o','v','e'}}
    };

