#include "ollama.hpp"
#include "embedding_server.h"
#include <algorithm>

std::vector<std::string> EmbeddingServer::chunking(std::string &document){
    const int CHARACTER_LIMIT = 2000;
    std::vector<std::string> chunks;

    for(int i = 0; i < document.length();i += CHARACTER_LIMIT){
        chunks.push_back(document.substr(i, std::min(CHARACTER_LIMIT, (int)document.length() - i)));
    }

    return chunks;
}

std::vector<float> EmbeddingServer::generate(std::string &s){

    ollama::response response = ollama::generate_embeddings(model, s);
    return response.as_json()["embeddings"][0];
}