#include "spawn.ih"

Spawn::Spawn(std::string const &command,
            std::string const &in, std::string const &out,
            std::string const &err)
:
    d_in(in.empty() ?   -2 : ::open(in.c_str(), O_RDONLY)),
    d_out(out.empty() ? -2 : ::open(out.c_str(), 
                                    O_CREAT | O_RDWR, S_IRUSR | S_IWUSR
                                    )),
    d_err(err.empty() ? -2 : ::open(err.c_str(), 
                                    O_CREAT | O_RDWR,
                                    S_IRUSR | S_IWUSR)),
    d_inRedirector(d_in),
    d_outRedirector(d_out),
    d_errRedirector(d_err),
    d_command(command)
{
    if (d_in == -1 || d_out == -1 || d_err == -1)
        throw Exception() << "Spawn: can't obtain file desciptors with " <<
            command << ": " << 
                    d_in << ' ' << in << ' ' <<
                    d_out << ' ' << out << ' ' <<
                    d_err << ' ' << err;
}
