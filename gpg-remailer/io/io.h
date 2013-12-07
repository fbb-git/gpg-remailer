#ifndef INCLUDED_IO_
#define INCLUDED_IO_

#include <iosfwd>

class IO
{
    public:
        static std::ofstream &open(std::ofstream &out, 
                                   std::string const &name, 
                                   bool relax);

                                    // unlink if existing
        static void unlink(std::string const &name);
};
        
#endif
