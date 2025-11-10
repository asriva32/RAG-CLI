#include <iostream>
#include "rag.h"
#include "utils/utils.h"
#include <sstream>
#include <memory>

constexpr int MAX_ELEMENTS = 10000;
constexpr int DIM = 768;
constexpr int M = 16;
constexpr int EF_CONSTRUCTION = 200;
const std::string EMBEDDING_MODEL = "nomic-embed-text";
const std::string LLM = "llama3.1";



int main() {
    Rag rag(DB(MAX_ELEMENTS, DIM, M, EF_CONSTRUCTION), LLMServer(LLM), EmbeddingServer(EMBEDDING_MODEL));

    while (true) {
        std::cout << "> ";

        std::string input;
        getline(std::cin, input);
        std::istringstream iss(input);

        std::vector<std::string> args;

        std::string arg;

        while(iss >> arg){
            args.push_back(arg);
        }

        if(args.empty())
            continue;

        std::string command = args.front();

        if(args[0] == "exit"){
            break;
        }

        handler(args, rag);

    }
    return 0;
}
