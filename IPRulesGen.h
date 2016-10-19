#ifndef IPRULESGEN_H
#define IPRULESGEN_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;
string checkRangeStart()
{
    string blocked_range_start;

    cout<<"Please enter the start of the IP range you would like to block now in the format of 10.10.10.0: "<<flush;
    while(!(cin>>blocked_range_start))
    {
        cin.clear();
        cerr<<"Input not recognized. Please try again."<<endl;
    }

    return blocked_range_start;
}

string checkRangeEnd()
{
    string blocked_range_end;

    cout<<"Please enter the end of the IP range you would like to block in the format of 10.10.10.10: "<<flush;

    while(!(cin>>blocked_range_end))
    {
        cin.clear();
        cerr<<"Input not recognized. Please try again."<<endl;
    }

    return blocked_range_end;
}

string checkIP()
{
    string blocked_IP;

    cout<<"The IP address you would like blocked needs to be in a format like these examples: 10.10.10.10 or 192.168.0.1"<<endl<<"Enter the IP you would like blocked: "<<flush;
    while(!(cin>>blocked_IP))
    {
        cin.clear();
        cerr<<"Input not recognized. Please try again."<<endl;
    }

    return blocked_IP;
}

string checkDirection()
{

    string direction_traffic;
    cout<<"Is this for incoming or outgoing traffic? Type i or o: "<<flush;
    while(!(cin>>direction_traffic))
    {
        cin.clear();
        cerr<<"Input not recognized. Please try again."<<endl;
    }
    return direction_traffic;
}

void dropTraffic()
{
    int range_option;
    string blocked_IP;
    string blocked_range_start;
    string blocked_range_end;
    string correct_input;
    string direction_traffic;

    cout<<"1) Range of IP addresses"<<endl<<"2) Individual IP addresses"<<endl;
    cout<<"Select 1 or 2: "<<endl;
    cin>>range_option;

    if (range_option == 1)
    {   //get the IP range
        correct_input="no";
        do {

            blocked_range_start = checkRangeStart();
            blocked_range_end = checkRangeEnd();
            cout<<"You have entered that you would like to block IP addresses: "<<blocked_range_start<<"-"<<blocked_range_end<<endl<<"Is this correct? Type y or n: ";
            cin>>correct_input;
            if(cin.fail())
            {
                cerr<<"Input not recognized. Please try again."<<endl;
                cin.clear();
            }
        }
        while (!cin.fail() && (correct_input == "n" || correct_input == "no" || correct_input == "NO" || correct_input == "No"));


        if(correct_input == "y" || correct_input == "yes" || correct_input == "YES" || correct_input == "Yes")
        {
            direction_traffic = checkDirection();
            if (direction_traffic == "i" || direction_traffic == "incoming" || direction_traffic =="INCOMING" || direction_traffic == "Incoming")
            {
                cout<<"iptables -A INPUT -s "<<blocked_range_start<<"-"<<blocked_range_end<<" -j DROP"<<endl;
            }
            else if(direction_traffic == "o" || direction_traffic == "outgoing" || direction_traffic == "OUTGOING" || direction_traffic == "Outgoing")
            {
                cout<<"iptables -A OUTPUT -s "<<blocked_range_start<<" - "<<blocked_range_end<<" -j DROP"<<endl;
            }
            else
            {
                cerr<<"Please enter either incoming or outgoing for the direction of traffic."<<endl;
            }
        }
        else
        {
            cerr<<"Input not recognized. Please try again."<<endl;
        }
    }

    else if (range_option == 2)
    {
        correct_input="no";
        do {
            blocked_IP = checkIP();
            cout<<"You have entered "<<blocked_IP<<endl<<"Is this correct? Type y or n: "<<flush;
            cin>>correct_input;
        }
        while(!cin.fail() && (correct_input == "n" || correct_input == "no" || correct_input== "NO" || correct_input == "No"));

        if(correct_input == "y" || correct_input == "yes" || correct_input == "YES" || correct_input == "Yes")
        {
            direction_traffic = checkDirection();
            if (direction_traffic == "i" || direction_traffic == "incoming" || direction_traffic == "INCOMING" || direction_traffic == "Incoming")
            {
                cout<<"iptables -A INPUT -s "<<blocked_IP<<" -j DROP"<<endl;
            }
            else if (direction_traffic == "o" || direction_traffic == "outgoing" || direction_traffic == "OUTGOING" || direction_traffic == "Outgoing")
            {
                cout<<"iptables -A OUTPUT -s "<<blocked_IP<<" -j DROP"<<endl;
            }
            else // something other than o or i was supplied for outcoming or incoming
            {
                cerr<<"That input was not recognized. Please enter either i for incoming or o for outgoing."<<endl;
            }
        }
        else // something other than yes or no was supplied for correct_input
        {
            cerr<<"That input was not recognized. Please try again."<<endl;
        }
    }
    else
    {
        cerr<<"Sorry, that was not a valid choice. Please enter 1 or 2 for the input."<<endl;
    }


}


void displayRules()
{
    int display_choice;

    cout<<"There are a few options for displaying IPtables rules. Please select from the list which rules you would like displayed."<<endl<<"1) ALL Rules"<<endl<<"2) INPUT Rules"<<endl<<"3) OUTPUT Rules"<<endl;
    cin>>display_choice;

    if(display_choice == 1)
        //This is displaying all the IPtables rules.
    {
        cout<<"iptables -L -v"<<endl<<"Note: a -n can be added to the end of the command to display the IP and port in numeric format (tends to be faster)."<<endl;
    }

    else if(display_choice == 2)
        //This is displaying just the input rules.
    {
        cout<<"iptables -L INPUT -v"<<endl;
    }

    else if(display_choice == 3)
        //This is displaying just the output rules.
    {
        cout<<"iptables -L OUTPUT -v"<<endl;
    }

    else
    {
        cerr<<"Sorry, that is not a valid choice. Please enter a number 1-3."<<endl;
    }

}

