#include "CommandManager.hpp"

void CommandManager::parseAndExecute(const std::string& command) 
{
    if (command.empty()) return;
    
    std::vector<std::string> tokens = tokenize(command);
    if (tokens.empty()) return;
    
    std::string cmd = tokens[0];
    
    try 
    {
        if (cmd == "create") 
        {
            handleCreate(tokens);
        } 
        else if (cmd == "open") 
        {
            handleOpen(tokens);
        } 
        else if (cmd == "save") 
        {
            handleSave(tokens);
        } 
        else if (cmd == "load") 
        {
            handleLoad(tokens);
        } 
        else if (cmd == "update") 
        {
            handleUpdate(tokens);
        } 
        else if (cmd == "delete") 
        {
            handleDelete(tokens);
        }
        else if (cmd == "help" || cmd == "h") 
        {
            handleHelp(tokens);
        } 
        else if (cmd == "status") 
        {
            handleStatus(tokens);
        }
        else 
        {
            printError("Unknown command: " + cmd + ". Type 'help' for available commands.");
        }
    } 
    catch (const std::exception& e) 
    {
        printError(std::string("Error: ") + e.what());
    }
}

void CommandManager::startInteractiveMode() 
{
    std::cout << "Password Manager - Type 'help' for commands" << std::endl;
    std::string input;
    
    while (true) 
    {
        std::cout << ">> ";
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") 
        {
            if(!confirmAndClose())
            {
                printError("Unknown response: " + input + ". Try to quit again.");
                continue;
            }
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        
        parseAndExecute(input);
    }
}

void CommandManager::handleCreate(const std::vector<std::string>& args) 
{
    if (args.size() != 6) 
    {
        printError("Usage: create <filename> <password cipher type> <password cipher config> <file cipher type> <file cipher config>");
        return;
    }
    
    std::string filename = args[1];
    std::string passwordType = args[2];
    std::string passwordConfig = args[3];
    std::string fileCipherType = args[4];
    std::string fileCipherConfig = args[5];
    
    PasswordFile::createFile(filename, passwordType, passwordConfig,fileCipherType, fileCipherConfig);
}

void CommandManager::handleOpen(const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        printError("Usage: open <filename> <file cipher type> <file cipher config>");
        return;
    }
    
    std::string filename = args[1];
    std::string fileCipherType = args[2];
    std::string fileCipherConfig = args[3];
    
    PasswordFile::openFile(filename, fileCipherType,fileCipherConfig);
}

void CommandManager::handleSave(const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        printError("Usage: save <website> <user> <password>");
        return;
    }
    
    std::string website = args[1];
    std::string user = args[2];
    std::string password = args[3];
    
    try
    {
        PasswordFile::getInstance().save(website,user,password);
    }
    catch(const std::exception& e)
    {
        printError(e.what());
    }
}

void CommandManager::handleLoad(const std::vector<std::string>& args) 
{
    if (args.size() < 2 || args.size()>3) 
    {
        printError("Usage: load <website> [<user>]");
        return;
    }
    
    std::string website = args[1];
    std::string user = (args.size() == 3) ? args[2] : "";
    
    std::vector<Entry> result;
    try
    {    
        result = PasswordFile::getInstance().getEntries(website, user);
        if (user.empty()) 
        {
            printInfo("All passwords for " + website + ":");
            for (size_t i = 0; i < result.size(); i++)
            {
                // password is decrypted after getEntries(website, user) so it actually gets the decrypted password
                printInfo(result[i].getWebsite()+" | "+result[i].getUsername()+" | "+result[i].getEncryptedPassword());
            }
        }
        else
        {
            printInfo(website +" | "+ user +" | "+ result[0].getEncryptedPassword());
        }
    }
    catch(const std::exception& e)
    {
        printError(e.what());
    }
}

