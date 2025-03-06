cmake_minimum_required(VERSION 3.26)
project(RAG_CLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(RAG_CLI main.cpp
        utils.cpp
        vector_db.cpp
        embedding_server.cpp
        llm_server.cpp
)