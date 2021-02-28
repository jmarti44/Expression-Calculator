
#include "myexp.h"


int main()
{
	string expression;
    string test;
    string newExpression;
	string choice;
	myExp exp;
    std::cout << "-----Expression Evaulation Program------" << endl;

    
    std::cout << endl;

    std::cout << "expression input: ";
    getline(cin, expression);
    exp.set(expression);

	std::cout << "Action list:" << endl;
    std::cout << "Evaulation (=)" << endl;
    std::cout << "Postfix expression conversion (<)" << endl;
    std::cout << "Quit the program(q)" << endl;


	while (choice != "q")                                                           
        {
            std::cout << "Choose desired action: ";
            cin >> choice;
            
        
            while (choice != "=" && choice != ">" && choice != "<" && choice != "f"&& choice !="q" && choice != "s")
            {
                std::cout << "Not a valid action input. Please try again: ";
                cin >> choice;
            }
            if (choice == "q")
                break;
            if (choice == "=")
            {
               
                    for (int i = 0; i<exp.evaluation.size(); i++)
                    {   
                       std::cout << exp.evaluation[i].get();
                    }
                    std::cout << endl;   
                
            }      
                
            if (choice == "<")
            {
               
            
                
                  std::cout << "postfix of " << newExpression << " " << "is" << " " ;
                    for ( int i = 0; i< exp.postfix.size(); i++)
                    {
                        std::cout << exp.postfix[i].get() << " ";

                    }
                     std::cout << endl;
				        
            }
                

            if (choice == "s")
                {
                    std::cout  << "expression input: ";
                    cin>> expression;
                    exp = expression;
                }
        }
        std::cout  << endl;
        std::cout << "Program has ended" << endl;

}
