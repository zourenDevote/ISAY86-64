//
// Created by 20580 on 2022/10/18.
//

#ifndef Y8664_UTIL_H
#define Y8664_UTIL_H

#include <vector>
#include <string>
#include "../error/error.h"

/// 判断字符串是否以xxx结尾
bool endsWith(const std::string& str, const std::string& v);

/// 将字符串以某个字符位边界拆分出来成为一个新的字串列表
std::vector<std::string> split(const std::string& str, char c);

/// 将字符串中的某个字符替换为目标字符
void replace(std::string& str, char src, char dst);

/// 将字符串转换为整数
ErrorOrSuccess strToInt(const std::string& number);

#endif //Y8664_UTIL_H
