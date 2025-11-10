#ifndef RAG_CLI_VECTOR_DB_H
#define RAG_CLI_VECTOR_DB_H
#include "../third_party/hnswlib/hnswlib.h"
#include <vector>
#include <string>
#include <filesystem>


class DB {
    hnswlib::L2Space space;
    hnswlib::HierarchicalNSW<float>* index;
    std::vector<std::string> documents;
    std::filesystem::path hsnw_path;
public:
    DB(int max_elements, int dim, int M, int ef_construction);

    ~DB();

    std::vector<std::string> search(float* prompt, int k);
    void add(const std::string &context, float* embedding);
    void save();
    void load();

};



#endif //RAG_CLI_VECTOR_DB_H
