#include "remailer.ih"

bool Remailer::step(char const *stepName)
{
    if (d_step.length() == 0)
        return true;

    if (d_step.substr(0, d_step.find(':')) == stepName)
    {
        d_log << level(LOGDEFAULT) << "Step " << stepName << " requested\n";
        return true;
    }

    return false;
}
