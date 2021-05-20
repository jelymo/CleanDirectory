#include <fstream>
#include <iostream>
#include <string>

template<typename t>
void log(t text)
{
    std::cout<<text<<std::endl;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        log("*******************************Clean Directory********************************");
        log("This will delete all files that matches a given Git ignore file in a directory.");
        log(std::string("usage: ")+ argv[0] + " [gitginore location] [directory to be cleaned]");
        return -1;
    }
    std::ifstream gitIgnoreFileStream{argv[1]};
    if(!gitIgnoreFileStream)
    {
        log("Git ignore file doesnt exist");
        return -1;
    }

    std::string entry;
    while(std::getline(gitIgnoreFileStream, entry))
    {
        size_t entrySize = entry.size();
        if(entrySize <= 0)
        {
            continue;
        }

        if(entry.at(0)=='#')
        {
            continue;
        }

        if(entry.at(entrySize-1) == '*' && entry.at(entrySize-2) == '/')
        {
            entry = entry.substr(0,entrySize-2);
        }

        std::string command = "del /S /Q /F \"" + std::string(argv[2]) + "\\" + entry + "\"";
        system(command.c_str());
    }
    
    return 0;
}