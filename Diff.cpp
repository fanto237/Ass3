#include "Diff.h"

void Diff::compare(const std::vector<std::string> &v1, const std::vector<std::string> &v2) {
    std::vector<unsigned> compareVec = shortestPath(v1, v2);
    for (unsigned ui = 1; ui < compareVec.size(); ++ui) {
        if (compareVec[ui] == compareVec[ui - 1] + 1) {
            std::cout << "loesche - " <<
                      "Zeile: " << (compareVec[ui - 1] % (v1.size() + 1)) + 1 << " | "
                      << v1[(compareVec[ui - 1] % (v1.size() + 1))] << std::endl;
        }
        if (compareVec[ui] == compareVec[ui - 1] + (v1.size() + 1)) {
            std::cout << "Fuege - " <<
                      "Zeile: " << (compareVec[ui - 1] / (v1.size() + 1)) + 1 << " | "
                      << v2[(compareVec[ui - 1] / (v1.size() + 1))] << std::endl;
        }
    }
}


unsigned Diff::zeroClosure(int *visited, unsigned node, const std::vector<std::string> &vec1,
                           const std::vector<std::string> &vec2) {
    const unsigned N = vec1.size() + 1;
    const unsigned M = vec2.size() + 1;
    const unsigned END = N * M;
    while (node % N + 1 < N && node + N < END && vec1[node % N] == vec2[node / N] && (visited[node + N + 1]) == -1) {
        visited[node + N + 1] = node;
        node = node + N + 1;
    }
    return node;
}


std::vector<unsigned> Diff::shortestPath(const std::vector<std::string> &a, const std::vector<std::string> &b) {
    const unsigned N = a.size() + 1;
    const unsigned M = b.size() + 1;
    const unsigned END = N * M;

    std::list<unsigned> list;
    int *visited = new int[END];

    for (unsigned i = 0; i < END; ++i) {
        visited[i] = -1;
    }

    unsigned currentState = zeroClosure(visited, 0, a, b);
    if (currentState != END - 1) {
        list.push_back(currentState);
    }

    bool bLoop = true;
    while (bLoop && !list.empty()) {
        unsigned iNextNode = list.front();
        list.pop_front();
        if (iNextNode % N + 1 < N && visited[iNextNode + 1] == -1) {
            bLoop = (currentState = zeroClosure(visited, iNextNode + 1, a, b)) != END - 1;
            list.push_back(currentState);
            visited[iNextNode + 1] = iNextNode;
        }
        if (bLoop && iNextNode + N < END && visited[iNextNode + N] == -1) {
            bLoop = (currentState = zeroClosure(visited, iNextNode + N, a, b)) != END - 1;
            list.push_back(currentState);
            visited[iNextNode + N] = iNextNode;
        }
    }
    return genPath(visited, END - 1);
}


std::vector<unsigned> Diff::genPath(const int *visited, unsigned iEnd) {
    int cnt = 0;
    std::vector<unsigned> res;

    for (int node = iEnd; node >= 0; node = visited[node]) {
        res.push_back(0);
        ++cnt;
    }

    for (int node = iEnd; node >= 0; node = visited[node]) {
        res[--cnt] = node;
    }
    delete[] visited;
    return res;
}

