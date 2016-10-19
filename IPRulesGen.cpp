#include <iostream>
#include "IPRulesGen.h"
using namespace std;

int main()

{
    int main_choice;
    cout<<"Welcome to IPRulesGen 1.0! This is a tool for quick IPTables rules generation."<<endl;
    cout<<"Below are several options for generation of rules. Please enter 1-5 for your choice."<<endl<<endl;
    cout<<"1) Display rules"<<endl;
    cout<<"2) Drop traffic from unwanted IP addresses"<<endl;
    cout<<"3) Insert rules"<<endl;
    cout<<"4) Delete firewall rules"<<endl;
    cout<<"5) Choose from standard rules"<<endl;
    cin>>main_choice;

    if(main_choice == 1)
    {
        displayRules();
    }

    else if (main_choice == 2)
    {
        dropTraffic();
    }

    else if (main_choice == 3)
    {
        insertRules();
    }

    else if(main_choice == 4)
    {
        deleteRules();
    }

    else if(main_choice == 5)
    {
        standardRules();
    }

    else
    {
        cout<<"Sorry, that was not a valid option. Please try again."<<endl;
    }


    return 0;
}
