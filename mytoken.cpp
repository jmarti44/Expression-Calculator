#include "mytoken.h"


myToken :: myToken()
{
    
    tokenType = INVALID;

    priority = -1;




}
myToken :: myToken (string s)
{
    
    token_piece = s;
    tokenType = INVALID;
    set(s);
    //priority = -1;
}

myToken :: myToken(const myToken &org)
{
    token_piece = org.token_piece;
    tokenType = org.tokenType;
    priority = org.priority;

}
myToken :: ~myToken ()
{

}

void myToken :: set (string s)
{


    token_piece = s;
    priority = -1;


    //checking if first is "a-z" or "A-Z" or "_"-condition for identifier

    if (s[0]== '_' || (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
    {
        if (s.size() == 1 && isalpha(s[0]))
        {
            tokenType = ID;
        }
            
        else
            {
             for (int i = 1; i<s.size(); i++)
            {

             if( s[i]== '_' || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
                (s[i] >= '0' && s[i] <= '9'))
                {

                    tokenType = ID;
                    break;
                }
             }
            }
       
    }


    //checking for ID
    else if ((s.size() == 1) && isalpha(s[0]))
    {

        tokenType = ID;
    }
    //checking for op type
    else if ((s.size() == 1) && ((s == "+" )|| (s== "-" )|| (s== "*" )|| (s== "/")))
    {
       
        tokenType = OP;
        if ( s == "+" || s== "-")
            priority = 1;
        else if (s == "*" || s =="/")
            priority = 2;
       


    }
    else if (s.size() == 1 && s == "=")
    {
        tokenType = EQ;
        cout << "correct = token type" << endl;
    }
    //checking for single 0
    else if (s[0] == '0')
    {
        tokenType = INT;
    
    }


    else if (s[0] >'0' && s[0] <= '9')
    {

        if (s.size() == 1)
        {
            tokenType = INT;
           
        }

        
        for (int i = 1; i<s.size(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {

                tokenType = INT;
                
                break;
            }
            else
            {
                tokenType = INVALID;
                break;
            }

        }

    }
    else if ((s.size() == 1) && (s == "("))
    {

        tokenType = OpenBrace;
        priority = 0;
    }
    else if ((s.size() == 1) && (s == ")"))
    {

        tokenType = CloseBrace;
    }
}
int myToken :: value () const
{
    switch (tokenType)
    {
        case INT:
            return 1;
        case ID:
            return -1;
        default :
            return -2;
        
    }
}
void myToken :: display () const
{
    
    cout << "type = " << get_type() << endl;
    cout << "token = " << token_piece << " (value is " << value() << ")" << endl;
    cout << "priority = " << priority << endl;
}

string myToken ::  get_type() const
{
    string type;
    switch (tokenType)
    {

        case ID:
            type = "ID";
            break;
        case INT:
            type = "INT";
            break;
        case OP:
            type = "OP";
            break;
        case EQ:
            type = "EQ";
            break;
        case OpenBrace:
            type = "OpenBrace";
            break;
        case CloseBrace:
             type = "CloseBrace";
            break;
           
        default:
            type = "INVALID";
    }
    return type;
}
int myToken :: get_priority () const
{
    return priority;
}

string myToken :: get() const
{

    return token_piece;
}

