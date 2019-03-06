#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string decToBin(int);
string decToBinFractional(float partRightOfDecimal, int lhsSize);

int main() {
  while (1) {
    float num;
    int partLeftOfDecimal;
    float partRightOfDecimal, intPartTmp;
    vector<int> binaryPartRightOfDecimal;
    vector<int> binaryPartLeftOfDecimal;
    float partRightPlaceHolder;
    stringstream result;
    string leftPartBinary, rightPartBinary;
    string exponent;
    bool positive;

    cout << "Input num: ";
    cin >> num;

    positive = num > 0;
    if (!positive)
      num *= -1;
    partRightOfDecimal = modf(num, &intPartTmp);
    partLeftOfDecimal = intPartTmp;

    leftPartBinary = decToBin(partLeftOfDecimal);
    rightPartBinary =
        decToBinFractional(partRightOfDecimal, leftPartBinary.length());
    exponent = decToBin(leftPartBinary.length() - 1);

    for (int i = exponent.length(); i < 8; i++) {
      exponent = ('0' + exponent);
    }

    result << (positive ? '0' : '1') << exponent
           << leftPartBinary.substr(1, leftPartBinary.size() - 1)
           << rightPartBinary;

    cout << result.str() << endl;
    cout << "^^       ^" << endl
         << "||       |-mantissa" << endl
         << "|- exponent" << endl
         << "-sign" << endl;
  }
}

string decToBinFractional(float partRightOfDecimal, int lhsSize) {
  stringstream result;
  float partRightPlaceHolder;
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

  return result.str();
}

string decToBin(int i) {
  vector<int> bitHolder;
  stringstream result;
  do {
    bitHolder.push_back(i % 2);
    i /= 2;
  } while (i != 0);

  for (int i = bitHolder.size() - 1; i >= 0; i--) {
    result << bitHolder[i];
  }
  return result.str();
}
