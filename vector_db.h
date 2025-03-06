#include "hnswlib/hnswlib.h"
#include <vector>
#include <string>
#ifndef RAG_CLI_VECTOR_DB_H
#define RAG_CLI_VECTOR_DB_H

class DB {
    hnswlib::L2Space space;
    hnswlib::HierarchicalNSW<float>* index;
    std::vector<std::string> documents;
    std::string hsnw_path;
public:
    DB(int max_elements, int dim, int M, int ef_construction): space(dim) {
        index = new hnswlib::HierarchicalNSW<float>(&space, max_elements, M, ef_construction);
        hsnw_path = "hsnw.bin";
    }
    std::vector<std::string> search(std::vector<float> prompt, int k);
    void add(std::string context, std::vector<float> embedding);
    void save();
    void load();

};



#endif //RAG_CLI_VECTOR_DB_H
