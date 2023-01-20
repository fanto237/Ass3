#ifndef ASS3_DIFF_H
#define ASS3_DIFF_H


#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>

class Diff{
public:
    static void compare(const std::vector<std::string>&v1, const std::vector<std::string>& v2);

private:
    static std::vector<unsigned> shortestPath(const std::vector<std::string>& a, const std::vector<std::string>& b);
    static unsigned zeroClosure(int* visited, unsigned node, const std::vector<std::string>& vec1, const std::vector<std::string>& vec2);
    static std::vector<unsigned> genPath(const int* visited, unsigned iEND);
};

#endif //ASS3_DIFF_H
