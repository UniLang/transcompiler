#include <iostream>
#include "code/programs/repo_tools/bazel_grpc_log_reader/task_executer.hpp"
#include "code/programs/repo_tools/bazel_grpc_log_reader/program_options/program_options.hpp"


int main(int const argc, char** const argv){
    
    Program_Options program_options(argc, argv);
    Task_Executer::Execute_Needed_Tasks(program_options);
}

