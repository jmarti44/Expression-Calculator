#ifndef MYTOKEN_H
#define MYTOKEN_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class myToken
{
 
    enum type {ID, INT, OP, EQ, OpenBrace, CloseBrace, INVALID};

private:


public:
    //constructors
    myToken ();  //default constructor
    myToken(const myToken &org);  //copy constructor
    myToken(string s);
    ~myToken(); //destructor

    //Method functions
    string get() const;
    void set(string s);
    int value ()const;
    void display()const;
    string get_type() const;
    int get_priority() const;

    type tokenType;
    int priority;
    string token_piece;





};

#endif