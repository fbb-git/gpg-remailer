#ifndef INCLUDED_ENUMS_
#define INCLUDED_ENUMS_


struct Enums
{
    enum LOGLEVELS
    {
        LOGDEBUG,
        LOGCOMMANDS,
        LOGDEFAULT
    };

    enum MailType
    {
        UNKNOWN,                // at step-processing
        CLEAR,
        ENCRYPTED
    };

    enum ClearText
    {
        ACCEPTED,
        REJECTED
    };
};
        
#endif
