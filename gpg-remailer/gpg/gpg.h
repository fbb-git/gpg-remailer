#ifndef INCLUDED_GPG_
#define INCLUDED_GPG_

#include <string>

#include <../enums/enums.h>

namespace FBB: private Enums
{
    class Log
};

class GPG
{
    FBB::Log &d_log;
    std::string d_homedir;

    std::string d_options;

    public:
        GPG(FBB::Log &log, std::string const &homedir);

        void debug();
        void decrypt(std::string const &in, 
                     std::string const &out, std::string const &err);

        void encrypt(std::string const &recipients, 
                     std::string const &in, 
                     std::string const &out, std::string const &err);

    private:
        void run(std::string command, std::string const &in,
                 std::string const &out, std::string const &err);
};
        
inlien GPG::debug()
{
    d_options.clear();
}

#endif
