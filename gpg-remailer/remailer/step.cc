#include "remailer.ih"

bool Remailer::step(string const &stepName)
{
    MailType requiredType = find_if(s_step, s_stepEnd,  // find the info 
        [&](StepStruct const &stepStruct)               // matching the step
        {
            return stepName.find(stepStruct.stepName) == 0;
        }
    )->requiredType;

    if (d_step.empty())                         // exec. all steps by default
        return d_mailType == requiredType;      // but only if types match

    if (d_step.find(stepName) == 0)             // explicit step requested
    {
        d_log << level(LOGDEFAULT) << "Step " << d_step << " request\n";
        return true;
    }

    return false;
}
