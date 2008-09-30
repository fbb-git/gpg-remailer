#include "remailer.ih"

void Remailer::fileToReencrypt()
{
    if (!step("doc"))
        return;

    ifstream in;
    Msg::open(in, d_decryptedName);

    ofstream out;
    ofopen(d_reencryptName, &out);

    string line;
    getline(in, line);              // see if this line contains a bdry

    d_log << level(LOGDEBUG) << d_decryptedName << 
                              " 1st line: " << line << "\n";

    Pattern bdry("boundary=\"([^\"]+)");

    if (!(bdry << line))            // no boundary found
    {
        d_log << level(LOGDEBUG) << "No boundary, no multipart message\n";

        // if no boundary and the first line is a content-type then 
        // insert those lines first
        if (line.find("Content-Type:") == 0)
        {
            do
                out << line << endl;
            while (getline(in, line) && 
                           line.find_first_not_of(" \t") != string::npos);
            out << endl;
        }
        signatureSection(out, "");

        out << "\n" <<
                line << '\n' << 
                in.rdbuf();
    }
    else
    {
        string boundary = "--" + bdry[1];

        d_log << level(LOGDEBUG) << "Caught boundary " << boundary << 
                ": multipart message\n";

        out << line << endl;
        copyTo(out, in, boundary);
        signatureSection(out, boundary);
        out << in.rdbuf();
    }
}
