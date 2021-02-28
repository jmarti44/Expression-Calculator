#include "myexp.h"
myExp :: myExp()
{

    type = ILLEGAL;
    valid = false;
    original = "empty";
}

myExp :: myExp (const string& s)
{
  
    set(s);
  
    
}

myExp :: ~myExp()
{

}

void myExp :: set(const string& s)
{
//converting string to a c-string (will be a const char * pointer                         
string str = s;                                                     //casting operator
char * c_string = ((char *)s.c_str());


//processing tokens and storing them

//intial varibles
const char delimeters [] = " ()+-*/=";                              //how string is tokenized
string delimeters_2 = " +-()*/=";                                   //extracting tokens that do not include spaces
string delimeterToken;                                              //storing delimeter tokens
int next = 0;                                                       //position of delimeter                                                               
string buffer;                                                      //buffer will be used to append tokens with more than one char
int counter = 0;                                                    //keeps track of tokenization position

char * tokenization =  strtok(c_string,delimeters);
if (str[0] == '=' || str[0] == '+' || str[0] =='-'|| str[0] =='=' || str[0] =='*' || str[0] ==')' || str[0] =='(')  //special case where the first token is a delimeter
{
    buffer.push_back(str[0]);
    tokenized.push_back(buffer);
    buffer.clear();
    counter++;
}
while (tokenization!=NULL)                                             
{
    //conditional where tokens are more than one char long
    if (strlen(tokenization) != 1)
    {
        for (int i = 0; tokenization[i]!= '\0'; i++)
        {
           buffer.push_back (tokenization[i]); 
        }
        tokenized.push_back(buffer);                                //inital tokens collected(operands and ID's)
        buffer.clear();

        next = str.find_first_of(delimeters_2,counter);
        if (next <= 0)                                              //werid case where the search reaches the end of the string- break
            break;
        delimeterToken = str.substr(next,1);                        //delimeter token is colleted(Operators and OB and CB)
        if (delimeterToken != " ")
            tokenized.push_back(delimeterToken);
        counter = next;
    //while loop is used collect all delimeter tokens
        while (delimeterToken == "=" || delimeterToken =="+" || delimeterToken =="-"|| delimeterToken =="/" || delimeterToken =="*" || delimeterToken ==")" || delimeterToken =="(" || " ")
        {
            counter ++;
            delimeterToken = str.substr(counter,1);
            if (delimeterToken != "=" && delimeterToken!="+" && delimeterToken !="-"&& delimeterToken !="/" && delimeterToken !="*" && delimeterToken !=")" && delimeterToken !="(" &&  delimeterToken != " ")
                break;
            if (delimeterToken!= " ")
                tokenized.push_back(delimeterToken);               
        }
           
    }
    //token is one char long
    else
    {
        buffer.push_back(*tokenization);                            
        tokenized.push_back(buffer);                                //char collected
        buffer.clear();
        next = str.find_first_of(delimeters_2,counter);
        if (next<0)
            break;
        delimeterToken = str.substr(next,1);                        //delimeter tokens collected in the same flow of logic
        if (delimeterToken != " ")                                  //line of code added to account for spaces
            tokenized.push_back(delimeterToken);
        counter = next;
        while (delimeterToken == "=" || delimeterToken =="+" || delimeterToken =="-"|| delimeterToken =="/" || delimeterToken =="*" || delimeterToken ==")" || delimeterToken =="(" || " ")
        {
            counter ++;
            delimeterToken = str.substr(counter,1);
            if (delimeterToken != "=" &&delimeterToken!="+" && delimeterToken !="-"&& delimeterToken !="/" && delimeterToken !="*" && delimeterToken !=")" && delimeterToken !="(" &&  delimeterToken != " ")
                break;
            if (delimeterToken!= " ")
                tokenized.push_back(delimeterToken);             
        }
    }
     tokenization = strtok(NULL,delimeters);                        //str tok called again to collect next token
    
}
    set_type();
    setPostfix();
    cout << type << endl;
    if (type == ARTHMETIC)
        setEvaluate();
}
void myExp :: setPostfix()  //error check for type: 1 + 2 * C
{
   
    stack<myToken> stk;
    for ( int i = 0; i<tokenized.size(); i++)
    {
        if (tokenized[i].get_type() == "INT" || tokenized[i].get_type() == "ID")
            postfix.push_back(tokenized[i]);
        else if ( tokenized[i].get_type() == "OP")
        {
            while (!stk.empty() && stk.top().get_priority() >= tokenized[i].get_priority() && stk.top().get_type() != "OpenBrace")
            {
                postfix.push_back(stk.top());
                stk.pop();
            }
            stk.push(tokenized[i]);
        }
         else if (tokenized[i].get_type() =="OpenBrace") //open brace condition
            stk.push(tokenized[i]);
         else if (tokenized[i].get_type() == "CloseBrace")
         {
              while (stk.top().get_type()!="OpenBrace" && !stk.empty())
              {
                  postfix.push_back(stk.top());
                  stk.pop();
              }
              stk.pop();
         }     
    }
    while (!stk.empty())
    {
        postfix.push_back(stk.top());
        stk.pop();
    }
}
void myExp :: setEvaluate()
{
    //variables for converting letters into numbers for evaluation
    string buffer [postfix.size()];                          //string buffer will be used to more easily convert to numbers
    float val_1 = 0;                                         //floats are used for decimal calcualtions
    float val_2 = 0;
    float x = 0;                                              //Will be used to convert string to numbers
    float y  = 0;                                            //will store final value
    string finalEval;                                        //Will store finalEval to evaluation token vector
    
    for (int i = 0; i<postfix.size();i++)
    {
        buffer[i]=postfix[i].get();
    }
    


    stack<float> stack;                                      //stack will be used to store operand and numbers

    
    for (int i = 0; i<postfix.size();i++)
    {
        if (postfix[i].get_type()== "INT")                  //pushing operands to the stack
            {
                stringstream integer(postfix[i].get());
                integer >> x;
                stack.push(x);

            }
        else if(postfix[i].get_type() == "OP")             //pusing operators to the stack
            { 
                val_1 = stack.top();                     
                stack.pop();
                val_2  = stack.top();
                stack.pop(); 
            
            //performing operations based on OP symbol
            if (postfix[i].get() == "+")
            {

                stack.push( val_2 + val_1);
            }
            else if (postfix[i].get() == "-")
            {
                stack.push(val_2-val_1);
            }
                
            else if (postfix[i].get() == "*")
                stack.push(val_2 * val_1);
            else if (postfix[i].get() == "/")
            {

                stack.push(float(val_2/val_1));
            }          

            }     
    }
    //final answer on top of the stack
   y = stack.top();

   stringstream ss;
   ss << y;
   string str = ss.str();;                              //final answer is coverted to a string;

   for (int i = 0; i<tokenized.size(); i++)             //appending original tokeniuzed expression
   {
       finalEval.append(tokenized[i].get());
   }
    //appending equal sign and postfix evaluation
   finalEval.append(" = ");             
   finalEval.append(str);
   evaluation.push_back(finalEval);
   
}
void myExp :: display() const
{
    int tokens = 0;
    cout << "original = " << original << endl;
    cout <<"tokenized = ";
    for (int i = 0; i< tokenized.size(); i++)
        cout << tokenized[i].get() <<";";
    cout << endl;


    for (int i = 0; i< tokenized.size(); i++)
        tokens ++;
    cout << "number of tokens = " << tokens << endl;

    cout << "postfix = ";
    cout << "size of postfix:" << postfix.size() << endl;
    for (int i = 0; i<postfix.size(); i++)
    {
        cout << postfix[i].get() << ";";
    }
    cout << endl;
    cout << "valid = " << "false" << endl;

}





