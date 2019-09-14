#pragma once
#include "code_audit.h"
#include "napi.h"

using namespace std;
using namespace Napi;
using namespace CodeAudit;

Napi::Object wrapVuln(Env env, Vulnerability vuln);
Napi::Array wrapVulns(Env env, const vector<Vulnerability> &vulns);