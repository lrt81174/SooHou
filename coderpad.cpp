#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct sVector {
    vector<unsigned int> first_hundreds;
    vector<unsigned int> second_hundreds;
    vector<unsigned int> third_hundreds;
    vector<unsigned int> fourth_hundreds;
} sNumVec;

void number_parse(unsigned int iNum, unsigned int iNumLen, vector<unsigned int> &vNum, sVector &sNumVec) {
    unsigned int iNumPrev = iNum;
    unsigned int iNumSub = 0, iNumRest = 0;

    while (iNum)
    {
        iNum /= 10;
        iNumSub = iNum * 10;
        iNumRest = iNumPrev - iNumSub;
        iNumPrev = iNum;
        vNum.push_back(iNumRest);
    }

    iNumLen = vNum.size();

    static int i = 0;
    while (i < 3)
    {
      if (i == iNumLen)
        break;
       sNumVec.first_hundreds.push_back(vNum[i]);
       ++i;
    }
    reverse(sNumVec.first_hundreds.begin(), sNumVec.first_hundreds.end());

    while ((i>2) && (i<6))
    {
      if (i == iNumLen)
        break;
      sNumVec.second_hundreds.push_back(vNum[i]);
      ++i;
    }
    reverse(sNumVec.second_hundreds.begin(), sNumVec.second_hundreds.end());

    while ((i>5) && (i<9))
    {
      if (i == iNumLen)
        break;
      sNumVec.third_hundreds.push_back(vNum[i]);
      ++i;
    }
    reverse(sNumVec.third_hundreds.begin(), sNumVec.third_hundreds.end());

    while ((i > 8) && (i < 12))
    {
      if (i == iNumLen)
        break;
      sNumVec.fourth_hundreds.push_back(vNum[i]);
      ++i;
    }
    reverse(sNumVec.fourth_hundreds.begin(), sNumVec.fourth_hundreds.end());

    //return num_len;
}

string single_digit(unsigned int iNum) {
  map<int, string> single;
  //single[0] = "null";
  single[1] = "ein";
  single[2] = "zwei";
  single[3] = "drei";
  single[4] = "vier";
  single[5] = "fuenf";
  single[6] = "sechs";
  single[7] = "sieben";
  single[8] = "acht";
  single[9] = "neun";
  
  return single[iNum];
}

string dozens_number(unsigned int iNum) {
  map<int, string> dozens;
  dozens[0] = "zehn";
  dozens[1] = "elf";
  dozens[2] = "zwoelf";
  dozens[3] = "dreizehn";
  dozens[4] = "vierzehn";
  dozens[5] = "fuenfzehn";
  dozens[6] = "sechzehn";
  dozens[7] = "siebzehn";
  dozens[8] = "achtzehn";
  dozens[9] = "neunzehn";
  
  return dozens[iNum];
}

string tens_digit(unsigned int iNum) {
  map<int, string> tens;
  tens[2] = "zwanzig";
  tens[3] = "dreissig";
  tens[4] = "vierzig";
  tens[5] = "fuenfzig";
  tens[6] = "sechzig";
  tens[7] = "siebzig";
  tens[8] = "achtzig";
  tens[9] = "neunzig";
  
  return tens[iNum];
}

string hundreds_digit(unsigned int iNum) {
  map<int, string> hundreds;
  hundreds[1] = "einhundert";
  hundreds[2] = "zweihundert";
  hundreds[3] = "dreihundert";
  hundreds[4] = "vierhundert";
  hundreds[5] = "fuenfhundert";
  hundreds[6] = "sechshundert";
  hundreds[7] = "siebenhundert";
  hundreds[8] = "achthundert";
  hundreds[9] = "neunhundert";
  
  return hundreds[iNum];
}

string rule_1digit(vector<unsigned int> &number_vec) {
  string result;

  // Number = 1
  if (number_vec.back() == 1)
    result = single_digit(number_vec.back()) + "s";
  // Number = 2-9
  else
    result = single_digit(number_vec.back());
  
  return result;
}

string rule_2digit(vector<unsigned int> &number_vec) {
  string result;

  // Dozens: 10-19
  if (number_vec[0] == 1)
    cout << dozens_number(number_vec[1]);
    // Tens: 20, 30, ..., 90
  else if (number_vec[0] != 1 && number_vec[1] == 0)
    cout << tens_digit(number_vec[0]);
  // Tens with any successive number except 0
  else
    cout << single_digit(number_vec[1]) << "und" << tens_digit(number_vec[0]);
}

int main() {
    unsigned int iNum;
    cout << "Enter a number: ";
    cin >> iNum;
    vector<unsigned int> vNum;
    unsigned int iNumLen;
    number_parse(iNum, iNumLen, vNum, sNumVec);

    cout << "First hundreds:\n";
    for (auto x : sNumVec.first_hundreds)
        cout << x;
    cout << "\n";

    cout << "Second hundreds:\n";
    for (auto x : sNumVec.second_hundreds)
        cout << x;
    cout << "\n";

    cout << "Third hundreds:\n";
    for (auto x : sNumVec.third_hundreds)
        cout << x;
    cout << "\n";

    cout << "Fourth hundreds:\n";
    for (auto x : sNumVec.fourth_hundreds)
        cout << x;
    cout << "\n";
}