const { expect } = require("chai");
const { test } = require("./lib");
const Path = require("path");
const { promisify } = require("util");
const fs = require("fs");
const { exec } = require('child_process');

describe("Syntax Paser", () => {
    it("C code test", async () => {
        
        const result = await test(Path.resolve("./bin/test_parser"), [Path.resolve("./data/syntax.c")], "");
        const expectResult = (await promisify(fs.readFile)(Path.resolve("./data/syntax-result.txt"))).toString();
        expect(result.replace(/\r\n/g, "\n")).be.equal(expectResult.replace(/\r\n/g, "\n"));
    });

    describe("Samples syntax test", () => {
        fs.readdirSync(Path.resolve("./data/samples"))
            .filter(file => /.*\.c/.test(file))
            .forEach(file => {
                it(`Test for "${file}"`, async () => {
                    const result = await test(Path.resolve("./bin/syntax_test"), [Path.resolve("./data/samples/" + file)], null);
                    expect(result).be.equal("");
                })
            });
    });
});