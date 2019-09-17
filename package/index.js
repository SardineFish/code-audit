"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const codeAuditCore = require("./build/Release/code_audit.node");
var DiffChanges;
(function (DiffChanges) {
    DiffChanges[DiffChanges["Keep"] = 0] = "Keep";
    DiffChanges[DiffChanges["Delete"] = 1] = "Delete";
    DiffChanges[DiffChanges["Insert"] = 2] = "Insert";
    DiffChanges[DiffChanges["Replace"] = 3] = "Replace";
})(DiffChanges = exports.DiffChanges || (exports.DiffChanges = {}));
var AnalyserType;
(function (AnalyserType) {
    AnalyserType[AnalyserType["StringPerLine"] = 0] = "StringPerLine";
    AnalyserType[AnalyserType["StringPerChar"] = 1] = "StringPerChar";
    AnalyserType[AnalyserType["Token"] = 2] = "Token";
    AnalyserType[AnalyserType["Syntax"] = 3] = "Syntax";
})(AnalyserType || (AnalyserType = {}));
class DistributedController {
    constructor() {
        this.master = codeAuditCore.initMaster();
    }
    scan(timeout) {
        return codeAuditCore.scan(this.master, timeout);
    }
    start() {
        codeAuditCore.start(this.master);
    }
    stop() {
        codeAuditCore.stop(this.master);
    }
    similarity(analyser, source, sample) {
        return new Promise((resolve) => {
            codeAuditCore.similarityAsync(this.master, analyser, source, sample, (similarity) => {
                resolve(similarity);
            });
        });
    }
    audit(source) {
        return new Promise(resolve => {
            codeAuditCore.auditAsync(this.master, source, (vulns) => {
                resolve(vulns);
            });
        });
    }
}
const Master = new DistributedController();
exports.analyser = {
    string: {
        similarity: codeAuditCore.stringSimilarity,
        similarityAsync: (source, sample) => __awaiter(void 0, void 0, void 0, function* () { return yield Master.similarity(AnalyserType.StringPerLine, source, sample); }),
    },
    token: {
        similarity: codeAuditCore.tokenSimilarity,
        similarityAsync: (source, sample) => __awaiter(void 0, void 0, void 0, function* () { return yield Master.similarity(AnalyserType.Token, source, sample); }),
    },
    syntax: {
        similarity: codeAuditCore.syntaxSimilarity,
        similarityAsync: (source, sample) => __awaiter(void 0, void 0, void 0, function* () { return yield Master.similarity(AnalyserType.Syntax, source, sample); }),
        audit: codeAuditCore.audit,
        auditAsync: (source) => __awaiter(void 0, void 0, void 0, function* () { return yield Master.audit(source); }),
    },
    helloWorld: codeAuditCore.helloWorld,
    master: Master,
};
exports.default = exports.analyser;
