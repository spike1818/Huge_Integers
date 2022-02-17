#include "HugeInteger.h"
#include "ctype.h"
#include <string>
using namespace std;

HugeInteger::HugeInteger(const std::string& val) {

	bool valid = true;

	if (val.find_first_not_of("-0123456789") != string::npos) {
		valid = false;
	}

	if (val.length() == 0) {
		valid = false;
	}

	for (size_t i = 1; i < val.length(); i++) {
		if ((int)val[i] == 45) {
			valid = false;
			i = val.length() + 1;
		}
	}

	if (valid){
		if (val[0] == '-') {
			positive = false;
			value = val.substr(1);
		}
		else {
			positive = true;
			value = val;
		}
	}
	else {
		throw("Invalid arguments");
	}
}

HugeInteger::HugeInteger(int n) {


	bool valid = (n > 0);
	string digit;
	string val = "";

	/*
	int sign = rand() % 1; // Randomly Determines if the number generated is negative (this is currently removed for this section of the lab but I can un-comment it if needed)
	if (sign == 0) {
		val += "-";
	}*/

	for (int i = 0; i < n; i++) { //adds a random digit n times
		digit = to_string(rand() % 10);
		val = digit + val;
	}
	if (valid) {
		value = val;
	}
	else {
		throw("Invalid arguments");
	}
}

int HugeInteger::valCompare(string a, string b) {

	string digit1;
	string digit2;

	if (a == b) {
		return 0;
	}
	else {
		for (size_t i = 0; i < a.length(); i++) {
			digit1 = a[i];
			digit2 = b[i];
			if (stoi(digit1) > stoi(digit2)) {
				return 1;
			}
			else if (stoi(digit1) < stoi(digit2)) {
				return -1;
			}
		}
	}
}