string myExp :: get_original(const string&s)
{
    return s;
}


void myExp :: set_type()
{

bool valid = false;
//two initial conditions for determining expression type
    if ((tokenized[0].get_type() == "ID" || tokenized[0].get_type() == "INT)") && tokenized[1].get_type() == "EQ" && tokenized[2].get_type() == "INT")          
        {type = ASSIGNMENT;
            
        }
    
    else if (tokenized[0].get_type() == "INT" || tokenized[0].get_type() == "OpenBrace" || tokenized[0].get_type() == "ID")
    {
        for (int i = 1; i < tokenized.size(); i++)
        {
            if (tokenized[i].get_type() == "OP" || tokenized[i].get_type()=="INT" || tokenized[i].get_type()== "OpenBrace" || tokenized[i].get_type()=="CloseBrace")
                valid = true;
            else
            {
                valid = false;
                break;
            }
            
        }
    
        if (valid == true)
            type = ARTHMETIC;
        else
            type = ILLEGAL;
    }
    {
            
    }
    
        
}
string myExp :: get_type()
{
    string exptype;
    switch (type)
    {
    case ASSIGNMENT:
        exptype = "ASSIGNMENT";
        break;
    case ARTHMETIC:
        exptype = "ARTHIMETIC";
    default:
        exptype ="ILLEGAL";
        break;
    }

    return exptype;
}

vector<myToken> myExp :: get_tokenized() const
{
    return tokenized;

}
vector < myToken> myExp :: get_postfix() const
{
    return postfix;
}
vector <myToken> myExp :: get_evaluation() const
{
    return evaluation;
}


