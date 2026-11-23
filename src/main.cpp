#include "TaskManager.h"

#include <iostream> 
#include <vector>
#include <sstream>
#include <unordered_map>


using namespace std;

vector<string> parseArgument(string input) { 
    if (input.empty()) return {};

    vector<string> arguments;
    vector<string> resultingArguments;
    istringstream inputStream(input);
    string command;

    while (inputStream >> command) { 
        arguments.push_back(command);
    }

    string id;
    string desc; 
    string listMode;

    resultingArguments.push_back(arguments[0]);
    if (arguments[0] == "add") { 
        for (int i = 1; i < arguments.size(); i++) { 
            desc += " "  + arguments[i];
        }
        //trim the leading whitespace
        desc.erase(0, 1);
        //push the description
        resultingArguments.push_back(desc);
    } else if (arguments[0] == "update") { 
        id = arguments[1];
        for (int i = 2; i < arguments.size(); i++) { 
            desc = " "  + arguments[i];
        }
        //delete the leading whitespace
        desc.erase(0, 1);
        resultingArguments.push_back(id);
        resultingArguments.push_back(desc);
    } else if (arguments[0] == "delete") { 
        id = arguments[1]; 
        resultingArguments.push_back(id); 
    } else if (arguments[0] == "mark-in-progress") { 
        id = arguments[1]; 
        resultingArguments.push_back(id);
    } else if (arguments[0] == "mark-done") { 
        id = arguments[1]; 
        resultingArguments.push_back(id);
    } else if (arguments[0] == "list") { 
        listMode = arguments[1];
        resultingArguments.push_back(listMode);
    }
    return resultingArguments;
}

int main() { 

    TaskManager manager ; 

    string userInput; 
    
    vector<string> args;
    string arg;

    getline(cin, userInput); 

    for (int i = 0; i < args.size(); i++) { 
        cout << args[i] << endl; 
    }

    if (args.size() > 3 || args.size() == 0) { 
        cout << "Error: Invalid Arguments" << endl;
        return EXIT_FAILURE;
    }

    if (args[0] == "add") { 
        manager.createTask(args[1]);
    } else if (args[0] == "update") { 
        //call update func
    } else if (args[0] == "delete") { 
        //call delete func 
    } else if (args[0] == "mark-in-progress") { 
        //call mark in progress func
    } else if (args[0] == "mark-done") { 
        //call mark done func 
    } else if (args[0] == "list") { 
        if (args[1] == "done") { 
            //list done
        } else if (args[1] == "todo") { 
            //list todo
        } else if (args[1] == "in-progress") { 
            //list in progress
        } else { 
            //list all tasks
        }
    } else if (args[0] == "exit") { 
        //invalid arg name 
        return EXIT_SUCCESS;
    } else { 
        return EXIT_FAILURE;
    }
}