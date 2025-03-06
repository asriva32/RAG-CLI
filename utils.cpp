#include "utils.h"
#include <unordered_map>
#include <functional>
#include <iostream>
#include <sstream>



std::unordered_map<std::string, std::function<void(std::vector<std::string>&, DB &, EmbeddingServer &, LLMServer &)>> funcs = {
        {"help", help},
        {"documents", build_vdb},
        {"ask", ask}
};


void help(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls){
   std::cout << "Commands: \n exit: exit the program \n documents: \n \t [params] add the path of the documents "
                "you are asking questions about. \n ask: \n \t [params] the question you would like to ask." << std::endl;
}

void ask(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls){
    std::string prompt;
    for(const std::string &arg: args){
        prompt += arg + " ";
    }
    prompt.pop_back();
    std::cout << prompt << '\n';
    std::vector<float> embedding = es.generate(prompt);

    std::vector<std::string> retrieved_docs = vdb.search(embedding, 5);

    if(retrieved_docs.empty()){
        std::cout << "Please add some documents!\n";
        return;
    }

    std::string new_prompt = "Context: ";
    // TODO: maybe implement some sort of auto punctuation to improve queries
    // TODO: look at prompt building techniques
    for(const std::string &s: retrieved_docs){
        new_prompt += s + " ";
    }
    new_prompt += '\n';
    new_prompt += "Question: " + prompt;

    std::cout << new_prompt << '\n';

    std::cout << ls.ask(new_prompt) << std::endl;

}

void build_vdb(std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls){
    // args contain path of each doc
    // convert from pdf to txt
    for(const std::string &filename: args){
        std::ifstream input(filename);
        if(!input.is_open()){
            std::cerr << "Please make sure you have the correct path!" << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << input.rdbuf();
        std::string content = buffer.str();

        input.close();

        std::vector<std::string> chunks = es.chunking(content);
        for(std::string s: chunks){

            std::vector<float> embedding = es.generate(s);
            vdb.add(s, embedding);
        }
    }
    vdb.save();
}



void handler(std::string &command, std::vector<std::string> &args, DB &vdb, EmbeddingServer &es, LLMServer &ls){
    if(funcs.find(command) != funcs.end()){
        funcs[command](args, vdb, es, ls);
    } else {
        std::cout << "Please enter a supported command, enter help for a list" << std::endl;
    }
}