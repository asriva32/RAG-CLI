#include "rag.h"
#include <sstream>

Rag::Rag(const DB &db, const LLMServer &ls, const EmbeddingServer &es): db(db), ls(ls), es(es){}

void Rag::build_vdb(std::vector<std::string> &args){
    // args contain path of each doc
    // convert from pdf to txt
    for(const std::string &filename: args){
        std::ifstream input(filename);
        if(!input.is_open()){
            std::cout << "Please make sure you have the correct path!" << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << input.rdbuf();
        std::string content = buffer.str();

        input.close();

        std::vector<std::string> chunks = es.chunking(content);
        for(const std::string &s: chunks){
            db.add(s, es.generate(s).data());
        }
    }
    db.save();
}

void Rag::ask(std::vector<std::string> &args){
    std::string prompt;
    for(const std::string &arg: args){
        prompt += arg + " ";
    }
    prompt.pop_back();

    std::vector<std::string> retrieved_docs = db.search(es.generate(prompt).data(), 10);

    if(retrieved_docs.empty()){
        std::cout << "Please add some documents!\n";
        return;
    }

    std::string new_prompt = "Context: ";

    for(const std::string &s: retrieved_docs){
        new_prompt += s + " ";
    }

    new_prompt += '\n';
    new_prompt += "Question: " + prompt;
    new_prompt += "\n Please rephrase the question asked above based on the context given while retaining the original intent.";

    std::string rephrased_prompt = ls.ask(new_prompt);

    retrieved_docs = db.search(es.generate(rephrased_prompt).data(), 5);

    std::string final_prompt = "Context: ";

    for(const std::string &s: retrieved_docs){
        final_prompt += s + " ";
    }
    final_prompt += '\n';
    final_prompt += "Question: " + rephrased_prompt;

    std::cout << ls.ask(final_prompt) << std::endl;
}