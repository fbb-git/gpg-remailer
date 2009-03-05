#include "remailer.ih"

void Remailer::simple(ostream &toReencrypt, istream &in)
{
    d_log << level(LOGDEBUG) << "No boundary, no multipart message\n";
    
    // if no boundary and the first line is a content-type then 
    // insert those lines first
    if (line.find("Content-Type:") == 0)
    {
        do
            toReencrypt << line << endl;
        while (getline(in, line) && not onlyWS(line));
    
        toReencrypt << endl;
    }

    signatureSection(toReencrypt, "");
    
    toReencrypt << "\n" <<
                    line << '\n' << 
                    in.rdbuf();
}
