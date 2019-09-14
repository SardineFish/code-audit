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