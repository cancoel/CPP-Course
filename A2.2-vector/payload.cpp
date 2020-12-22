#include "payload.h"
#include <iostream>

// instantiate the payload's static count
size_t Payload::count_ = 0;

std::ostream& operator<<(std::ostream& os, const Payload& rhs)
{
    os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
    return os;
}
