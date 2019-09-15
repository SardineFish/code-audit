#pragma once
#include <cstdint>
#include <string>
#include "code_audit.h"

using namespace std;

namespace CodeAudit
{
namespace Distributed
{

class Message
{
public:
    virtual size_t serialize(char *buffer, size_t pos, size_t size);
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size);
};

enum AnalyserType {
    ANALYSE_STRING_CHAR,
    ANALYSE_STRING_LINE,
    ANALYSE_TOKEN,
    ANALYSE_SYNTAX,
};

class SimilarityRequest : public Message
{
public:
    AnalyserType analyser;
    string source;
    string sample;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

class SimilarityResult : public Message
{
public:
    double similarity;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

class AuditRequest : public Message
{
public:
    string source;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

class AuditResult :public Message
{
public:
    vector<Vulnerability> vulns;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

enum TaskType : int
{
    TASK_REQUEST = 1,
    TASK_RESULT = 2,
    TASK_SIMILARITY = 4,
    TASK_AUDIT = 8,
};

class TaskMessage : public Message
{
public:
    int id;
    TaskType task;
    Message* params;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

struct MasterBroadcast
{
    int version;
};

class SlaveHandshake : public Message
{
public:
    string name;
    int version;
    virtual size_t serialize(char *buffer, size_t pos, size_t size) override;
    virtual size_t deserialize(const char *buffer, size_t pos, size_t size) override;
};

} // namespace Distributed
}