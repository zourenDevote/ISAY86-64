//
// Created by 20580 on 2022/10/18.
//

#include "util.h"
#include "../base.h"

#include <cstring>
#include <cmath>
#include <map>

using namespace std;

bool endsWith(const std::string& str, const std::string& v) {
    if(str.length() < v.length())
        return false;
    int i = int(str.length()) - 1, j = int(v.length()) - 1;
    for(;j >= 0;) {
        if(str[i--] != v[j--])
            return false;
    }
    return true;
}

vector<string> split(const string& str, char c)
{
    vector<string> splList;
    string temp = "";
    for(const auto& ch : str)
    {
        if(ch == c){
            if(temp != ""){
                splList.push_back(temp);
            }
            temp = "";
            continue;
        }
        else{
            temp.push_back(ch);
        }
    }
    if(temp != "")
        splList.push_back(temp);
    return splList;
}

void replace(string& str, char src, char dst){
    for(auto& ch : str)
    {
        if(ch == src){
            ch = dst;
        }
    }
}

const std::map<char, Quad> digMap = {
        {'0', 0},{'1', 1},{'2', 2},{'3', 3},{'4', 4},
        {'5', 5},{'6', 6},{'7', 7},{'8', 8},{'9', 9},
};

const std::map<char, Quad> expandHexDigMap = {
        {'a', 10},{'b', 11},{'c', 12},{'d', 13},{'e', 14},{'f', 15},
        {'A', 10},{'B', 11},{'C', 12},{'D', 13},{'E', 14},{'F', 15}
};

ErrorOrSuccess strToInt(const std::string& number) {

    if(strcmp(number.c_str(), "") == 0){
        return {ERROR_CODE, (Quad)ERROR_CODE};
    }
    else{
        bool isHex = false;
        if(number.size() >= 3 && number[0] == '0' && (number[1] == 'x' || number[1] == 'X')) {isHex = true;}
        Quad v = 0, numbit = 0;
        int index;
        if(isHex) {
            for(numbit = 0, index = number.length() - 1 ; index > 1 ; index--, numbit++) {
                auto it = digMap.find(number[index]);
                if(it == digMap.end()) {
                    it = expandHexDigMap.find(number[index]);
                    if(it == digMap.end())
                        return {ERROR_CODE, (Quad)ERROR_CODE};
                    v += it->second * (Quad)std::pow(16, numbit);
                }
                else{
                    v += it->second * (Quad)std::pow(16, numbit);
                }
            }
        }
        else {
            for(numbit = 0, index = number.size() - 1 ; index >= 0 ; index--, numbit++) {
                auto it = digMap.find(number[index]);
                if(it == digMap.end()) {
                    return {ERROR_CODE, (Quad)ERROR_CODE};
                }
                v += it->second * (Quad)std::pow(10, numbit);
            }
        }
        return {SUCCESS_CODE, v};
    }
}
