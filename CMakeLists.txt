cmake_minimum_required(VERSION 3.26)
project(RAG_CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(RAG_CLI src/main.cpp
        src/utils/utils.cpp
        src/vector_db.cpp
        src/embedding_server.cpp
        src/llm_server.cpp
        src/rag.cpp
)