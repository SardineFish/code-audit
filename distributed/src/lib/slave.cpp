#include "slave.h"
#include <thread>
#include <memory.h>
#include <unistd.h>

using namespace std;
using namespace CodeAudit;
using namespace CodeAudit::Distributed::Slave;


Node::Node(string name, int port): name(name), port(port)
{
}

void Node::start()
{
Restart:
    auto sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock <=0)
    {
        cerr << "Failed to open socket." << endl;
        exit(1);
    }

    // Set address to be reuseable
    int optVal = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optVal, sizeof(optVal))  == -1)
    {
        cerr << "Failed to reuse port." << endl;
        exit(1);
    }

    // Listen to broadcast port
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_port = htons(port);

    if(bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        cerr << "Failed to bind on UDPbroadcast port " << port << endl;
        exit(1);
    }

    cout << "CodeAudit node setup." << endl;
    cout << "Bind to " << port << endl;

    // Receive handshake from master
    sockaddr_in sender;
    socklen_t addrlen = sizeof(sender);
    MasterBroadcast data;
    size_t size = 0;
    while(size ==0)
    {
        size = recvfrom(sock, &data, sizeof(data), 0, (sockaddr *)&sender, &addrlen);
    }
    cout << "Detected master server." << endl;

    if(data.version != VERSION)
    {
        cerr << "Unsupported version." << endl;
        goto Restart;
    }

    // Send handshake to master
Reconnect:
    close(sock);
    char buffer[65507];

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock <= 0)
    {
        cerr << "Failed to open socket." << endl;
        exit(1);
    }

    // Send back handshake
    SlaveHandshake handshake;
    size = handshake.serialize(buffer, 0, sizeof(buffer));
    if(sendto(sock, buffer, size, 0, (sockaddr *)&sender, sizeof(sender)) != size)
    {
        cerr << "Failed to reply handshake to master server." << endl;
        goto Reconnect;
    }

    // 
    while(true)
    {
        size = recvfrom(sock, &buffer, sizeof(buffer), 0, (sockaddr *)&sender, &addrlen);
        if(size < sizeof(int) * 2)
            goto Restart;
        TaskMessage msg;
        size_t len = msg.deserialize(buffer, 0, size);
        Message *result;
        cout << "Receive task from master." << endl;
        if (msg.task & TASK_SIMILARITY)
        {
            cout << "    Task: Similarity Evaluation" << endl;
            cout << "    Analyser: ";
            SimilarityRequest request;
            auto simResult = new SimilarityResult;
            request.deserialize(buffer, len, size);
            CodeAnanyser *analyser;
            switch (request.analyser)
            {
            case ANALYSE_STRING_CHAR:
                cout << "    String based." << endl;
                cout << "    Mode: Char" << endl;
                analyser = new StringBasedAnalyser(StringAnalyseMode::STR_ANALYSE_CHAR);
                break;
            case ANALYSE_STRING_LINE:
                cout << "    String based." << endl;
                cout << "    Mode: Line" << endl;
                analyser = new StringBasedAnalyser(StringAnalyseMode::STR_ANALYSE_LINE);
                break;
            case ANALYSE_TOKEN:
                cout << "    Token based." << endl;
                analyser = new TokenBasedAnalyser;
                break;
            case ANALYSE_SYNTAX:
                cout << "    Syntax based." << endl;
                analyser = new SyntaxBasedAnalyser;
                break;
            }
            simResult->similarity = analyser->calcSimilarity(request.source, request.sample);
            cout << "    Result: " << simResult->similarity << endl;
            result = simResult;
            delete analyser;
        }
        else if (msg.task & TASK_AUDIT)
        {
            cout << "    Task: Code Audition." << endl;
            AuditRequest request;
            request.deserialize(buffer, len, size);
            auto auditResult = new AuditResult;
            SyntaxBasedAnalyser analyser;
            auditResult->vulns = analyser.audit(request.source);
            result = auditResult;
            delete auditResult;
        }

        msg.params = result;
        size = msg.serialize(buffer, 0, sizeof(buffer));

        if (sendto(sock, buffer, size, 0, (sockaddr *)&sender, sizeof(sender)) != size)
        {
            cerr << "Failed to send result back to master server." << endl;
            continue;
        }
        cout << "Task completed." << endl;
    }
}