#include "TaskManager.h"

#include <iostream> 
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

vector<string> parseArguments(string input, vector<string>& resultingArguments) { 
    if (input.empty()) return {};

    vector<string> arguments;
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
    TaskManager manager; 
    string userInput;
    vector<string> args;


    // TODO implement console menu and handle argument checking for each case
    while (true) { 
        getline(cin, userInput);
        parseArguments(userInput, args);
        if (args[0] == "add") { 
            if (args.size() > 3) { 
                cerr << "Incorrect command" << endl;
                break;
            }
            manager.createTask(args[1]);
        } else if (args[0] == "delete") { 
            if (args.size() > 2) { 
                cerr << "Incorrect command" << endl;
                break;
            }
            manager.deleteTask(stoi(args[1]));
        } else if (args[0] == "update") { 
            if (args.size() > 3) { 
                cerr << "Incorrect command" << endl;
            }
        }
    }







    if (args[0] == "add") { 
        
        manager.createTask(args[1]);
    } else if (args[0] == "update") { 
        
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