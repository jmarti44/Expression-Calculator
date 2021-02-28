#ifndef MYEXP_H
#define MYEXP_H


#include "mytoken.h"
#include <sstream>
#include <stack>
#include <queue>

class myExp
{
    enum exp_type { ASSIGNMENT, ARTHMETIC, ILLEGAL};


    bool valid; //not used
    exp_type type; //not used




public:
    string original;
    vector <myToken > tokenized;
    vector <myToken> postfix;
    vector <myToken> evaluation;






    //constructors
    myExp();
    myExp( const string& s);
    myExp(const myExp &orig);
    ~myExp();

    //functions
    void set(const string& s);
    void display() const;
    void setPostfix();
    void setEvaluate();
    string get_original (const string&s);
    vector <myToken> get_tokenized() const;
    vector <myToken> get_postfix() const;
    vector <myToken> get_evaluation() const;



    //Check point 3
   
    void set_type();
    string get_type();


    //operator overloading

};

#endif