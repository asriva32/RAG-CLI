#include "vector_db.h"

std::vector<std::string> DB::search(std::vector<float> prompt, int k) {
    auto result = index->searchKnn(prompt.data(), k);
    std::vector<std::string> retrieved_docs;

    while (!result.empty()) {
        int doc_id = result.top().second;
        result.pop();
        retrieved_docs.push_back(documents[doc_id]);
    }

    return retrieved_docs;
}

void DB::add(std::string context, std::vector<float> embedding) {
    int doc_id = (int)documents.size();
    documents.push_back(context);
    index->addPoint(embedding.data(), doc_id);
}

void DB::save() { index->saveIndex(hsnw_path); }
void DB::load() { index->loadIndex(hsnw_path, &space); }

