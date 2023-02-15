#include "Huffman.h"

#include <utility>

Huffman::Huffman(std::string name) : filename(std::move(name)) {
    for (unsigned i = 0; i < MAX; ++i) {
        m_Left[i] = m_Right[i] = m_Dad[i] = -1;
    }
}

std::string Huffman::decode(std::vector<bool> vec, char fillUpZeros) {
    std::string result;
    for (unsigned ui = 0; ui < vec.size() - fillUpZeros;) {
        unsigned node = m_Root;

        while (m_Left[node] != -1) {
            node = vec[ui++] ? m_Right[node] : m_Left[node];
        }
        result.push_back((char) node);
    }
    return result;
}

void Huffman::compress(const std::string &arg) {
    for (unsigned i = 0; i < MAX; ++i) {
        m_Count[i] = 0;
    }
    for (char i: arg)
        ++m_Count[(unsigned char) i];

    PriorityHeap ph(MAX / 2);
    for (unsigned i = 0; i < MAX / 2; ++i)
        if (m_Count[i] > 0)
            ph.insert(i, (float) m_Count[i]);

    for (int i = MAX / 2; !ph.empty(); ++i) {
        auto s1 = ph.remove();
        auto s2 = ph.remove();
        m_Dad[i] = 0;
        m_Dad[s1] = i;
        m_Dad[s2] = -i;
        m_Left[i] = (int) s1;
        m_Right[i] = (int) s2;
        m_Count[i] = m_Count[s1] + m_Count[s2];
        if (!ph.empty())
            ph.insert(i, (float) m_Count[i]);
        else
            m_Root = i;
    }

    for (unsigned ui = 0; ui < MAX / 2; ++ui) {
        unsigned len = 0;
        unsigned code = 0;
        if (m_Count[ui] > 0) {
            for (int t = m_Dad[ui]; t != 0; t = m_Dad[t], ++len)
                if (t < 0) {
                    code += 1 << len;
                    t = -t;
                }
        }
        m_Code[ui] = code;
        m_Len[ui] = len;
    }
    binToString(arg);
}


void Huffman::binToString(const std::string &arg) {
    auto out = std::fstream(filename + ".bin", std::ios::out | std::ios::binary);
    setTree(out);
    std::vector<bool> vector;
    for (char c: arg) {
        unsigned code = m_Code[(unsigned char) c];
        unsigned len = m_Len[(unsigned char) c];
        for (unsigned ui = 0; ui < len; ++ui) {
            vector.push_back(((code >> (len - ui - 1)) & 1) == 1);
        }
    }
    unsigned counter = 0;
    while (vector.size() % 8 != 0) {
        vector.push_back(0);
        ++counter;
    }
    unsigned bit = 0;
    char c;
    out.write(reinterpret_cast<const char *>(&counter), sizeof(char));
    for (auto &&ui: vector) {
        change(c, 7 - bit, ui);
        ++bit;
        if (bit > 0 && bit % 8 == 0) {
            bit = 0;
            out.write(reinterpret_cast<const char *>(&c), sizeof(char));
        }
    }
    out.close();
}


void Huffman::setTree(std::fstream &out) {
    char *c = reinterpret_cast<char *>(&m_Root);
    out.write(c, sizeof(short));
    for (unsigned ui = 0; ui < m_Root; ++ui) {
        if (m_Count[ui]) {
            c = reinterpret_cast<char *>(&ui);
            out.write(c, sizeof(short));
            c = reinterpret_cast<char *>(&m_Dad[ui]);
            out.write(c, sizeof(short));
        }
    }
    c = reinterpret_cast<char *>(&m_Dad[m_Root]);
    out.write(c, sizeof(short));
}


void Huffman::decompress() {
    std::fstream file(filename + ".bin", std::fstream::in | std::fstream::out | std::fstream::binary);

    genTree(file);
    char c;
    char fillUpZeros = 0;
    file.read(reinterpret_cast<char *>(&fillUpZeros), sizeof(char));
    std::vector<bool> vector;

    while (file.read(reinterpret_cast<char *>(&c), sizeof(char)) && !file.eof()) {
        for (int i = 7; i >= 0; --i) {
            vector.push_back((c >> i) & 1);
        }
    }

    std::ofstream outp;
    outp.open(filename + ".output");
    outp << decode(vector, fillUpZeros);
    outp.close();
}

void Huffman::genTree(std::fstream &in) {
    char c[sizeof(short)];
    in.read(c, sizeof(short));
    unsigned iDx = 1;
    short s = *(reinterpret_cast<short *>(c));
    m_Root = s;
    while (iDx) {
        in.read(c, sizeof(short));
        iDx = *(reinterpret_cast<short *>(c));
        if (!iDx)
            return;
        in.read(c, sizeof(short));
        s = *(reinterpret_cast<short *>(c));
        if (s > 0)
            m_Left[(int) s] = iDx;
        else if (s < 0)
            m_Right[(int) -s] = iDx;
    }
}


void Huffman::change(char &n, int p, int b) {
    int mask = 1 << p;
    n = (n & ~mask) | (b << p);
}



