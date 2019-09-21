#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string der_power(string coeff)
{
	string res = "";
	res.append(coeff);
	if(stoi(coeff) <= 2)
	{
		res = res + "*" + "x"; 
	}
	else
	{
		res = res + "*" + "x" + "^" + to_string(stoi(coeff) - 1);
	}
	return res; 
}

string cut_der_power(string coeff)
{
	string res = "";
	if(stoi(coeff) <= 2)
	{
		res = res + "*" + "x"; 
	}
	else
	{
		res = res + "*" + "x" + "^" + to_string(stoi(coeff) - 1);
	}
	return res; 
}

string derivative(string polynomial)
{
	string result = "";
	vector<int> coeff(2); 
	string num = ""; 

	bool mult = false; 
	for(auto i = 0; i < polynomial.length(); i++)
	{
		if(polynomial[i] == 'x' && polynomial[i + 1] == '^')
		{
			for(auto j = i + 2; j < polynomial.length(); j++)
			{
				if(polynomial[j] == '+' || polynomial[j] == '-')
				{
					break;
				}
				else
				{
					num = num + polynomial[j]; 
				}
			}
			if(!mult)
			{
				result = result + der_power(num);	
			}
			else
			{
				coeff[1] = stoi(num); 
				result = result + to_string(coeff[0] * coeff[1]) + cut_der_power(num);
				mult = false;
			}
			num = "";
		}
		else if(polynomial[i] == 'x' && polynomial[i + 1] == '+' || polynomial[i + 1] == '-')
		{
			result += 'x';
		}
		else if(polynomial[i] == '^' || polynomial[i - 1] == '^')
		{
			continue; 
		}
		else if(polynomial[i] == '+' || polynomial[i] == '-')
		{
			result += polynomial[i];
		}
		else if(polynomial[i] == '*')
		{
			mult = true; 
			coeff[0] = stoi(num);
			num = "";
		}
		else
		{
			num = num + polynomial[i];
			cout << polynomial[i] << " " << num << endl; 
		}
	}
	
	return result;
}

int main( )
{
	string polynom = "x^10000+x+1"; 
	cout << derivative(polynom) << endl; 

	return 0; 
}