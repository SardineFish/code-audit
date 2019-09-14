#include <iostream>
#include <napi.h>
#include "code_audit.h"
#include "module.h"

using namespace std;
using namespace Napi;

namespace CodeAudit
{

// (source: string, sample: string) => number
Value stringSimilarity(const CallbackInfo& info)
{
    if(info.Length() < 2)
    {
        Error::New(info.Env(), "Require 2 parameters of string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if(!info[0].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 1 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if(!info[1].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 2 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }

    string src = info[0].As<String>();
    string sample = info[1].As<String>();
    auto analyser = new StringBasedAnalyser;
    auto similarity = analyser->calcSimilarity(src, sample);
    delete analyser;
    return Number::New(info.Env(), similarity);
}

Value tokenSimilarity(const CallbackInfo &info)
{
    if (info.Length() < 2)
    {
        Error::New(info.Env(), "Require 2 parameters of string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if (!info[0].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 1 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if (!info[1].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 2 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }

    string src = info[0].As<String>();
    string sample = info[1].As<String>();
    auto analyser = new TokenBasedAnalyser();
    auto similarity = analyser->calcSimilarity(src, sample);
    delete analyser;
    return Number::New(info.Env(), similarity);
}

Value syntaxSimilarity(const CallbackInfo &info)
{
    if (info.Length() < 2)
    {
        Error::New(info.Env(), "Require 2 parameters of string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if (!info[0].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 1 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }
    else if (!info[1].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 2 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }

    string src = info[0].As<String>();
    string sample = info[1].As<String>();
    auto analyser = new SyntaxBasedAnalyser();
    auto similarity = analyser->calcSimilarity(src, sample);
    delete analyser;
    return Number::New(info.Env(), similarity);
}

Value audit(const CallbackInfo &info)
{
    if(info.Length()<1 || !info[0].IsString())
    {
        TypeError::New(info.Env(), "Require parameters 1 to be string.")
            .ThrowAsJavaScriptException();
        return info.Env().Null();
    }

    string src = info[0].As<String>();
    auto analyser = new SyntaxBasedAnalyser;
    auto results = analyser->audit(src);
    delete analyser;
    return wrapVulns(info.Env(), results);
}

String helloWorld(const CallbackInfo& info)
{
    Env env = info.Env();
    return String::New(env, helloWorldCore());
}

Object Init(Env env, Object exports)
{
    auto exportDefault = Object::New(env);
    exports.Set("helloWorld", Function::New(env, helloWorld));
    exports.Set("stringSimilarity", Function::New(env, stringSimilarity));
    exports.Set("tokenSimilarity", Function::New(env, tokenSimilarity));
    exports.Set("syntaxSimilarity", Function::New(env, syntaxSimilarity));
    exports.Set("audit", Function::New(env, audit));
    exportDefault.Set("helloWorld", Function::New(env, helloWorld));
    exports.Set("default", exportDefault);
    return exports;
}

NODE_API_MODULE(code_audit, Init)

} // namespace CodeAudit