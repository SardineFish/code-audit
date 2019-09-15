#include "message.h"
#include "membuff.h"
#include <memory.h>

using namespace CodeAudit;
using namespace CodeAudit::Distributed;

template <typename T>
size_t serializeVal(char *buffer, size_t pos, size_t size, T *value);

template <typename T>
size_t deserializeVal(const char *buffer, size_t pos, size_t size, T *value);

size_t Message::serialize(char *buffer, size_t pos, size_t size)
{
    return 0;
}
size_t Message::deserialize(const char * buffer, size_t pos, size_t size)
{
    return 0;
}

size_t SimilarityRequest::serialize(char* buffer, size_t pos, size_t size)
{
    size_t len = serializeVal(buffer, pos, size, &analyser);
    len += serializeVal(buffer, pos + len, size, &source);
    len += serializeVal(buffer, pos + len, size, &sample);
    return len;
}
size_t SimilarityRequest::deserialize(const char * buffer, size_t pos, size_t size)
{
    size_t len = deserializeVal(buffer, pos, size, &analyser);
    len += deserializeVal(buffer, pos + len, size, &source);
    len += deserializeVal(buffer, pos + len, size, &sample);
    return len;
}

size_t SimilarityResult::serialize(char* buffer, size_t pos, size_t size)
{
    return serializeVal(buffer, pos, size, &similarity);
}
size_t SimilarityResult::deserialize(const char* buffer, size_t pos, size_t size)
{
    return deserializeVal(buffer, pos, size, &similarity);
}

size_t AuditRequest::serialize(char* buffer, size_t pos, size_t size)
{
    return serializeVal(buffer, pos, size, &source);
}
size_t AuditRequest::deserialize(const char* buffer, size_t pos, size_t size)
{
    return deserializeVal(buffer, pos, size, &source);
}

size_t AuditResult::serialize(char* buffer, size_t pos, size_t size)
{
    return deserializeVal(buffer, pos, size, &vulns);
}
size_t AuditResult::deserialize(const char* buffer, size_t pos, size_t size)
{
    return deserializeVal(buffer, pos, size, &vulns);
}

size_t TaskMessage::serialize(char *buffer, size_t pos, size_t size)
{
    size_t len = serializeVal(buffer, pos, size, &id);
    len += serializeVal(buffer, pos + len, size, &task);
    len += params->serialize(buffer, pos, size);
}
size_t TaskMessage::deserialize(const char* buffer, size_t pos, size_t size)
{
    size_t len = deserializeVal(buffer, pos, size, &id);
    len += deserializeVal(buffer, pos + len, size, &task);
    return len;
}

size_t SlaveHandshake::serialize(char* buffer, size_t pos, size_t size)
{
    size_t len = serializeVal(buffer, pos, size, &version);
    len += serializeVal(buffer, pos, size, &name);
    return len;
}
size_t SlaveHandshake::deserialize(const char* buffer, size_t pos, size_t size)
{
    size_t len = deserializeVal(buffer, pos, size, &version);
    len += deserializeVal(buffer, pos, size, &name);
    return len;
}

inline size_t serialize(char *buffer, size_t pos, size_t bufSize, const void *value, size_t valSize)
{
    if(pos + valSize < bufSize)
    {
        throw runtime_error("Buffer overflow");
    }
    memcpy((void *)buffer + pos, value, valSize);
    return valSize;
}
inline size_t deserialize(const char* buffer, size_t pos, size_t bufSize, void * value, size_t valSize)
{
    if (pos + valSize < bufSize)
    {
        throw runtime_error("Buffer overflow");
    }
    memcpy(value, buffer + pos, valSize);
    return valSize;
}

template <typename T>
size_t serializeVal<T>(char *buffer, size_t pos, size_t size, T *value)
{
    return serialize(buffer, pos, size, value, sizeof(T));
}
template <typename T>
size_t deserializeVal<T>(const char* buffer, size_t pos, size_t size, T* value)
{
    return deserialize(buffer, pos, size, value, sizeof(T));
}

template<>
size_t serializeVal<string>(char*buffer, size_t pos, size_t size, string* value)
{
    size_t strlen = value->size();
    const char *strBuf = value->c_str();
    size_t len = serialize(buffer, pos, size, &strlen, sizeof(size_t));
    len += serialize(buffer, pos + len, size, strBuf, strlen);
    return len;
}
template<>
size_t deserializeVal<string>(const char* buffer, size_t pos, size_t size, string*value)
{
    size_t strlen;
    size_t len = deserialize(buffer, pos, size, &strlen, sizeof(size_t));
    char strbuf[strlen + 1];
    len += deserialize(buffer, pos + len, size, strbuf, strlen);
    return len;
}

template<>
size_t serializeVal<vector<Vulnerability>>(char* buffer, size_t pos, size_t size, vector<Vulnerability>* vulns)
{
    size_t arrlen = vulns->size();
    size_t len = serialize(buffer, pos, size, &arrlen, sizeof(size_t));
    for (size_t i = 0; i < arrlen; i++)
    {
        Vulnerability vuln = vulns->at(i);
        len += serializeVal(buffer, pos + len, size, &(vuln.line));
        len += serializeVal(buffer, pos + len, size, &(vuln.column));
        len += serializeVal(buffer, pos + len, size, &(vuln.description));
        len += serializeVal(buffer, pos + len, size, &(vuln.level));
    }
    return len;
}
template<>
size_t deserializeVal<vector<Vulnerability>>(const char* buffer, size_t pos, size_t size, vector<Vulnerability>* vulns)
{
    size_t arrlen;
    size_t len = deserialize(buffer, pos, size, &arrlen, sizeof(size_t));
    for (size_t i = 0; i < arrlen;i++)
    {
        Vulnerability vuln;
        len += deserializeVal(buffer, pos + len, size, &(vuln.line));
        len += deserializeVal(buffer, pos + len, size, &(vuln.column));
        len += deserializeVal(buffer, pos + len, size, &(vuln.description));
        len += deserializeVal(buffer, pos + len, size, &(vuln.level));
    }
    return len;
}
