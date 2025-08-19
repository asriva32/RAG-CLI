#include <iostream>
#include "ollama.hpp"
#include "vector_db.h"
#include "llm_server.h"
#include "embedding_server.h"
#include "utils.h"



int main() {
    int max_elements = 10000;
    int dim = 768;
    int M = 16;
    int ef_construction = 200;
    DB vdb(max_elements, dim, M, ef_construction);
    EmbeddingServer es("nomic-embed-text");
    LLMServer ls("llama3.1");

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
        args.erase(args.begin());

        if(command == "exit"){
            break;
        }

        handler(command, args, vdb, es, ls);

    }
    std::remove("hsnw.bin");
    return 0;
}
