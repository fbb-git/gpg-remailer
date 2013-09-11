#include "remailer.ih"

bool Remailer::hasBoundary(string const &line, string const &msgTypeName)
{
    static Pattern d_bdry( R"(boundary="([^\"]+))" );

    if (d_bdry << line)
    {
        d_boundary = "--" + d_bdry[1];
        d_log << level(LOGDEBUG) << "Saw boundary " << d_boundary << 
                ": " << msgTypeName << " message\n";
        
        return true;
    }
     
    return false;   
}
