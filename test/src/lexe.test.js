const { expect } = require("chai");
const { test } = require("./lib");
const Path = require("path");
const { promisify } = require("util");
const fs = require("fs");
const { exec } = require('child_process');

describe("Lexer", () =>
{
    it("C code test", async () =>
    {
        
        const result = await test(Path.resolve("./bin/test-lexer"), [], fs.readFileSync("./data/code.c"));
        //const result = (await promisify(exec)(`"./bin/test-lexer" "${Path.resolve("./data/code.c")}"`)).stdout;
        const expectResult = (await promisify(fs.readFile)(Path.resolve("./data/lex-result.txt"))).toString();
        expect("test").be.equal("test");
        expect(result.replace(/\r\n/g, "\n")).be.equal(expectResult.replace(/\r\n/g, "\n"));
    });
});