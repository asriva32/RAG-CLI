#ifndef RAG_CLI_UTILS_H
#define RAG_CLI_UTILS_H
#include <memory>
#include <string>
#include "../rag.h"



void handler(std::vector<std::string> &args, Rag &rag);
void help();
void build_vdb(std::vector<std::string> &args, Rag &rag);
void ask(std::vector<std::string> &args, Rag &rag);

#endif //RAG_CLI_UTILS_H