#include "main.ih"

Remailer::Preamble preamble(char const *options, 
                        Arg::LongOption const *const longOptions,
                        Arg::LongOption const *const longEnd,
                        int argc, char **argv)
{
    Remailer::Preamble remailerData{
                Arg::initialize(
                    "dhL:l:m:n:r:t:vx", longOptions,longEnd, argc, argv)
                };

    remailerData.arg.versionHelp(usage, version, 0);

    remailerData.configName = remailerData.arg.nArgs() == 0 ? 
                                    "etc/gpg-remailer.rc" 
                                : 
                                    remailerData.arg[0];

                                                // change to homedir
    if (chdir(remailerData.user.homedir().c_str()) != 0)    
        throw Exception() << "Failed to change dir to " << 
                                        remailerData.user.homedir();

    return remailerData;
}





