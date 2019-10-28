#include <iostream>
#include <map>
#include <string>

#include <cassert>

using namespace std;

string derivate(string input)
{
    map<int, signed int> data;

    string part;
    string power;
    string k;
    string result = "";
    bool been = false;


    while( input.length() > 0 )
    {
        int16_t pos = input.find('+') == string::npos ? input.find('-') : input.find('+');

        if( input.find('+') < input.find('-') )
            pos = input.find('+');
        else
        {
            pos = input.find('-');
//        cout << "POS 28 " << pos << endl;

            if( input.find('-') != string::npos )
            {
    //            cout << "MINUS HERE" << endl;
                pos = input.find('-');
                if( pos == 0 )
                {
                    string tmp = input.substr(1, input.length());
                    if( tmp.find('+') != string::npos )
                        pos = tmp.find('+') + 1;
                    else
                        pos = tmp.find('-') + 1;
                }
            }
        }
//        cout << "POS " << pos << endl;
        if( input.find('+') !=  string::npos )
        {
            part = input.substr(0, pos);
        }
        else if( input.find('-') != string::npos && pos != 0 )
            part = input.substr(0, pos);
        else
        {
            part = input.substr(0, input.length());
        }

//        cout << "Part is " << part << endl;

        power = "";
        k = "";

        if( part.find('^') != string::npos )
        {
            uint16_t mult_pos = part.find('^');
            for( uint16_t i = mult_pos + 1; i < part.length(); i++ )
            {
                if( i != '*')
                    power += part[i];
                else
                    break;
            }
//            cout << "Found ^ " << power << ": " << data[stoi(power)] << endl;
            data[stoi(power)] += 0; // as default
//            cout << "After Found " << power << ": " << data[stoi(power)] << endl;
        }
        if( part.find('*') != string::npos )
        {
            uint16_t x_pos = part.find('*');
            for( uint16_t i = 0; i < x_pos; i++ )
            {
                k += part[i];
            }
            if( /*data.size() == 0 ||*/ power == "" ) power = "1";
//            if( part[0] == 0 ) data[stoi(power)] += -stoi(k); // as default
            /*else */data[stoi(power)] += stoi(k); // as default
        }
        if( part[0] == '-' && part.find('x') == 1 && part.find('*') == string::npos)
        {

            data[stoi(power)] += -1;
//            cout << "MINUSSSS " << power << ": " << data[stoi(power)] << endl;
        }

        if( part.find('x') != string::npos && part.find('*') == string::npos
            && part.find('^') == string::npos)
        {

            data[1] += 1;
        }
        else if( k == "" && power != "" && part[0] != '-')
        {
//            cout << "Else if" << endl;
            data[stoi(power)] += 1;
        }

//        for( auto iter = data.rbegin(); iter != data.rend(); iter++ )
//        {
//            cout << iter -> first << ": " << iter -> second << endl;
//        }



        pos = pos < 0 ? input.length() - 1 : pos;
//        cout << "POS POS POS " << pos << " " << input << " " << input[pos] << endl;
        if( input[pos] == '-' )
        {
            if( been )
            {
                string tmp = input.substr(1, input.length());
                pos = tmp.find('-');
//                cout << "BEEN " << pos << endl;
                input = "";
                break;
            }
            been = true;
//            cout << "first been " << endl;
            input = input.substr(pos, input.length());
        }
        else
        {
//            cout << "else end " << pos << endl;
            input = input.substr(pos + 1, input.length());
            been = false;
        }

//        cout << "NEW INPUT is " << input << endl;
    }
    for( auto iter = data.rbegin(); iter != data.rend(); iter++ )
    {
//        cout << iter -> first << ": " << iter -> second << endl;
        if( iter -> first == 2 && iter -> second != 0)
        {
            result += to_string(iter -> first * iter -> second) + "*x";
        }
        else if( iter -> first > 2 && iter -> second != 0 )
        {
            if( result.size() == 0 )
                result += to_string(iter -> first * iter -> second) + "*x";
            result += "^" + to_string(iter -> first - 1);
            if( iter -> second > 0 )
                result += "+";
        }
        else if( iter -> second == 0 )
        {
            if( iter -> first == 0 && data.size() == 1 )
            {
                result = "0";
            }
            else
                continue;
        }
        else
        {
            if(result[result.length() - 1] == '+')
                result = result.substr(0, result.length() - 1);
            if( data.size() == 1 )
                result += to_string(iter -> first * iter -> second);
            else if( result == "")
                result += to_string(iter -> first * iter -> second );
            else
            {
                if( iter -> second < 0 )
                    result += to_string(iter -> first * iter -> second );
                else
                    result += + "+" + to_string(iter -> first * iter -> second );
            }

        }
    }
    if( data.size() == 0 ) result = "0";
//    cout << "RESULT!!!!!!!! " << result << endl;
    return result;
}


