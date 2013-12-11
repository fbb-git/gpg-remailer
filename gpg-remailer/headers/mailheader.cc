#include "headers.ih"

Headers::const_hdr_iterator Headers::mailHeader(char const *hdr)
{
    setHeaderIterator(hdr, CASE_FULL);
    return beginh();
}
