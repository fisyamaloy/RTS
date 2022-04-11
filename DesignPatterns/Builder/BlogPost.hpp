#pragma once
#include <string>
#include <vector>

struct BlogPost
{
    std::string              title;
    std::string              body;
    std::vector<std::string> tags;
    std::vector<std::string> categories;
};