std::string HugeInteger::valAdd(string a, string b) {

	if (a.length() > b.length()) { // pad smaller string with 0 to account for differences in sizes
		while (b.length() < a.length()) {
			b = "0" + b;
		}
	}
	else if (a.length() < b.length()) {
		while (b.length() > a.length()) {
			a = "0" + a;
		}
	}

	string num1;
	string num2;
	int digitSum;
	int carry = 0;

	string newValue;

	for (int i = a.length() - 1; i >= 0; i--) {
		num1 = a[i]; // for some reason stoi() woudnt accept the strings unless I did this idk why
		num2 = b[i];

		digitSum = stoi(num1) + stoi(num2) + carry;
		if (digitSum > 9) {
			digitSum = digitSum % 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		newValue = to_string(digitSum) + newValue;
	}

	if (carry == 1) {
		newValue = to_string(carry) + newValue;
	}

	return newValue;
}

std::string HugeInteger::valSub(string a, string b) {

	if (a.length() > b.length()) { // pad smaller string with 0 to account for differences in sizes
		while (b.length() < a.length()) {
			b = "0" + b;
		}
	}
	else if (a.length() < b.length()) {
		while (b.length() > a.length()) {
			a = "0" + a;
		}
	}

	string num1;
	string num2;
	int digitDiff;
	int carry = 0;
	int nextCarry = 0;

	bool isNeg = false;

	string newValue;

	for (int i = a.length() - 1; i >= 0; i--) {
		num1 = a[i]; // for some reason stoi() woudnt accept the strings unless I did this idk why
		num2 = b[i];
		carry = nextCarry;


		if (stoi(num1) - stoi(num2) - carry < 0) {
			nextCarry = 1;
			num1 = "1" + num1;
		}
		else {
			nextCarry = 0;
		}

		digitDiff = stoi(num1) - carry - stoi(num2);

		newValue = to_string(digitDiff) + newValue;
	}

	while (newValue[0] == '0' && newValue.length() > 1) { //removes the zero pad from the output
		newValue = newValue.substr(1);
	}

	return newValue;
}

string HugeInteger::valMul(string a, string b) {

	if (a.length() > b.length()) { // pad smaller string with 0 to account for differences in sizes
		while (b.length() < a.length()) {
			b = "0" + b;
		}
	}
	else if (a.length() < b.length()) {
		while (b.length() > a.length()) {
			a = "0" + a;
		}
	}

	string num1;
	string num2;
	string digitless;
	string currentSum;

	int digitMul;
	int ind1 = 0;
	int ind2 = 0;

	int aLen = a.length();
	int bLen = b.length();


	for (size_t i = bLen - 1; i >= 0 && i < bLen; i--) {
		num2 = b[i];
		ind1 = 0;

		for (size_t j = aLen - 1; j >= 0 && j < aLen; j--) {
			num1 = a[j];

			digitMul = stoi(num2) * stoi(num1);
			digitless = to_string(digitMul);

			for (int k = 0; k < ind1 + ind2; k++) {
				digitless = digitless + "0";
			}
			ind1++;
			currentSum = valAdd(currentSum, digitless);
		}
		ind2++;
	}
	while (currentSum[0] == '0' && currentSum.length() > 1) { //removes the zero pad from the output
		currentSum = currentSum.substr(1);
	}

	return currentSum;
}


HugeInteger HugeInteger::add(const HugeInteger& h) { //Assumes both numbers are positive

	int carry = 0;
	string newValue = "";
	bool newSign;
	string num1;
	string num2;

	string huge1 = value;
	string huge2 = h.value;

	bool pos1 = positive;
	bool pos2 = h.positive;

	if (huge1.length() > huge2.length()) { // pad smaller string with 0 to account for differences in sizes
		while (huge2.length() < huge1.length()) {
			huge2 = "0" + huge2;
		}
	}
	else if (huge1.length() < huge2.length()) {
		while (huge2.length() > huge1.length()) {
			huge1 = "0" + huge1;
		}
	}

	if (pos1 == pos2) {
		newSign = pos1;
		newValue = valAdd(huge1, huge2);
	}
	else if (!pos2) {
		newSign = (huge2 < huge1);
		if (newSign) {
			newValue = valSub(huge1, huge2);
		}
		else {
			newValue = valSub(huge2, huge1);
		}
	}
	else {
		newSign = (huge1 < huge2);
		if (newSign){
			newValue = valSub(huge2, huge1);
		}
		else{
			newValue = valSub(huge1, huge2);
		}
	}

	if (!newSign && newValue != "0") {
		newValue = "-" + newValue;
	}

	return HugeInteger(newValue);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	string newValue;
	bool newSign;

	string huge1 = value;
	string huge2 = h.value;

	bool pos1 = positive;
	bool pos2 = h.positive;

	if (huge1.length() > huge2.length()) { // pad smaller string with 0 to account for differences in sizes
		while (huge2.length() < huge1.length()) {
			huge2 = "0" + huge2;
		}
	}
	else if (huge1.length() < huge2.length()) {
		while (huge2.length() > huge1.length()) {
			huge1 = "0" + huge1;
		}
	}

	if (pos1 == pos2) {
		if (valCompare(huge1, huge2) == -1) {
			newSign = !pos1;
			newValue = valSub(huge2, huge1);
		}
		else {
			newSign = pos1;
			newValue = valSub(huge1, huge2);
		}
	}
	else {
		newSign = pos1;
		newValue = valAdd(huge1, huge2);
	}
	/*
	while (newValue[0] == '0') {
		newValue = newValue.substr(1);
	}*/

	if (!newSign && newValue != "0") {
		newValue = "-" + newValue;
	}

	return HugeInteger(newValue);
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	string huge1 = value;
	string huge2 = h.value;

	bool pos1 = positive;
	bool pos2 = h.positive;

	string newValue;
	bool newSign = false;

	if (pos1 == pos2) {
		newSign = true;
	}

	newValue = valMul(huge1, huge2);

	if (!newSign && newValue != "0") {
		newValue = "-" + newValue;
	}

	return HugeInteger(newValue);
}

int HugeInteger::compareTo(const HugeInteger& h) {

	string num1 = value;
	string num2 = h.value;
	bool pos1 = positive;
	bool pos2 = h.positive;

	string a;
	string b;

	if (num1.length() > num2.length()) { // pad smaller string with 0 to account for differences in sizes
		while (num2.length() < num1.length()) {
			num2 = "0" + num2;
		}
	}
	else if (num1.length() < num2.length()) {
		while (num2.length() > num1.length()) {
			num1 = "0" + num1;
		}
	}

	if (pos1 == pos2) {
		if (num1 == num2) {
			return 0;
		}
		else if (pos1 == false){ 
				for (size_t i = 0; i < num1.length(); i++) {
					a = num1[i];
					b = num2[i];
					if (stoi(a) < stoi(b)) {
						return 1;
					}
					else if (stoi(a) > stoi(b)) {
						return -1;
					}
			}
		}
		else{
			for (size_t i = 0; i < num1.length(); i++) {
				a = num1[i];
				b = num2[i];
				if (stoi(a) > stoi(b)) {
					return 1;
				}
				else if (stoi(a) < stoi(b)) {
					return -1;
				}
			}
		}
	}
	else if (pos1) {
		return 1;
	}
	else {
		return -1;
	}
	return 0;
}

std::string HugeInteger::toString() {
	string word = value;
	if (!positive) {
		word = "-" + word;
	}
	return word;
}
