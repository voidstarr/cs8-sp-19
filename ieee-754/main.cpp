#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string decToBin(int i);
string decToBinFractional(float partRightOfDecimal, int lhsSize);

int main() {
  while (1) {
    float num;                // number we want to convert
    int partLeftOfDecimal;    // Part of the number to the left of the decimal
    float partRightOfDecimal; // Part of the number to the right of the decimal
    float intPartTmp; // place holder for partLeftOfDecimal, need float for modf
    string leftPartBinary,
        rightPartBinary; // right part and left part converted to binary
    string exponent;     // exponent part of the IEEE 754 standard
    bool positive;       // is the input number positive?

    // get the number we will be working on
    cout << "Input num: ";
    cin >> num;

    // determine whether or not this number is positive
    positive = num > 0;
    // if it is not, make it postitive so we don't encounter any weirdness
    if (!positive)
      num *= -1;
    // split the number at the decimal point
    partRightOfDecimal = modf(num, &intPartTmp);
    partLeftOfDecimal = intPartTmp;

    // do conversions to binary
    leftPartBinary = decToBin(partLeftOfDecimal);
    rightPartBinary =
        decToBinFractional(partRightOfDecimal, leftPartBinary.length());

    // figure the exponent and convert it to binary
    exponent = decToBin(leftPartBinary.length() - 1 + 127);
    // left pad zeros for our exponent field
    for (int i = exponent.length(); i < 8; i++) {
      exponent = ('0' + exponent);
    }

    // print it all out
    cout << (positive ? '0' : '1') << exponent
         << leftPartBinary.substr(1, leftPartBinary.size() - 1)
         << rightPartBinary << endl
         << "^^       ^" << endl
         << "||       |-mantissa" << endl
         << "|- exponent" << endl
         << "-sign" << endl;
  }
}

// In this function, we multiply our fractional number by 2
// if the result is greater than 1, push back 1
//                                 and subtract one
// if the result is less than 1 push back 0
string decToBinFractional(float partRightOfDecimal, int lhsSize) {
  stringstream result;
  float partRightPlaceHolder;

  // while we have don't have a large enough mantissa to satisfy
  // the IEEE 754 standard, find more bits
  while (lhsSize + result.tellp() < 24) {
    partRightPlaceHolder = partRightOfDecimal * 2;
    if (partRightPlaceHolder >= 1) {
      result << int(partRightPlaceHolder);
      partRightOfDecimal = partRightPlaceHolder - 1;
    } else {
      result << int(partRightPlaceHolder);
      partRightOfDecimal = partRightPlaceHolder;
    }
  }
  // ship it
  return result.str();
}

string decToBin(int i) {
  vector<int> bitHolder;
  stringstream result;
  // find remainders of integer division representing binary digits in reverse
  // order
  do {
    bitHolder.push_back(i % 2);
    i /= 2;
  } while (i != 0);

  // reverse the bits to give us what we want.
  // what do you think this is? big endian?
  for (int i = bitHolder.size() - 1; i >= 0; i--) {
    result << bitHolder[i];
  }
  // ship it
  return result.str();
}
