#ifndef INCLUDED_LOGEXCEPTION_
#define INCLUDED_LOGEXCEPTION_

#include <bobcat/exception>

    // Any fatal situations that should be logged. If stdErr == true the
    // message is first written to cerr. Logging is the responsibility of the
    // catch handler, catching a LogException.
struct LogException: public FBB:Exception
{
    bool d_stdErr;

    LogException(bool stdErr = false);

    public char const *msg();
};
        
inline LogException::LogException(bool stdErr)
:
    d_stdErr(stdErr)
{}

#endif
