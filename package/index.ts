const codeAuditCore = require("./build/Release/code_audit.node");

export interface Vulnerability
{
    level: number;
    line: number;
    column: number;
    description: string;
}
export enum DiffChanges
{
    Keep = 0,
    Delete = 1,
    Insert = 2,
    Replace = Delete | Insert,
}
export interface Token
{
    name: string;
    attribute: string;
    position: string;
}
enum AnalyserType
{
    StringPerLine = 0,
    StringPerChar = 1,
    Token = 2,
    Syntax = 3,
}

interface Analyser
{
    similarity: (source: string, sample: string) => number;
    similarityAsync: (source: string, sample: string) => Promise<number>;
}

interface StringBasedAnalyser extends Analyser
{
    diff: (source: string, destination: string) => DiffChanges[];    
}

interface TokenBasedAnalyser extends Analyser
{
    diff: (source: string, destination: string) => DiffChanges[];    
    analyse: (source: string) => Token[];
}

interface SyntaxBasedAnalyser extends Analyser
{
    audit: (source: string) => Vulnerability[];   
    auditAsync: (source: string) => Promise<Vulnerability[]>;
}

interface DistributedNode
{
    name: string;
    port: number;
}

class DistributedController
{
    private master: any;
    constructor()
    {
        this.master = codeAuditCore.initMaster();
    }
    scan(timeout: number): DistributedNode[]
    {
        return codeAuditCore.scan(this.master, timeout);
    }
    start()
    {
        codeAuditCore.start(this.master);
    }
    similarity(analyser: AnalyserType, source: string, sample: string)
    {
        return new Promise<number>((resolve) => {
            codeAuditCore.similarityAsync(this.master, analyser, source, sample, (similarity: number) => {
                resolve(similarity);
            });
        });
    }
    audit(source: string)
    {
        return new Promise<Vulnerability[]>(resolve => {
            codeAuditCore.auditAsync(this.master, source, (vulns: Vulnerability[]) => {
                resolve(vulns); 
            });
        })
    }
}

const Master = new DistributedController();

export const analyser = {
    string: <StringBasedAnalyser>{
        similarity: codeAuditCore.stringSimilarity,
        similarityAsync: async (source: string, sample: string) => await Master.similarity(AnalyserType.StringPerLine, source, sample),
    },
    token: <TokenBasedAnalyser>{
        similarity: codeAuditCore.tokenSimilarity,
        similarityAsync: async (source: string, sample: string) => await Master.similarity(AnalyserType.Token, source, sample),
    },
    syntax: <SyntaxBasedAnalyser>{
        similarity: codeAuditCore.syntaxSimilarity,
        similarityAsync: async (source: string, sample: string) => await Master.similarity(AnalyserType.Syntax, source, sample),
        audit: codeAuditCore.audit,
        auditAsync: async (source: string) => await Master.audit(source),
    },
    helloWorld: <() => string>codeAuditCore.helloWorld,
    master: Master,
};

export default analyser;
