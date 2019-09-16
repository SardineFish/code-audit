#include "module.h"
Napi::Object wrapVuln(Env env, Vulnerability vuln)
{
    auto obj = Object::New(env);
    obj.Set("level", Number::New(env, vuln.level));
    obj.Set("line", Number::New(env, vuln.line));
    obj.Set("column", Number::New(env, vuln.column));
    obj.Set("description", String::New(env, vuln.description));
    return obj;
}

Napi::Array wrapVulns(Env env, const vector<Vulnerability>& vulns)
{
    auto arr = Array::New(env, vulns.size());
    for (size_t i = 0; i < vulns.size();i++)
    {
        arr.Set(i, wrapVuln(env, vulns[i]));
    }
    return arr;
}

Napi::Object wrapNode(Env env, const NodeInfo* node)
{
    auto obj = Object::New(env);
    obj.Set("name", String::New(env, node->name));
    obj.Set("port", Number::New(env, node->net.addr.sin_port));
    return obj;
}

Napi::Array wrapNodes(Env env, const vector<NodeInfo*>& nodes)
{
    auto arr = Array::New(env, nodes.size());
    for (size_t i = 0; i < nodes.size(); i++)
    {
        arr.Set(i, wrapNode(env, nodes[i]));
    }
    return arr;
}

/*
Napi::Array wrapDiffResult(Env env, const vector<DiffChanges> & changes)
{
    auto arr = Array::New(env, changes.size());
    for (size_t i = 0; i < changes.size();i++)
    {
        arr.Set(i, Number::New(env, changes[i]));
    }
    return arr;
}*/