void CommandManager::handleUpdate(const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        printError("Usage: update <website> <user> <new-password>");
        return;
    }
    
    std::string website = args[1];
    std::string user = args[2];
    std::string newPassword = args[3];
    
    try
    {
        PasswordFile::getInstance().update(website,user,newPassword);
    }
    catch(const std::exception& e)
    {
        printError(e.what());
    }
    
}

void CommandManager::handleDelete(const std::vector<std::string>& args) 
{
    if (args.size() < 2 || args.size()>3) 
    {
        printError("Usage: delete <website> [<user>]");
        return;
    }
    
    std::string website = args[1];
    std::string user = (args.size() == 3) ? args[2] : "";
    
    try
    {
        PasswordFile::getInstance().deleteEntry(website,user);
        if (user.empty()) 
        {
            printInfo("All entries deleted for website:" + website);
        } 
        else 
        {
            printInfo("Entry deleted for user: " + user + " at website: " + website);
        }
    }
    catch(const std::exception& e)
    {
        printError(e.what());
    }
}

void CommandManager::handleHelp(const std::vector<std::string>& args) 
{
    if(args.size()!=1)
    {
        printError("Usage: delete <website> [<user>]");
        return;
    }

    std::cout << "Available commands:" << std::endl;
    std::cout << "  create <filename> <passCipher type> <passCipher config> <fileCipher type> <fileCipher config>    - Create new password file" << std::endl;
    std::cout << "  open <filename> <file cipher type> <file cipher config>    - Open existing password file" << std::endl;
    std::cout << "  save <website> <user> <password>                           - Save password entry" << std::endl;
    std::cout << "  load <website> [<user>]                                    - Load password(s)" << std::endl;
    std::cout << "  update <website> <user> <new-password>                     - Update password" << std::endl;
    std::cout << "  delete <website> [<user>]                                  - Delete password entry" << std::endl;
    std::cout << "  status                                                     - Show current status" << std::endl;
    std::cout << "  help                                                       - Show this help" << std::endl;
    std::cout << "  exit/quit                                                  - Exit program" << std::endl;
    std::cout << std::endl;
    std::cout << "Supported ciphers: Caesar, TextCode, HillCipher" << std::endl;
}

void CommandManager::handleStatus(const std::vector<std::string>& args) 
{
    if(args.size()!=1)
    {
        printError("Usage: delete <website> [<user>]");
        return;
    }

    if (PasswordFile::isFileLoaded()) 
    {
        printInfo("Password file is loaded and ready.");
    } 
    else 
    {
        printInfo("No password file loaded. Use 'create' or 'open' command.");
    }
}

std::vector<std::string> CommandManager::tokenize(const std::string& str) 
{
    std::vector<std::string> tokens;
    std::string current = "";
    bool inQuotes = false;
    
    for (size_t i = 0; i < str.length(); i++) 
    {
        char c = str[i];
        
        if (c == '"') 
        {
            inQuotes = !inQuotes;
        } 
        else if (c == ' ' && !inQuotes) 
        {
            if (!current.empty()) 
            {
                tokens.push_back(current);
                current = "";
            }
        } 
        else 
        {
            current += c;
        }
    }
    
    if (!current.empty()) 
    {
        tokens.push_back(current);
    }
    
    return tokens;
}

void CommandManager::printError(const std::string& message) 
{
    std::cout << "[ERROR] " << message << std::endl;
}

void CommandManager::printInfo(const std::string& message) 
{
    std::cout<< message << std::endl;
}

bool CommandManager::confirmAndClose()
{
    if (PasswordFile::isFileLoaded())
    {
        std::string response;
        std::cout << "Do you want to save changes before exiting? (yes/no): ";
        std::getline(std::cin, response);
        std::vector<std::string> tokens = tokenize(response);

        if(tokens.size()!=1)
        {
            return false;
        }

        if (tokens[0] == "yes" || tokens[0] == "y")
        {
            PasswordFile::getInstance().saveFile();
        }
        else if(tokens[0] != "no" || tokens[0] != "n")
        {
            return false;
        }

        PasswordFile::closeFile();
        printInfo("Password file closed.");
    }
    return true;
}