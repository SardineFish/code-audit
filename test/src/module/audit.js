const codeAudit = require("code-audit");
const program = require("commander");
const fs = require("fs");

program
    .arguments("<source_file>")
    .action((source) => {
        source = fs.readFileSync(source).toString();
        const vulns = codeAudit.analyser.syntax.audit(source);
        //console.log(source);
        vulns.forEach(vuln => console.warn(`At:${vuln.line},${vuln.column}: ${vuln.description}`));
    })
    .parse(process.argv);