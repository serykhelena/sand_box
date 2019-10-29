#include <iostream>
#include <map>
#include <string>

#include <bits/stdc++.h>

#include <cassert>

using namespace std;

string derivate(string polynomial)
{
    map<int, signed int> data;

    string part;
    string power;
    string k;
    string result = "";
    bool been = false;
    int64_t pos = 0;


    while( polynomial.length() > 0 )
    {
        /* split statement by term */
        if( polynomial.find('+') < polynomial.find('-') && polynomial.find('+') != string::npos )
            pos = polynomial.find('+');
        else if( polynomial.find('-') != string::npos ) // if thre is minus in statement
        {
            pos = polynomial.find('-');
            if( pos == 0 ) // if statement starts with minus
            {
                string tmp = polynomial.substr(1, polynomial.length());
                if( tmp.find('+') < tmp.find('-') && tmp.find('+') != string::npos )
                    pos = tmp.find('+') + 1;
                else
                    pos = tmp.find('-') + 1;

                if( pos == 0 ) pos = polynomial.length();
            }
        }
        else
            pos = polynomial.length();

        part = polynomial.substr(0, pos);
        /* new part */
        power = "";
        k = "";

        if( part.find('^') != string::npos )
        {
            uint64_t mult_pos = part.find('^');
            for( uint64_t i = mult_pos + 1; i < part.length(); i++ )
            {
                if( i != '*') power += part[i];
                else break;
            }
            data[stoi(power)] += 0; // as default
        }
        if( part.find('*') != string::npos )
        {
            uint64_t x_pos = 0;
            string tmp = part;
            string val = "";
            k = "1";
            for( auto j = 0; j < count(part.begin(), part.end(), '*'); j++ )
            {
                x_pos = tmp.find('*');
                for( uint64_t i = 0; i < x_pos; i++ )
                {
                    val += tmp[i];
                }
                tmp = part.substr(x_pos + 1, part.length());
                k = to_string(stoi(k) * stoi(val));
                val = "";
            }

            if( power == "" ) power = "1";
            data[stoi(power)] += stoi(k); // as default
        }
        if( part[0] == '-' && part.find('x') == 1 && part.find('*') == string::npos)
        {
            if( power == "" ) power = "1";
            data[stoi(power)] += -1;
        }
        else if( part.find('x') != string::npos && part.find('*') == string::npos
            && part.find('^') == string::npos )
        {
            data[1] += 1;
        }
        else if( k == "" && power != "" && part[0] != '-')
            data[stoi(power)] += 1;

        if( pos == static_cast<int64_t>(polynomial.length()) )
            polynomial = "";
        else if( polynomial[pos] == '-' )
        {
            if( been )
            {
                string tmp = polynomial.substr(1, polynomial.length());
                pos = tmp.find('-') + 1;
            }
            else been = true;

            polynomial = polynomial.substr(pos, polynomial.length());
        }
        else
        {
            polynomial = polynomial.substr(pos + 1, polynomial.length());
            been = false;
        }
    }

    for( auto iter = data.rbegin(); iter != data.rend(); iter++ )
    {
        if( iter -> first == 2 && iter -> second != 0)
        {
            result += to_string(iter -> first * iter -> second) + "*x";
        }
        else if( iter -> first > 2 && iter -> second != 0 )
        {
            if( result.size() == 0 )
                result += to_string(iter -> first * iter -> second) + "*x";
            result += "^" + to_string(iter -> first - 1);
            if( iter -> second > 0 && data.size() > 1 )
                result += "+";
        }
        else if( iter -> second == 0 )
        {
            if( iter -> first == 0 && data.size() == 1 )
            {
                result = "0";
            }
            else if( data.size() == 1 )
                result = to_string(iter -> first * iter -> second);
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
    cout << "100*x-20*x+10*x-50*x\tpassed\tOK" << endl;
    assert(derivate("-x^2+x^2+x") == "1");
    cout << "-x^2+x^2+x\t\tpassed\tOK" << endl;
    assert(derivate("-x^2-x^2+x") == "-4*x+1");
    cout << "-x^2-x^2+x\t\tpassed\tOK" << endl;
    assert(derivate("-x^2-x^2-x") == "-4*x-1");
    cout << "-x^2-x^2-x\t\tpassed\tOK" << endl;
    assert(derivate("x-x-x-x-x-x-x-x-x-x") == "-8");
    cout << "x-x-x-x-x-x-x-x-x-x\tpassed\tOK" << endl;
    assert(derivate("-x-x-x-x-x-x-x-x-x-x") == "-10");
    cout << "-x-x-x-x-x-x-x-x-x-x\tpassed\tOK" << endl;
    assert(derivate("-7*0*x") == "0");
    cout << "-7*0*x\t\t\tpassed\tOK" << endl;
    assert(derivate("-1*x^2-2*x^3-3*x^2") == "-6*x^2-8*x");
    cout << "-1*x^2-2*x^3-3*x^2\tpassed\tOK" << endl;
    assert(derivate("-1*x^1-2*x^3-3*x^2") == "-6*x^2-6*x-1");
    cout << "-1*x^1-2*x^3-3*x^2\tpassed\tOK" << endl;
    assert(derivate("-x-x-1256895") == "-2");
    cout << "-x-x-1256895\t\tpassed\tOK" << endl;
    assert(derivate("x-1") == "1");
    cout << "x-1\t\t\tpassed\tOK" << endl;
    assert(derivate("x^600000-1") == "600000*x^599999");
    cout << "x^600000-1\t\tpassed\tOK" << endl;

    return 0;
}
