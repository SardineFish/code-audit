const codeAudit = require("code-audit");
const program = require("commander");
const fs = require("fs");

program
    .option("--string", "String based analyse.")
    .option("--token", "Token based analyse.")
    .option("--syntax", "Syntax based analyse.")
    .arguments("<source> <sample>")
    .action((source, sample) => {
        source = fs.readFileSync(source).toString();
        sample = fs.readFileSync(sample).toString();
        if (program.string)
            console.log(codeAudit.analyser.string.similarity(source, sample));
        else if (program.token)
            console.log(codeAudit.analyser.token.similarity(source, sample));
        else if (program.syntax)
            console.log(codeAudit.analyser.syntax.similarity(source, sample));
    })
    .parse(process.argv);