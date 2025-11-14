#include <iostream>
#include <ranges>
#include <print>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <regex>

std::string get_path(int dst)
{
    if (dst == 0)
        return "0 0";

    if (std::abs(dst) < 10)
    {
        switch (dst)
        {
        case 1:
            return "0 5 0";
        case 2:
            return "0 5 5 0";
        case 3:
            return "0 5 4 5 0";
        case 4:
            return "0 5 4 5 5 0";
        case 5:
            return "0 5 4 3 4 5 0";
        case 6:
            return "0 5 4 3 3 4 5 0";
        case 7:
            return "0 5 4 3 2 3 4 5 0";
        case 8:
            return "0 5 4 3 2 2 3 4 5 0";
        case 9:
            return "0 5 4 3 2 1 2 3 4 5 0";
        case -1:
            return "0 -5 0";
        case -2:
            return "0 -5 -5 0";
        case -3:
            return "0 -5 -4 -5 0";
        case -4:
            return "0 -5 -4 -5 -5 0";
        case -5:
            return "0 -5 -4 -3 -4 -5 0";
        case -6:
            return "0 -5 -4 -3 -3 -4 -5 0";
        case -7:
            return "0 -5 -4 -3 -2 -3 -4 -5 0";
        case -8:
            return "0 -5 -4 -3 -2 -2 -3 -4 -5 0";
        case -9:
            return "0 -5 -4 -3 -2 -1 -2 -3 -4 -5 0";
        }
    }

    std::string result;
    if (dst > 0)
    {
        result = "0 5 4 3 2 ";
        for (auto i = 0; i < (dst - 8); ++i)
        {
            result.append("1 ");
        }
        result.append("2 3 4 5 0");
    }
    else
    {
        result = "0 -5 -4 -3 -2 ";
        for (auto i = 0; i < (std::abs(dst) - 8); ++i)
        {
            result.append("-1 ");
        }
        result.append("-2 -3 -4 -5 0");
    }
    return result;
}

int main()
{
    std::ifstream in{"/Users/elvisdukaj/Projects/content/assets/level4_2_large.in"};
    std::string str;
    std::getline(in, str);

    while (std::getline(in, str))
    {
        std::replace_if(begin(str), end(str), [](char c) { return c == ','; }, ' ');
        int x_dst, y_dst, time;
        std::stringstream ss{str};
        ss >> x_dst >> y_dst >> time;

        std::cout << get_path(x_dst) << "\n" << get_path(y_dst) << "\n" << std::endl;
    }
}
