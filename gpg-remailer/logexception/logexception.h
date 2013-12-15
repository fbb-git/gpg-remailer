#ifndef INCLUDED_LOGEXCEPTION_
#define INCLUDED_LOGEXCEPTION_

#include <bobcat/exception>

    // Any fatal situations that should be logged. If stdErr == true the
    // message is first written to cerr. Logging is the responsibility of the
    // catch handler, catching a LogException.
class LogException: public FBB::Exception
{
    template <typename Type>
    friend LogException &&operator<<(LogException &&tmp, Type const &value);

    bool d_stdErr;

    public:
        LogException(bool stdErr = false);
    
        char const *msg() const;
};
        
inline LogException::LogException(bool stdErr)
:
    d_stdErr(stdErr)
{}

template <typename Type>
inline LogException &&operator<<(LogException &&tmp, Type const &value)
{
    static_cast<FBB::Exception &&>(std::move(tmp)) << value;

    return std::move(tmp);
}

#endif


