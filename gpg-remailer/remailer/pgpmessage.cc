#include "remailer.ih"

bool Remailer::PGPmessage(ostream &out)
{
    static Pattern subject(R"(^Subject:\s*)");

    string line;
    
    while (getline(cin, line))
    {
        out << line << endl;                // copy a line

                                            // got the first ^Subject: line
        if (d_subject.empty() && subject << line) 
        {
            d_subject = subject.beyond();

            while (isblank(cin.peek()))     // multiple subject lines
            {
                getline(cin, line);         // get the next subject line
                d_subject += ' ' + String::trim(line);  // append it to the
            }                                           // subject seen so far

            rmQuotes(d_subject);
            d_log << level(LOGDEBUG) << "Subject: " << d_subject << '\n';
        }
            
        if (line == "-----BEGIN PGP MESSAGE-----")      // found the marker
            return true;
    }
    return false;
}





