#include "remailer.ih"

void Remailer::checkMembers(vector<string> &target)
{
    auto member = find(target.begin(), target.end(), "members");

    if (member != target.end())         // accept all members
    {
        target.erase(member);           // this is not an envelope address
        target.insert(target.end(),     // add the members
                          d_members.begin(), d_members.end());
    }
}
