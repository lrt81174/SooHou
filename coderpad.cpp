#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct sVector {
    std::vector<unsigned int> first_hundreds;
    std::vector<unsigned int> second_hundreds;
    std::vector<unsigned int> third_hundreds;
    std::vector<unsigned int> fourth_hundreds;
} sNumVec;

unsigned int number_parse(unsigned int iNum, std::vector<unsigned int>& vNum, sVector& srNumVec) {
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

    unsigned int iNumLen = vNum.size();

    static int i = 0;
    while (i < 3)
    {
        if (i == iNumLen)
            break;
        srNumVec.first_hundreds.push_back(vNum[i]);
        ++i;
    }
    reverse(srNumVec.first_hundreds.begin(), srNumVec.first_hundreds.end());

    while ((i > 2) && (i < 6))
    {
        if (i == iNumLen)
            break;
        srNumVec.second_hundreds.push_back(vNum[i]);
        ++i;
    }
    reverse(srNumVec.second_hundreds.begin(), srNumVec.second_hundreds.end());

    while ((i > 5) && (i < 9))
    {
        if (i == iNumLen)
            break;
        srNumVec.third_hundreds.push_back(vNum[i]);
        ++i;
    }
    reverse(srNumVec.third_hundreds.begin(), srNumVec.third_hundreds.end());

    while ((i > 8) && (i < 12))
    {
        if (i == iNumLen)
            break;
        srNumVec.fourth_hundreds.push_back(vNum[i]);
        ++i;
    }
    reverse(srNumVec.fourth_hundreds.begin(), srNumVec.fourth_hundreds.end());

    return iNumLen;
}

std::string single_digit(unsigned int iNum) {
    std::map<int, std::string> single;
    //single[0] = "null";
    single[1] = "ein";
    single[2] = "zwei";
    single[3] = "drei";
    single[4] = "vier";
    single[5] = "fünf";
    single[6] = "sechs";
    single[7] = "sieben";
    single[8] = "acht";
    single[9] = "neun";

    return single[iNum];
}

std::string dozens_number(unsigned int iNum) {
    std::map<int, std::string> dozens;
    dozens[0] = "zehn";
    dozens[1] = "elf";
    dozens[2] = "zwölf";
    dozens[3] = "dreizehn";
    dozens[4] = "vierzehn";
    dozens[5] = "fünfzehn";
    dozens[6] = "sechzehn";
    dozens[7] = "siebzehn";
    dozens[8] = "achtzehn";
    dozens[9] = "neunzehn";

    return dozens[iNum];
}

std::string tens_digit(unsigned int iNum) {
    std::map<int, std::string> tens;
    tens[2] = "zwanzig";
    tens[3] = "dreißig";
    tens[4] = "vierzig";
    tens[5] = "füfzig";
    tens[6] = "sechzig";
    tens[7] = "siebzig";
    tens[8] = "achtzig";
    tens[9] = "neunzig";

    return tens[iNum];
}

std::string hundreds_digit(unsigned int iNum) {
    std::map<int, std::string> hundreds;
    hundreds[1] = "einhundert";
    hundreds[2] = "zweihundert";
    hundreds[3] = "dreihundert";
    hundreds[4] = "vierhundert";
    hundreds[5] = "fünfhundert";
    hundreds[6] = "sechshundert";
    hundreds[7] = "siebenhundert";
    hundreds[8] = "achthundert";
    hundreds[9] = "neunhundert";

    return hundreds[iNum];
}

std::string rule_1digit(std::vector<unsigned int>& svNumVec) {
    std::string sResult;

    // Number = 1
    if (svNumVec.back() == 1)
        sResult = single_digit(svNumVec.back()) + "s";
    // Number = 2-9
    else
        sResult = single_digit(svNumVec.back());

    return sResult;
}

std::string rule_2digit(std::vector<unsigned int>& svNumVec) {
    std::string sResult;
    unsigned int iNumVecLen = svNumVec.size();

    // 
    if (iNumVecLen == 2)
    {
        // Dozens: 10-19
        if (svNumVec[0] == 1)
            sResult = dozens_number(svNumVec[1]);
        // Tens: 20, 30, ..., 90
        else if (svNumVec[0] != 1 && svNumVec[1] == 0)
            sResult = tens_digit(svNumVec.front());
        // Tens with any successive number except 0
        else
            sResult = single_digit(svNumVec[1]) + "und" + tens_digit(svNumVec[0]);
    }
    // If it is in 3 digits number
    else if (iNumVecLen == 3)
    {
        // Dozens: 10-19
        if (svNumVec[1] == 1)
            sResult = dozens_number(svNumVec[2]);
        // Tens: 20, 30, ..., 90
        else if (svNumVec[1] != 1 && svNumVec[2] == 0)
            sResult = tens_digit(svNumVec[1]);
        // Tens with any successive number except 0
        else
            sResult = single_digit(svNumVec[2]) + "und" + tens_digit(svNumVec[1]);
    }

    return sResult;
}

