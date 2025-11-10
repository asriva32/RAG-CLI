#include <string>
#include <vector>

#ifndef RAG_CLI_EMBEDDING_SERVER_H
#define RAG_CLI_EMBEDDING_SERVER_H


class EmbeddingServer {
    public:
        EmbeddingServer(std::string model): model(std::move(model)){}
        std::vector<std::string> chunking(const std::string &document);
        std::vector<float> generate(const std::string &prompt);
    private:
        std::string model;
        const int CHARACTER_LIMIT = 2000;
};


#endif //RAG_CLI_EMBEDDING_SERVER_H
