"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const codeAuditCore = require("./build/Release/code_audit.node");
var DiffChanges;
(function (DiffChanges) {
    DiffChanges[DiffChanges["Keep"] = 0] = "Keep";
    DiffChanges[DiffChanges["Delete"] = 1] = "Delete";
    DiffChanges[DiffChanges["Insert"] = 2] = "Insert";
    DiffChanges[DiffChanges["Replace"] = 3] = "Replace";
})(DiffChanges = exports.DiffChanges || (exports.DiffChanges = {}));
exports.analyser = {
    string: {
        similarity: codeAuditCore.stringSimilarity,
    },
    token: {
        similarity: codeAuditCore.tokenSimilarity,
    },
    syntax: {
        similarity: codeAuditCore.syntaxSimilarity,
    },
    helloWorld: codeAuditCore.helloWorld,
};
exports.default = exports.analyser;
