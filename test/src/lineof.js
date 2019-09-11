const fs = require("fs");
const path = require("path");
const readline = require("readline");
const program = require("commander");

program.arguments("<pos> <file>")
    .action((pos, file) =>
    {
        const text = fs.readFileSync(path.resolve(file)).toString();
        const subtext = text.substr(0, parseInt(pos));
        const lines = subtext.split("\n").length;
        console.log(lines);
    })
    .parse(process.argv);