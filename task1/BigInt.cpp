#include "BigInt.h"

#define _CRT_SECURE_NO_WARNINGS

int BigInt::getIntAt(int i) const
{
	return  i >= 0 ? (int)val[i] - 48 : 0;
}

void BigInt::copyResult(char* result, int resLen)
{
	memset(val, 0, sizeof(val));
	int i = 0;
	while (resLen >= 0) {
		
		val[i] = result[resLen];
		i++;
		resLen--;
	}

	val[i] = 0;

	delete[] result;
}

void BigInt::addDecimals(int dec) {
	int i = strlen(val);
	while (dec > 0) {
		val[i] = '0';
		i++;
		dec--;
	}
	val[i] = 0;
}

void BigInt::Free()
{
	if (val) {
		delete[] val;
		val = nullptr;
	}
}

void BigInt::trunc()
{
	if (strlen(val) < 2 || val[0] != '0') {
		return;
	}
	strcpy_s(&val[0], maxVal - 1,&val[1]);
	trunc();
}

bool BigInt::operator==(const BigInt& rhs)
{
	return strcmp(val, rhs.val) == 0;
}

bool BigInt::operator!=(const BigInt& rhs)
{
	return strcmp(val, rhs.val) != 0;
}


BigInt& BigInt::operator=(const BigInt& rhs)
{
	delete[] val;
	val = new char[maxVal + 2];
	strcpy_s(val, maxVal, rhs.val);
	negative = rhs.negative;
	return *this;
};

BigInt& BigInt::operator/=(const BigInt& rhs)
{
	int i = 0;

	BigInt answer{ "0", maxVal };
	BigInt div{ "0", maxVal };

	while (i < (int)strlen(val)) {
		bool run = true;

		while (run) {
			div.addDecimals(1);
			div += BigInt(val[i], maxVal);

			BigInt temp{ div };
			temp -= rhs;
			i++;

			run = temp.negative && temp != BigInt("0") && i < (int)strlen(val);

			if (run) {
				answer.addDecimals(1);
			}
		}

		int num = 0;

		run = true;
		while (run) {
			BigInt temp{ div };
			temp -= rhs;
			run = !temp.negative;

			if (run) {
				num++;
				div = temp;
			}
		}

		if (num) {
			answer.addDecimals(1);
			answer += num;
		}
	}

	remain = new BigInt(div);
	*this = answer;
	this->trunc();

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& rhs)
{
	int j = strlen(rhs.val) - 1;

	BigInt temp("0", maxVal);

	while (j >= 0) {
		int mult = rhs.getIntAt(j);
		if (j != strlen(rhs.val) - 1)
		{
			addDecimals(1);
		}

		while (mult > 0) {
			temp += *this;
			mult--;
		}
		j--;
	}

	*this = temp;
	this->trunc();
	return *this;
}

BigInt& BigInt::operator+=(const int& rhs)
{
	*this += BigInt(std::to_string(rhs).c_str(), maxVal);
	return *this;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	int i = strlen(val) - 1;
	int j = strlen(rhs.val) - 1;
	char* result = new char[maxVal + 2];

	int k = 0;
	int carry = 0;

	while (i >= 0 || j >= 0) {

		int v1 = getIntAt(i);
		int v2 = rhs.getIntAt(j);
		int sum = v1 + v2 + carry;

		carry = 0;
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}

		result[k] = (char)(sum + 48);

		k++;
		if (k > maxVal) {
			break;
		}
		j--;
		i--;
	}

	if (carry) {
		result[k] = (char)(1 + 48);
		k++;
	}

	copyResult(result, --k);
	this->trunc();
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
	int i = strlen(val) - 1;
	int j = strlen(rhs.val) - 1;
	char* result = new char[maxVal + 2];

	int k = 0;
	int carry = 0;
	bool isGreater = (*this > rhs);

	negative = !isGreater && *this != rhs;

	while (i >= 0 || j >= 0) {

		int v1 = getIntAt(i);
		int v2 = rhs.getIntAt(j);

		int dif = isGreater ? (v1 - v2 - carry) : (v2 - v1 - carry);

		carry = 0;
		if (dif < 0) {
			carry = 1;
			dif += 10;
		}

		result[k] = (char)(dif + 48);

		k++;
		j--;
		i--;
	}

	copyResult(result, --k);
	this->trunc();
	return *this; // return the result by reference
}

bool BigInt::operator>(const BigInt& rhs)
{
	int i = strlen(val) - 1;
	int j = strlen(rhs.val) - 1;

	if (i == j) {
		for (int k = 0; k <= i; k++) {
			if (getIntAt(k) != rhs.getIntAt(k)) {
				return getIntAt(k) > rhs.getIntAt(k);
			}
		}
		return false;
	}
	return i > j;
}

bool BigInt::operator>=(const BigInt& rhs)
{
	return *this > rhs || *this == rhs;
}

std::ostream& operator<<(std::ostream& out, const BigInt& bi)
{
	if (bi.negative) {
		out << '-';
	}

	out << bi.val;

	if (bi.remain) {
		out << " ( liekana yra " << *bi.remain << " )";
	}

	return out;
}

std::istream& operator>>(std::istream& in, const BigInt& bi) {
    return std::cin >> bi.val;
}
