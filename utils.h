#ifndef RAG_CLI_UTILS_H
#define RAG_CLI_UTILS_H

#include <string>
#include "embedding_server.h"
#include "vector_db.h"
#include "llm_server.h"





void handler(std::string &command, std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls);
void help(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls);
void build_vdb(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls);
void ask(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls);

#endif //RAG_CLI_UTILS_H