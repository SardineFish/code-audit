const { expect } = require("chai");
const { test } = require("./lib");
const Path = require("path");
const { promisify } = require("util");
const fs = require("fs");
const { exec } = require('child_process');

describe("Diff", () =>
{
    for (let idx = 0; idx < 5; idx++)
    {
        it(`Random text diff round ${idx}`, async () =>
        {
            const charSet = "qwertyuiopasdfghjklzxcvbnm".split("");
            const textA = charSet.sort(() => Math.random() - 0.5).join("");
            const textB = charSet.sort(() => Math.random() - 0.5).join("");
            const result = await test(Path.resolve("./bin/test-diff"), [], textA + " " + textB + " ");
            let text = "";
            let i = 0, j = 0;
            for (let k = 0; k < result.length; k++)
            {
                if (result[k] == "|")
                    break;
                switch (result[k])
                {
                    case "+":
                        text += textB[j++];
                        break;
                    case "-":
                        i++;
                        break;
                    case " ":
                        expect(textA[i]).be.equal(textB[j]);
                        text += textA[i];
                        i++ , j++;
                        break;
                }
            }
            expect(text).be.equal(textB);
        });
    }
    
});