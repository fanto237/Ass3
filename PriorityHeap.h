#ifndef ASS3_PRIORITYHEAP_H
#define ASS3_PRIORITYHEAP_H


#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

class PriorityHeap {
public:

    // Constructor
    explicit PriorityHeap(unsigned uiNrOfNodes) : m_iNextFree(0), m_Keys(new float[uiNrOfNodes]),
                                                  m_Entries(new unsigned[uiNrOfNodes]) {}

    PriorityHeap(const PriorityHeap &other) = delete;

    PriorityHeap &operator=(const PriorityHeap &other) = delete;

    //Destructor
    ~PriorityHeap() {
        delete[] m_Entries;
        delete[] m_Keys;
    }

    // methods
    void insert(unsigned iNode, float key) {
        m_Keys[m_iNextFree] = key;
        m_Entries[m_iNextFree] = iNode;
        upHeap(m_iNextFree);
        ++m_iNextFree;
    }

    unsigned remove() {
        const unsigned NODE = m_Entries[0];
        m_Keys[0] = m_Keys[--m_iNextFree];
        m_Entries[0] = m_Entries[m_iNextFree];
        downHeap(0);
        return NODE;
    }

    bool empty() const {
        return m_iNextFree == 0;
    }

private:

    void upHeap(unsigned iIndex) {
        const float VAL = m_Keys[iIndex];
        const unsigned NODE = m_Entries[iIndex];
        unsigned iFather = (iIndex - 1) / 2;
        while (iIndex != 0 && m_Keys[iFather] > VAL) {
            m_Keys[iIndex] = m_Keys[iFather];
            m_Entries[iIndex] = m_Entries[iFather];
            iIndex = iFather;
            iFather = (iIndex - 1) / 2;
        }
        m_Keys[iIndex] = VAL;
        m_Entries[iIndex] = NODE;
    }

    void downHeap(unsigned iIndex) {
        const float KEY = m_Keys[iIndex];
        const unsigned NODE = m_Entries[iIndex];
        while (iIndex < m_iNextFree / 2) {
            unsigned iSon = 2 * iIndex + 1;
            if (iSon < m_iNextFree - 1 && m_Keys[iSon] > m_Keys[iSon + 1])
                ++iSon;
            if (KEY <= m_Keys[iSon])
                break;
            m_Keys[iIndex] = m_Keys[iSon];
            m_Entries[iIndex] = m_Entries[iSon];
            iIndex = iSon;
        }
        m_Keys[iIndex] = KEY;
        m_Entries[iIndex] = NODE;
    }

    // members

    unsigned m_iNextFree;
    float *m_Keys = nullptr;
    unsigned *m_Entries = nullptr;

};


#endif //ASS3_PRIORITYHEAP_H
