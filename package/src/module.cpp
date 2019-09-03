#include <iostream>
#include <napi.h>
#include "code_audit.h"

using namespace std;
using namespace Napi;

namespace CodeAudit
{

String helloWorld(const CallbackInfo& info)
{
    Env env = info.Env();
    return String::New(env, helloWorldCore());
}

Object Init(Env env, Object exports)
{
    auto exportDefault = Object::New(env);
    exports.Set("helloWorld", Function::New(env, helloWorld));
    exportDefault.Set("helloWorld", Function::New(env, helloWorld));
    exports.Set("default", exportDefault);
    return exports;
}

NODE_API_MODULE(code_audit, Init)

} // namespace CodeAudit