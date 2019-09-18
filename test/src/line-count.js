const fs = require("fs");
const path = require("path");
const folder = [
    "./app/src",
    "./core/include",
    "./core/src",
    "./distributed/include",
    "./distributed/src",
    "./package/src",
    "./test/src",
];
const except = [
    "parser.yy.cpp",
    "lex.yy.cpp"
];

let total = 0;
let lines = [];
function search(p)
{
    const sub = fs.readdirSync(p);
    sub.map(f=>path.resolve(p, f)).forEach(file => {
        if (fs.lstatSync(file).isDirectory())
            search(file);
        else
        {
            if (except.indexOf(path.parse(file).base) >= 0)
                return;
            const line = fs.readFileSync(file).toString().split("\n").length;
            total += line;
            lines.push({
                file: file,
                lines: line
            });
        }
    })
}

folder.forEach(p => search(p));

console.log(`Total lines: ${total}`);
lines = lines.sort((a, b) => b.lines - a.lines);
total = 0;
lines.forEach(line => {
    console.log(`${line.file}: ${line.lines}`);
    total += line.lines;
});
console.log(`Total lines: ${total}`);