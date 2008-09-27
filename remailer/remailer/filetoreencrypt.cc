#include "remailer.ih"

void Remailer::fileToReencrypt()
{
    if (!step("doc"))
        return;

    ifstream in;
    Msg::open(in, d_decryptedName);

    ofstream out;
    Msg::open(out, d_reencryptName);

    string line;
    getline(in, line);              // see if this line contains a bdry

    msg() << "First line in " << d_decryptedName << ":\n" << 
             line << info;

    Pattern bdry("boundary=\"([^\"]+)");

    if (!(bdry << line))            // no boundary found
    {
        msg() << "No boundary, no multipart message" << info;
        
        signatureSection(out, "");
        out << "\n" <<
                line << in.rdbuf();
    }
    else
    {
        string boundary = "--" + bdry[1];

        msg() << "Caught boundary " << boundary << 
                ": multipart message found" << info;

        out << line << endl;
        copyTo(out, in, boundary);
        signatureSection(out, boundary);
        out << in.rdbuf();
    }
}
