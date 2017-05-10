#include "remailer.ih"

// Lines are read in pairs. Initially line1 is read. 
// Then in a loop line2 is read until line2 contains the boundary

// If the boundary is found line1 is inserted into out. 
// With Apple-pgp encrypted e-mail this last line might not end with a \n 
// and therefore at this point the last line cannot be inserted as a line 
// ending in \n. With other encrypted e-mail the last line should be empty,
// and doesn't count for that reason.

// If line2 doesn't contain the boundary, line1 is inserted into out, with \n,
// and line1 and line2 are swapped. Now line1 is the line read last and the
// process is repeated.
 
void Remailer::copyToBoundary(ostream &out, istream &in)
{
    string line[2];
    string *line1 = &line[0];
    string *line2 = &line[1];

    char sep[] = "\r\n";                    // assume CRLF separator
    bool ignore1 = true;

    getline(in, *line1);                    // get the first line

    if (line1->back() == '\r')              // indeed: CRLF
        line->pop_back();                   // so: remove the CR fm the line
    else if (in.peek() == '\r')             // if it's LFCR?
    {
        in.ignore();                        // then remove the CR
        swap(sep[0], sep[1]);               // and swap the separator
    }
    else
    {
        sep[1] = 0;                         // only \n: that's the separator
        ignore1 = false;                    // only 1 separating character
    }


    while (getline(in, *line2, sep[0]))     // get the next line
    {
        if (ignore1)
            in.ignore();

        if (line2->find(d_boundary) == 0)   // boundary was found
        {
            out << *line1;                  // insert the last line w/o the
            return;                         // last separator
        }
        out << *line1 << sep;               // otherwise insert line1 + \n
        swap(line1, line2);                 // and prepare a new line1 
    }
        
    throw LogException() << "no " << d_boundary << 
                " boundary separator found in multipart MIME file\n";
}


