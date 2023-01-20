#include <iostream>
#include "Huffman.h"
#include "Diff.h"


std::vector<std::string> extractLines(std::ifstream &is, std::string &str) {
    std::vector<std::string> vector;
    while (!is.eof()) {
        std::getline(is, str);
        vector.push_back(str);
    }
    return vector;
}

void decompress(const std::string &filename) {
    std::string name = filename;
    name.erase(filename.length() - 4, filename.length());
    std::ifstream file(name);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    Huffman huffman(name);

    huffman.decompress();
    std::cout << "Die dekomprimierte Datei " << name << ".output wurde generiert" << std::endl;
}


void compressAndDecompress(const std::string &filename) {
    std::ifstream file(filename);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    Huffman huffman(filename);

    huffman.compress(str);
    std::cout << "Das komprimierte Datei " << filename << ".bin wurde generiert" << std::endl;

    huffman.decompress();
    std::cout << "Das dekomprimierte Datei " << filename << ".output wurde generiert" << std::endl;
}

void compressAndCompare(const std::string &filename1, const std::string &filename2) {
    decompress(filename1);

    std::string name = filename1;
    name.erase(filename1.length() - 4, filename1.length());
    std::ifstream is(name + ".output");
    std::string str;
    auto vector1 = extractLines(is, str);

    decompress(filename2);
    name = filename2;
    name.erase(filename2.length() - 4, filename2.length());
    std::ifstream is2(name + ".output");
    std::string str2;
    auto vector2 = extractLines(is2, str2);

    Diff::compare(vector1, vector2);
}


int main(int argc, char **argv) {

    switch (argc) {
        case 2:
            if (((std::string) argv[1]).find(".bin") != std::string::npos)
                decompress(argv[1]);
            else
                compressAndDecompress(argv[1]);
            break;
        case 3:
            compressAndCompare(argv[1], argv[2]);
            break;
        default:
            std::cout
                    << "Geben sie bitte eine Datei als argument ein, wenn sie es komprimieren bzw. dekomprimieren wollen \n"
                    << "Oder 2 Dateien als Argument, wenn Sie die komprimieren wollen und ạnschliessend mit Hilfe von Diff vergleichen"
                    << std::endl;
            break;
    }

    return 0;
}
