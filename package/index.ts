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

interface Analyser
{
    similarity: (source: string, sample: string) => number;    
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
}

export const analyser = {
    string: <StringBasedAnalyser>{
        similarity: codeAuditCore.stringSimilarity,

    },
    token: <TokenBasedAnalyser>{
        similarity: codeAuditCore.tokenSimilarity,
    },
    syntax: <SyntaxBasedAnalyser>{
        similarity: codeAuditCore.syntaxSimilarity,
    },
    helloWorld: <() => string>codeAuditCore.helloWorld,
};

export default analyser;
