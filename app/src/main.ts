import electron, { BrowserWindow, app } from "electron";
import codeAudit from "code-audit";

let win: BrowserWindow;
function createWindow()
{
    win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true
        }
    });

    win.loadFile("./pages/index.html");

}
app.on('ready', createWindow);

app.on("activate", () =>
{
    if (win == null)
    {
        createWindow();
    }
});