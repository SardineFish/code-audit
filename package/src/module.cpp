#include <iostream>
#include <napi.h>
#include "code_audit.h"
#include "module.h"

using namespace std;
using namespace Napi;

using namespace CodeAudit::Distributed::Master;

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

Value initMaster(const CallbackInfo&info)
{
    auto master = new CodeAuditMaster();
    master->init();
    auto obj = External<CodeAuditMaster>::New(info.Env(), master, [](Env env, CodeAuditMaster *data) -> void {
        delete data;
    });
    return obj;
}

Value scan(const CallbackInfo&info)
{
    if(info.Length() < 2 ||!info[0].IsExternal() ||!info[1].IsNumber())
    {
        TypeError::New(info.Env(), "Usage: scan(master: MasterController, timeout: number)")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    auto obj = info[0].As<External<CodeAuditMaster>>();
    auto master = obj.Data();
    auto timeout = info[1].As<Number>().Int32Value();
    master->scan(timeout);
    return wrapNodes(info.Env(), master->nodes);
}

Value start(const CallbackInfo&info)
{
    if (info.Length() < 1 || !info[0].IsExternal())
    {
        TypeError::New(info.Env(), "Usage: scan(master: MasterController, timeout: number)")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    auto obj = info[0].As<External<CodeAuditMaster>>();
    auto master = obj.Data();
    master->start();
    return info.Env().Undefined();
}

map<int, ThreadSafeFunction> tsfns;

Value similarityAsync(const CallbackInfo &info)
{
    if(info.Length() < 5)
    {
        TypeError::New(info.Env(), "Usage: similarityAsync(master: MasterController, analyser: AnalyserType, source: string, sample: string, callback: (similarity: double) => void)")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    auto obj = info[0].As<External<CodeAuditMaster>>();
    auto master = obj.Data();
    auto analyser = (AnalyserType)info[1].As<Number>().Int32Value();
    string source = info[2].As<String>();
    string sample = info[3].As<String>();
    auto callback = info[4].As<Function>();
    auto env = info.Env();
    string str = "test";

    Task* t = master->similarity(analyser, source, sample, [](Task* task, double similarity) -> void {
        tsfns[task->id].BlockingCall(&similarity, [=](Env env, Function func, double *value) {
            func.Call({Number::New(env, similarity)});
        });
        tsfns[task->id].Release();
        tsfns.erase(task->id);

    },[&](Task* task){
        tsfns[task->id] = ThreadSafeFunction::New(
            env,
            callback,
            "Similarity Callback",
            0,
            2 );
    });
    return env.Undefined();
}

Value auditAsync(const CallbackInfo& info)
{
    if (info.Length() < 3)
    {
        TypeError::New(info.Env(), "Usage: auditAsync(master: MasterController, source: string, callback: (vulns: Vulnerability[]) => void)")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    auto obj = info[0].As<External<CodeAuditMaster>>();
    auto master = obj.Data();
    string source = info[1].As<String>();
    auto callback = info[2].As<Function>();
    auto env = info.Env();
    master->audit(source, [](Task* task, vector<Vulnerability> vulns) -> void {
        tsfns[task->id].BlockingCall([=](Env env, Function func) {
            func.Call({wrapVulns(env, vulns)});
        });
        tsfns[task->id].Release();
        tsfns.erase(task->id);
    },
    [&](Task* task){
        tsfns[task->id] = ThreadSafeFunction::New(
            env,
            callback,
            "Similarity Callback",
            0,
            2 );
    });
    return env.Undefined();
}

String helloWorld(const CallbackInfo& info)
{
    Env env = info.Env();
    return String::New(env, helloWorldCore());
}

ThreadSafeFunction tslog;
map<int ,ThreadSafeFunction> fuuuuuuuu;
Object Init(Env env, Object exports)
{
    auto exportDefault = Object::New(env);
    exports.Set("helloWorld", Function::New(env, helloWorld));
    exports.Set("stringSimilarity", Function::New(env, stringSimilarity));
    exports.Set("tokenSimilarity", Function::New(env, tokenSimilarity));
    exports.Set("syntaxSimilarity", Function::New(env, syntaxSimilarity));
    exports.Set("audit", Function::New(env, audit));
    exports.Set("initMaster", Function::New(env, initMaster));
    exports.Set("scan", Function::New(env, scan));
    exports.Set("start", Function::New(env, start));
    exports.Set("similarityAsync", Function::New(env, similarityAsync));
    exports.Set("auditAsync", Function::New(env, auditAsync));
    exportDefault.Set("helloWorld", Function::New(env, helloWorld));
    exports.Set("default", exportDefault);
    fuuuuuuuu[0] = ThreadSafeFunction::New(
        env,
        env.Global().Get("console").As<Object>().Get("log").As<Function>(),
        "Resource Name",
        0,
        3);

    setLogger([&](string msg) -> void {
        fuuuuuuuu[0].BlockingCall(&msg, [=](Env _env, Function callback, string *value) {
            callback.Call({String::New(_env, msg)});
        });
        //env.Global().Get("console").As<Object>().Get("log").As<Function>().MakeCallback(env.Global(), {String::New(env, msg)});
    });
    return exports;
}

NODE_API_MODULE(code_audit, Init)

} // namespace CodeAudit