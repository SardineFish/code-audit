const codeAudit = require("code-audit");
const program = require("commander");
const fs = require("fs");

console.log(codeAudit.analyser.master.scan(500));
codeAudit.analyser.master.start();

program
    .arguments("<source_file>")
    .action(async (source) => {
        source = fs.readFileSync(source).toString();
        const vulns = await codeAudit.analyser.syntax.auditAsync(source);
        //console.log(source);
        vulns.forEach(vuln => console.warn(`At:${vuln.line},${vuln.column}: ${vuln.description}`));
    })
    .parse(process.argv);