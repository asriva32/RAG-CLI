#ifndef RAG_H
#define RAG_H
#include "vector_db.h"
#include "llm_server.h"
#include "embedding_server.h"


class Rag{
    public:
        Rag(const DB &db, const LLMServer &ls, const EmbeddingServer &es);

        void build_vdb(std::vector<std::string> &args);
        void ask(std::vector<std::string> &args);
        // std::filesystem::path getPath();
        
        
    private:
        DB db;
        LLMServer ls;
        EmbeddingServer es;

};




#endif //RAG_H