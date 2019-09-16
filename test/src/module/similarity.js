const codeAudit = require("code-audit");
const program = require("commander");
const fs = require("fs");

console.log(codeAudit.analyser.master.scan(500));
codeAudit.analyser.master.start();

program
    .option("--string", "String based analyse.")
    .option("--token", "Token based analyse.")
    .option("--syntax", "Syntax based analyse.")
    .arguments("<source> <sample>")
    .action(async (source, sample) => {
        source = fs.readFileSync(source).toString();
        sample = fs.readFileSync(sample).toString();
        if (program.string)
        {
            let sim = await codeAudit.analyser.string.similarityAsync(source, sample);
            console.log(sim);
        }
        else if (program.token)
            console.log(await codeAudit.analyser.token.similarityAsync(source, sample));
        else if (program.syntax)
            console.log(await codeAudit.analyser.syntax.similarityAsync(source, sample));
    })
    .parse(process.argv);