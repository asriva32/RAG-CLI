#include "vector_db.h"

DB::DB(int max_elements, int dim, int M, int ef_construction): space(dim), hsnw_path("hnsw.bin") {
        index = new hnswlib::HierarchicalNSW<float>(&space, max_elements, M, ef_construction);
}

DB::~DB(){
    delete index;
}

std::vector<std::string> DB::search(float* prompt, int k) {
    auto result = index->searchKnn(prompt, k);
    std::vector<std::string> retrieved_docs;

    while (!result.empty()) {
        int doc_id = result.top().second;
        result.pop();
        retrieved_docs.push_back(documents[doc_id]);
    }

    return retrieved_docs;
}

void DB::add(const std::string &context, float* embedding) {
    int doc_id = (int)documents.size();
    documents.push_back(context);
    index->addPoint(embedding, doc_id);
}

void DB::save() { index->saveIndex(hsnw_path); }
void DB::load() { index->loadIndex(hsnw_path, &space); }

