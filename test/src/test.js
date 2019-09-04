const fs = require("fs");
const Path = require("path");

describe("Test start", () =>
    describe("Scan test files", () =>
    {
        fs.readdirSync(Path.resolve("./src")).forEach(
            file => /\.test\.js$/.test(file) ? it(file, () => require(Path.resolve("./src", file))) : null
        );
    })
);