std::string rule_3digit(std::vector<unsigned int>& svNumVec) {
    std::string sResult;

    // x0x -> x=1-9
    if (svNumVec[1] == 0)
    {
        // x00
        if (svNumVec[2] == 0)
            sResult = hundreds_digit(svNumVec[0]);
        // x0x
        else
            sResult = hundreds_digit(svNumVec[0]) + rule_1digit(svNumVec);
    }
    // xxy -> y=0-9
    else
    {
        sResult = hundreds_digit(svNumVec[0]) + rule_2digit(svNumVec);
    }

    return sResult;
}

std::string rule_embedded(std::vector<unsigned int>& svNumVec) {
    std::string sResult;
    unsigned int iNumVecLen = svNumVec.size();
    switch (iNumVecLen)
    {
    case 1:
        sResult = rule_1digit(svNumVec);
        break;
    case 2:
        sResult = rule_2digit(svNumVec);
        break;
    case 3:
        sResult = rule_3digit(svNumVec);
        break;
    };

    return sResult;
}

std::string rule_thousand(sVector& srNumVec) {
    std::string sResult;
    bool bZeros3 = std::all_of(srNumVec.second_hundreds.begin(), srNumVec.second_hundreds.end(), [](int i) { return i == 0; });
    bool bZeros2 = std::all_of(srNumVec.second_hundreds.begin(), srNumVec.second_hundreds.end() - 1, [](int i) { return i == 0; });

    // for x Million 000 yyy
    if (bZeros3)
        sResult = rule_embedded(srNumVec.first_hundreds);
    // for x Million 001 yyy
    else if ((bZeros2) && (srNumVec.second_hundreds[2] == 1))
        sResult = single_digit(1) + "tausend" + rule_embedded(srNumVec.first_hundreds);
    // x01 yyy
    else if ((srNumVec.second_hundreds[1] == 0) && (srNumVec.second_hundreds[2] == 1))
        sResult = hundreds_digit((srNumVec.second_hundreds[0])) + single_digit(1) + "tausend" + rule_embedded(srNumVec.first_hundreds);
    // xx(2-9) yyy
    else
        sResult = rule_embedded(srNumVec.second_hundreds) + "tausend" + rule_embedded(srNumVec.first_hundreds);

    return sResult;
}

std::string rule_million(sVector& srNumVec) {
    std::string sResult;
    bool bZeros3 = std::all_of(srNumVec.third_hundreds.begin(), srNumVec.third_hundreds.end(), [](int i) { return i == 0; });
    bool bZeros2 = std::all_of(srNumVec.third_hundreds.begin(), srNumVec.third_hundreds.end() - 1, [](int i) { return i == 0; });
    unsigned int iNumVecLen = srNumVec.third_hundreds.size();

    // for x Billion 000 yyy yyy
    if (bZeros3)
        sResult = rule_thousand(srNumVec);// +rule_embedded(srNumVec.first_hundreds);
    // for x Billion 001 yyy yyy
    //else if ((bZeros2) && (srNumVec.third_hundreds[2] == 1))
        //sResult = single_digit(1) + " Million " + rule_thousand(srNumVec);
    else if ((iNumVecLen == 1) && (srNumVec.third_hundreds[0] == 1))
        sResult = "eine Million " + rule_thousand(srNumVec);
    else
        sResult = rule_embedded(srNumVec.third_hundreds) + " Millionen " + rule_thousand(srNumVec);

    return sResult;
}

std::string rule_billion(sVector& srNumVec) {
    std::string sResult;
    unsigned int iNumVecLen = srNumVec.fourth_hundreds.size();
    bool bZeros2 = std::all_of(srNumVec.third_hundreds.begin(), srNumVec.third_hundreds.end() - 1, [](int i) { return i == 0; });

    // 1 yyy yyy yyy
    if ((iNumVecLen == 1) && (srNumVec.fourth_hundreds[0] == 1))
    {
        sResult = "eine Milliarde " + rule_million(srNumVec);
        if ((bZeros2) && (srNumVec.third_hundreds[2] == 1))
            sResult = "eine Milliarde eine Million " + rule_thousand(srNumVec);
    }
    else
    {
        sResult = rule_embedded(srNumVec.fourth_hundreds) + " Milliarden " + rule_million(srNumVec);
        if ((bZeros2) && (srNumVec.third_hundreds[2] == 1))
            sResult = rule_embedded(srNumVec.fourth_hundreds) + " Milliarden eine Million " + rule_thousand(srNumVec);
    }

    return sResult;
}

std::string solution(unsigned int iNum) {
    // Please write your code here.
    string sResult;
    std::vector<unsigned int> vNum;
    unsigned int iNumLen = number_parse(iNum, vNum, sNumVec);

    if ((iNumLen >= 1) && (iNumLen <= 3))
        sResult = rule_embedded(sNumVec.first_hundreds);
    else if ((iNumLen >= 4) && (iNumLen <= 6))
        sResult = rule_thousand(sNumVec);
    else if ((iNumLen >= 7) && (iNumLen <= 9))
        sResult = rule_million(sNumVec);
    else if ((iNumLen >= 10) && (iNumLen <= 12))
        sResult = rule_billion(sNumVec);

    return sResult;
}

int main() {
    unsigned int number;

    std::cout << "Enter a number: ";
    std::cin >> number;

    std::cout << solution(number);
    
    return 0;
}