#ifndef ASS3_HUFFMAN_H
#define ASS3_HUFFMAN_H


#include "PriorityHeap.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class Huffman {
public:
    explicit Huffman(std::string name);

    Huffman(const Huffman &other) = delete;

    Huffman &operator=(const Huffman &other) = delete;

    void compress(const std::string &arg);

    void decompress();

private:
    static const unsigned MAX = 512;
    unsigned m_Count [MAX];
    int m_Dad [MAX];
    unsigned m_Code [MAX/2];
    unsigned m_Len[MAX/2];
    int m_Left[MAX];
    int m_Right[MAX];
    unsigned m_Root = -1;
    const std::string filename;

    std::string decode(std::vector<bool> vec, char fillUpZeros);

    void binToString(const std::string &arg);

    static void modify(char &n, int p, int b);

    void setTree(std::fstream &out);

    void reproducedTree(std::fstream &in);

};


#endif //ASS3_HUFFMAN_H
