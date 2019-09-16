#pragma once
#include "code_audit.h"
#include <vector>
#include <queue>
#include <sys/socket.h>
#include "master.h"
#include "slave.h"
#include <functional>

using namespace std;

void log(string msg);
void setLogger(function<void(string)> logger);