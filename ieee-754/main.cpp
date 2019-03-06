#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  float num;
  cout << "Input num: ";
  cin >> num;

  int partLeftOfDecimal;
  float partRightOfDecimal, intPartTmp;

  partRightOfDecimal = modf(num, &intPartTmp);
  partLeftOfDecimal = intPartTmp;

  cout << "right : " << partRightOfDecimal << " left: " << partLeftOfDecimal
       << endl;

  vector<int> binaryPartRightOfDecimal;
  vector<int> binaryPartLeftOfDecimal;

  while (partLeftOfDecimal != 0) {
    binaryPartLeftOfDecimal.push_back(partLeftOfDecimal % 2);
    partLeftOfDecimal /= 2;
    // cout << partLeftOfDecimal << endl;
  }

  // cout << "above for loop" << endl;
  for (int i = binaryPartLeftOfDecimal.size() - 1; i >= 0; i--) {
    //  cout << "in loop" << endl;
    cout << binaryPartLeftOfDecimal[i];
  }

  cout << '.';

  int asdf = 1;
  float tmp;
  while (
      (binaryPartRightOfDecimal.size() + binaryPartLeftOfDecimal.size() < 24)) {
    //    cout << "partRightOfDecimal "<<partRightOfDecimal;

    tmp = partRightOfDecimal * 2;
    if (tmp >= 1) {
      binaryPartRightOfDecimal.push_back(int(tmp));
      partRightOfDecimal = tmp - 1;
    } else {
      binaryPartRightOfDecimal.push_back(int(tmp));
      partRightOfDecimal = tmp;
    }
  }

  for (int i = 0; i < binaryPartRightOfDecimal.size(); i++) {
    cout << binaryPartRightOfDecimal[i];
  }

  cout << endl;
}