int checkLineNumber()
{
    int line_number;

    cout<<"Enter in the line number: "<<endl;

    while(!(cin>>line_number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr<<"ERROR: input must be a positive integer between 1 and 999999999."<<endl;
    }
    if(line_number<0 || line_number>999999999)
    {   cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr<<"ERROR: input must be a positive integer between 1 and 999999999."<<endl;
    }
    return line_number;
}

void insertRules()
{
    string direction_traffic;
    string correct_input;
    int line_number;
    correct_input="no";

    cout<<"To display the line number where you would like to insert a rule, in a command prompt, type 'iptables -L INPUT -n --line-numbers or iptables -L OUTPUT -n --line-numbers'."<<endl;

    while(!cin.fail() && (correct_input == "n" || correct_input == "no" || correct_input == "NO" || correct_input == "No"))
    {
        cout<<"Enter in the line number where you would like to insert a rule: "<<endl;
        cin>>line_number;
        if(cin.fail() || line_number<0 || line_number>999999999)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr<<"ERROR: input must be a positive integer between 1 and 999999999."<<endl;
            return;
        }
        else {
            cout<<"You have selected line number: "<<line_number<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Is this correct? Type y or n: "<<flush;
            cin>>correct_input;
        }

    }

    if(correct_input == "y" || correct_input == "yes" || correct_input == "YES" || correct_input == "Yes")
    {
        direction_traffic = checkDirection();
        if (direction_traffic == "i" || direction_traffic == "incoming" || direction_traffic == "INCOMING" || direction_traffic == "Incoming")
        {
            cout<<"iptables -I INPUT "<<line_number<<" <insert here>"<<endl;
        }
        else if (direction_traffic == "o" || direction_traffic == "outgoing" || direction_traffic == "OUTGOING" || direction_traffic == "Outgoing")
        {
            cout<<"iptables -I OUTPUT "<<line_number<<" <insert here>"<<endl;
        }
        else
        {
            cerr<<"Please enter either i for incoming or o for outgoing traffic."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else
    {
        cerr<<"Input not recognized. Please enter y or n if the IP specified is correct."<<endl;
    }

}


void deleteRules()
{
    string direction_traffic;
    string correct_input;
    int line_number;
    correct_input="no";

    cout<<"To display the line number of the rule you would like to delete, in a command prompt, type 'iptables -L INPUT -n --line-numbers or iptables -L OUTPUT -n --line-numbers'."<<endl;

    while(!cin.fail() && (correct_input == "n" || correct_input == "no" || correct_input == "NO" || correct_input == "No"))
    {
        cout<<"Enter in the line number where you would like to insert a rule: "<<endl;
        cin>>line_number;
        if(cin.fail() || line_number<0 || line_number>999999999)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr<<"ERROR: input must be a positive integer between 1 and 999999999."<<endl;
            return;
        }
        else {
            cout<<"You have selected line number: "<<line_number<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Is this correct? Type y or n: "<<flush;
            cin>>correct_input;
        }

    }



    if(correct_input == "y" || correct_input == "yes" || correct_input == "YES" || correct_input == "Yes")
    {
        direction_traffic = checkDirection();
        if (direction_traffic == "i" || direction_traffic == "incoming" || direction_traffic == "INCOMING" || direction_traffic == "Incoming")
        {
            cout<<"iptables -D INPUT "<<line_number<<endl;
        }
        else if (direction_traffic == "o" || direction_traffic == "outgoing" || direction_traffic == "OUTGOING" || direction_traffic == "Outgoing")
        {
            cout<<"iptables -D OUTPUT "<<line_number<<"."<<endl;
        }
        else
        {
            cerr<<"Please enter i for incoming or o for outgoing."<<endl;
        }
    }
    else
    {
        cerr<<"Input not recognized. Please try again."<<endl;
    }


}

void standardRules()
{
    int standard_option;

    cout<<"Choose from the following: "<<endl;
    cout<<"1) Drop all incoming and forwarded packets."<<endl;
    cout<<"2) Allow all outgoing traffic."<<endl;
    cout<<"3) Block an attacker's IP address."<<endl;
    cout<<"4) Block incoming requests on a certain port."<<endl;
    cout<<"5) Prevent outgoing access to domain or IP."<<endl;
    cout<<"6) Block an ICMP Ping request."<<endl;
    cin>>standard_option;

    if (standard_option == 1)
    {
        cout<<"iptables -P INPUT DROP"<<endl<<"iptables -P FORWARD DROP"<<endl;
    }

    else if (standard_option == 2)
    {
        cout<<"iptables -P OUTPUT ACCEPT"<<endl;
    }

    else if (standard_option == 3)
    {
        cout<<"iptables -A INPUT -s <ip> -j DROP"<<endl;
    }

    else if (standard_option == 4)
    {
        cout<<"iptables -A INPUT --dport <port> -j DROP"<<endl;
    }

    else if( standard_option == 5)
    {
        cout<< "iptables -A OUTPUT -p tcp -d www.facebook.com -j DROP"<<endl;
    }

    else if( standard_option == 6)
    {
        cout<<"iptables -A INPUT -p icmp --icmp-type echo-request -j DROP"<<endl;
    }

    else
    {
        cerr<<"Input not recognized. Please enter a choice 1-6."<<endl;
    }
}

#endif
