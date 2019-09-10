const readline = require("readline");
const chalk = require("chalk").default;
const fetch = require("node-fetch");
const fs = require("fs");
const Path = require("path");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
});

let idx = 1;
const filePrefix = "data/samples/qsort";
const filePostfix = ".c";

console.log(Path.resolve("."));

rl.on("line", (line) =>
{
    const apiUrl = line.replace(/https:\/\/github.com\/(.+)\/(.+)\/blob\/master\/(.+)/, "https://api.github.com/repos/$1/$2/contents/$3");
    fetch(apiUrl)
        .then(response => response.json())
        .catch(err=>console.err(err))
        .then(data =>
        {
            const url = data.download_url;
            console.log(chalk.yellow(`Fetch: ${url}`));
            fetch(url)
                .then(r => r.text())
                .then(text =>
                {
                    text = `// ${line}

${text}`;
                    const path = Path.resolve(`${filePrefix}-${idx++}${filePostfix}`);
                    fs.writeFile(path, text, (err) =>
                    {
                        if (err)
                            console.error(err.message);
                        else
                            console.log(chalk.green(`Download: ${path}`));
                    })
                })
        });
});