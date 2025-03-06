#include "ollama.hpp"
#include "llm_server.h"

std::string LLMServer::ask(std::string &prompt) {
    ollama::response response = ollama::generate(model, prompt);
    return response.as_simple_string();
}
