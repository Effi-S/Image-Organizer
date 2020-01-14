#pragma once
#include <vector>
#include <string>

class AbstractImageFinder{
public:

    AbstractImageFinder() = default;
    virtual ~AbstractImageFinder() = default;
    virtual std::vector<std::vector<std::string>> show() =0;
    virtual void makeSet() =0;
};
