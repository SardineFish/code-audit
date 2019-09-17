export interface Vulnerability {
    level: number;
    line: number;
    column: number;
    description: string;
}
export declare enum DiffChanges {
    Keep = 0,
    Delete = 1,
    Insert = 2,
    Replace = 3
}
export interface Token {
    name: string;
    attribute: string;
    position: string;
}
declare enum AnalyserType {
    StringPerLine = 0,
    StringPerChar = 1,
    Token = 2,
    Syntax = 3
}
export interface Analyser {
    similarity: (source: string, sample: string) => number;
    similarityAsync: (source: string, sample: string) => Promise<number>;
}
export interface StringBasedAnalyser extends Analyser {
    diff: (source: string, destination: string) => DiffChanges[];
}
export interface TokenBasedAnalyser extends Analyser {
    diff: (source: string, destination: string) => DiffChanges[];
    analyse: (source: string) => Token[];
}
export interface SyntaxBasedAnalyser extends Analyser {
    audit: (source: string) => Vulnerability[];
    auditAsync: (source: string) => Promise<Vulnerability[]>;
}
interface DistributedNode {
    name: string;
    port: number;
}
declare class DistributedController {
    private master;
    constructor();
    scan(timeout: number): DistributedNode[];
    start(): void;
    similarity(analyser: AnalyserType, source: string, sample: string): Promise<number>;
    audit(source: string): Promise<Vulnerability[]>;
}
export declare const analyser: {
    string: StringBasedAnalyser;
    token: TokenBasedAnalyser;
    syntax: SyntaxBasedAnalyser;
    helloWorld: () => string;
    master: DistributedController;
};
export default analyser;
