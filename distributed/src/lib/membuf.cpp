#include "membuff.h"

membuf::membuf(char* buffer, size_t size): buffer(buffer), size(size)
{
    setg(buffer, buffer, buffer + size);
}