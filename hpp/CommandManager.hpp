#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include "PasswordFile.hpp"
#include <string>
#include <vector>

class CommandManager 
{
public:
    // Parse command
    void parseAndExecute(const std::string& command);
    
    // Loop to enter commands
    void startInteractiveMode();

private:
    // Commands 
    void handleCreate(const std::vector<std::string>& args);
    void handleOpen(const std::vector<std::string>& args);
    void handleSave(const std::vector<std::string>& args);
    void handleLoad(const std::vector<std::string>& args);
    void handleUpdate(const std::vector<std::string>& args);
    void handleDelete(const std::vector<std::string>& args);
    void handleHelp(const std::vector<std::string>& args);
    void handleStatus(const std::vector<std::string>& args);

    bool confirmAndClose();

    // Utility methods
    std::vector<std::string> tokenize(const std::string& str);
    void printError(const std::string& message);
    void printInfo(const std::string& message);
};

#endif