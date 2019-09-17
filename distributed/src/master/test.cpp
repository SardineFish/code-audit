#include "distribute.h"
#include <fstream>
#include "time.h"
#include <unistd.h>

using namespace std;
using namespace CodeAudit::Distributed::Master;
using namespace CodeAudit;

int N = 5000;
int completed = 0;
clock_t endTime, start;

int main(int argc, char**argv)
{

    auto master = new CodeAuditMaster();
    master->init();
    master->scan(500);
    master->start();

    if(argc >= 3)
    {
        fstream fs;
        char buffer[8192];
        fs.open(string(argv[1]));
        fs.get(buffer, 8192, EOF);
        fs.close();
        string source = string(buffer);
        fs.open(argv[2]);
        fs.get(buffer, 8192, EOF);
        fs.close();
        string sample = string(buffer);

        start = clock();

        for (int i = 0; i < N; i++)
        {
            master->similarity(AnalyserType::ANALYSE_TOKEN, source, sample, [=](Task* task, double similarity) -> void {
                cout << similarity << endl;
                completed++;
                if(completed == N)
                {
                    endTime = clock();
                    cout << "Time: " << (double)(endTime - start) / CLOCKS_PER_SEC << "s" << endl;
                }
            });
        }

        
    }
    else if (argc >= 2)
    {
        fstream fs;
        char buffer[8192];
        fs.open(string(argv[1]));
        fs.get(buffer, 8192, EOF);
        fs.close();
        string source = string(buffer);

        master->audit(source, [](Task* task, vector<Vulnerability> vulns) -> void {
            auto x = 1;
        });
    }
    sleep(5);
    master->stop();
    return 0;
}