#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
using namespace std;

class HugeInteger
{
private:

	
	
public:

	string value;
	bool positive;

	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	int valCompare(string a, string b);
	string valAdd(string a, string b);
	string valSub(string a, string b);
	string valMul(string a, string b);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */
