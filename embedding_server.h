#include <string>
#include <vector>

#ifndef RAG_CLI_EMBEDDING_SERVER_H
#define RAG_CLI_EMBEDDING_SERVER_H


class EmbeddingServer {
    std::string model;
public:
    EmbeddingServer(std::string model): model(std::move(model)){}
    std::vector<std::string> chunking(std::string &document);
    std::vector<float> generate(std::string &prompt);
};


#endif //RAG_CLI_EMBEDDING_SERVER_H
