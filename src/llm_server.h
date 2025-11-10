#include <string>

#ifndef RAG_CLI_LLM_SERVER_H
#define RAG_CLI_LLM_SERVER_H


class LLMServer {
    std::string model;

public:
    LLMServer(std::string model): model(std::move(model)){}
    std::string ask(const std::string &prompt);
};


#endif //RAG_CLI_LLM_SERVER_H
