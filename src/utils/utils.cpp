#include "utils.h"
#include <unordered_map>
#include <functional>
#include <iostream>
#include <sstream>

void help(){
   std::cout << "Commands: \n exit: exit the program \n documents: \n \t [params] add the path of the documents "
                "you are asking questions about. \n ask: \n \t [params] the question you would like to ask." << std::endl;
}

void ask(std::vector<std::string> &args, Rag &rag){
    rag.ask(args);
}

void build_vdb(std::vector<std::string> &args, Rag &rag){
    rag.build_vdb(args);
}

void handler(std::vector<std::string> &args, Rag& rag){
    std::string command = args[0];
    args.erase(args.begin());
    if(command == "help"){
        help();
    }else if(command == "ask"){
        ask(args, rag);
    }else if(command == "documents"){
        build_vdb(args, rag);
    }else{
        std::cout << "Please enter a supported command, enter help for a list of valid commands" << std::endl;
    }
}