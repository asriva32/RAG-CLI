#include "../third_party/ollama.hpp"
#include "llm_server.h"

std::string LLMServer::ask(const std::string &prompt) {
    ollama::response response = ollama::generate(model, prompt);
    return response.as_simple_string();
}
