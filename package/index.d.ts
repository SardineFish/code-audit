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
interface Analyser {
    similarity: (source: string, sample: string) => number;
}
interface StringBasedAnalyser extends Analyser {
    diff: (source: string, destination: string) => DiffChanges[];
}
interface TokenBasedAnalyser extends Analyser {
    diff: (source: string, destination: string) => DiffChanges[];
    analyse: (source: string) => Token[];
}
interface SyntaxBasedAnalyser extends Analyser {
    audit: (source: string) => Vulnerability[];
}
export declare const analyser: {
    string: StringBasedAnalyser;
    token: TokenBasedAnalyser;
    syntax: SyntaxBasedAnalyser;
    helloWorld: () => string;
};
export default analyser;
