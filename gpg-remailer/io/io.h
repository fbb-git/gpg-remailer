#ifndef INCLUDED_IO_
#define INCLUDED_IO_


class IO
{
    public:
        IO();

        static std::ofstream &open(ofstream &out, string const &name, 
                                    bool relax);

                                    // unlink if existing
        static void unlink(std::string const &name);

    private:
};
        
#endif
