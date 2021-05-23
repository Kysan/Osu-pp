#ifndef utils_h
#define utils_h


#include <string>

// * retourne le dossier courant depuis argv[0] 
// * au cas ou l'executable est invoqué depuis 
// * un autre dossier que celui ou son fichier est
std::string currentWorkingDirectory(char const* argv0) {
    std::string cwd(argv0);
    std::size_t index = cwd.find_last_of("\\");

    index = index == std::string::npos ? cwd.find_last_of("/") : index;
    
    return (index == std::string::npos) 
            ? 
                std::string("") 
            : 
                cwd.substr(0, index);
}


#endif