#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

class BigInt {
	const int maxVal;
	char* val{ NULL };
	bool negative{ false };

	BigInt* remain{ NULL };

	int getIntAt(int i) const;
	void copyResult(char* result, int resLen);
	void addDecimals(int dec);
	void Free();

	void trunc();



public:

	BigInt(const char* val_ = "0", const int maxVal = 20) : maxVal(maxVal) {
		val = new char[maxVal+2];
		strcpy_s(val, maxVal, val_);
	}

	BigInt(const char c = '0', const int maxVal = 20) : maxVal(maxVal) {
		val = new char[maxVal];
		val[0] = c;
		val[1] = 0;
	}

	BigInt(const BigInt& copy) : maxVal(copy.maxVal) {
		val = new char[maxVal];
		strcpy_s(val, maxVal, copy.val);
		negative = copy.negative;
	}

	~BigInt() {
		Free();
		if (remain) {
			remain->Free();
		}
	}

	BigInt& operator=(const BigInt& rhs);

	BigInt& operator/=(const BigInt& rhs);

	BigInt& operator*=(const BigInt& rhs);

	BigInt& operator+=(const int& rhs);

	BigInt& operator+=(const BigInt& rhs);

	BigInt& operator-=(const BigInt& rhs);

	bool operator>(const BigInt& rhs);
	bool operator>=(const BigInt& rhs);

	bool operator==(const BigInt& rhs);

	bool operator!=(const BigInt& rhs);

	bool overMax() const { return strlen(val) > maxVal/1000;}

	bool isZero() const { return val[0] == '0';}

	friend std::ostream& operator<<(std::ostream& out, const BigInt& bi);
	friend std::istream& operator>>(std::istream& in, const BigInt& bi);
};
