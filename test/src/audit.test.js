const { expect } = require("chai");
const { test } = require("./lib");
const Path = require("path");
const { promisify } = require("util");
const fs = require("fs");
const { exec } = require('child_process');

describe("Auditor", () => {
    it("C Audit test", async () => {

        const result = await test(Path.resolve("./bin/audit_test"), [Path.resolve("./data/audit.c")], null);
        //const result = (await promisify(exec)(`"./bin/test-lexer" "${Path.resolve("./data/code.c")}"`)).stdout;
        const expectResult = (await promisify(fs.readFile)(Path.resolve("./data/audit-result.txt"))).toString();
        expect(result.replace(/\r\n/g, "\n")).be.equal(expectResult.replace(/\r\n/g, "\n"));
    });
});