int main()
{
    assert(derivate("x^2+x") == "2*x+1");
    cout << "x^2+x\t\t\tpassed\tOK" << endl;
    assert(derivate("2*x^100+100*x^2") == "200*x^99+200*x");
    cout << "2*x^100+100*x^2\t\tpassed\tOK" << endl;
    assert(derivate("x^10000+x+1") == "10000*x^9999+1");
    cout << "x^10000+x+1\t\tpassed\tOK" << endl;
    assert(derivate("-x^2-x^3") == "-3*x^2-2*x");
    cout << "-x^2-x^3\t\tpassed\tOK" << endl;
    assert(derivate("x+x+x+x+x+x+x+x+x+x") == "10");
    cout << "x+x+x+x+x+x+x+x+x+x+x\tpassed\tOK" << endl;
    assert(derivate("10*x-9*x") == "1");
    cout << "10*x-9*x\t\tpassed\tOK" << endl;
    assert(derivate("x+x^2+x^3") == "3*x^2+2*x+1");
    cout << "x+x^2+x^3\t\tpassed\tOK" << endl;
    assert(derivate("x^2-x^2+x") == "1");
    cout << "x^2-x^2+x\t\tpassed\tOK" << endl;
    assert(derivate("x^2+x^2+x") == "4*x+1");
    cout << "x^2+x^2+x\t\tpassed\tOK" << endl;
    assert(derivate("0*x^0") == "0");
    cout << "0*x^0\t\t\tpassed\tOK" << endl;
    assert(derivate("10") == "0");
    cout << "10\t\t\tpassed\tOK" << endl;
    assert(derivate("100*x-20*x") == "80");
    cout << "100*x-20*x\t\tpassed\tOK" << endl;
    assert(derivate("x^3+2*x^2-3*x+5") == "3*x^2+4*x-3");
    cout << "x^3+2*x^2-3*x+5\t\tpassed\tOK" << endl;
    assert(derivate("-7") == "0");
    cout << "-7\t\t\tpassed\tOK" << endl;
    assert(derivate("11-6*x") == "-6");
    cout << "11-6*x\t\t\tpassed\tOK" << endl;
    assert(derivate("5*x+5") == "5");
    cout << "5*x+5\t\t\tpassed\tOK" << endl;
    assert(derivate("12*x-x^3") == "-3*x^2+12");
    cout << "12*x-x^3\t\tpassed\tOK" << endl;
    assert(derivate("x^3+3*x^2-72*x+90") == "3*x^2+6*x-72");
    cout << "x^3+3*x^2-72*x+90\tpassed\tOK" << endl;
    assert(derivate("0*x^3000+3*x^2-72*x+90") == "6*x-72");
    cout << "0*x^3000+3*x^2-72*x+90\tpassed\tOK" << endl;
    assert(derivate("2*x^3000+0*x^2-72*x+90") == "6000*x^2999-72");
    cout << "2*x^3000+0*x^2-72*x+90\tpassed\tOK" << endl;
    assert(derivate("1+x^2+1+0") == "2*x");
    cout << "x^2+1\t\t\tpassed\tOK" << endl;
    assert(derivate("100*x-20*x+10*x-50*x") == "40");
    cout << "100*x-20*x+10*x-50*x\t\tpassed\tOK" << endl;

//    cout << derivate("x^3+2*x^2-3*x+5") << endl;
//    cout << derivate("10") << endl;





    return 0;
}
