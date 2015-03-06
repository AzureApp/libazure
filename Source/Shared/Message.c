#include "Message.h"

const char* enumToName(enum MessageType type)
{
    switch (type)
    {
        case StatusOK:
            return "StatusOK";
            break;
        case StatusErr:
            return "StatusErr";
            break;
        case Attach:
            return "Attach";
            break;
        case Detach:
            return "Detach";
            break;
        case NewSearch:
            return "NewSearch";
            break;
        case IterateSearch:
            return "IterateSearch";
            break;
        case Edit:
            return "Edit";
            break;
        case Lock:
            return "Lock";
            break;
        case Results:
            return "Results";
            break;
        default:
            return 0;
            break;
    }
}
