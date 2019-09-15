#include <streambuf>

class membuf : public std::basic_streambuf<char>
{
public:
    size_t size;
    char *buffer;
    membuf(char *buffer, size_t size);
};