import codeAudit, { Analyser, Vulnerability } from "code-audit";
import React from "react";
import ReactDOM from "react-dom";
import { Layout, Menu, Icon, PageHeader, Switch, Button, Table, Dropdown, Statistic, Input, Descriptions, message, Progress, List } from "antd";
import Sider from "antd/lib/layout/Sider";
import { IconCompare } from "../components/icons";
import { Page } from "../components/page";
import { ColumnProps } from "antd/lib/table";
import CodeAudit from "code-audit";
import AceEditor from "react-ace";
import { promisify } from "util";
import fs from "fs";
import Path from "path";
import linq from "linq";

const { dialog } = require("electron").remote;

import "brace/mode/c_cpp";
import "brace/theme/github";
import Text from "antd/lib/typography/Text";
import Title from "antd/lib/typography/Title";
import { setTimeoutAsync } from "../components/utils";

type NodeDataSource = {
    key: string,
    name: string,
    port: number
};
type DiffDataSource = {
    key: string,
    source: string,
    sample: string,
    similarity: number,
}
const analyserName: { [key: string]: string } = {
    ["string"]: "String based",
    ["token"]: "Token based",
    ["syntax"]: "Syntax based"
};
const NodesTableColumns: ColumnProps<NodeDataSource>[] = [
    {
        title: "Name",
        dataIndex: "name",
        key: "name",
    },
    {
        title: "Port",
        dataIndex: "port",
        key: "port",
    }
];
const DiffTableColumns: ColumnProps<DiffDataSource>[] = [
    {
        title: "Source",
        dataIndex: "source",
        key: "source",
    },
    {
        title: "Sample",
        dataIndex: "sample",
        key: "sample"
    },
    {
        title: "Similarity",
        dataIndex: "similarity",
        key: "similarity",
        defaultSortOrder: "descend",
        sorter: (a, b)=>a.similarity - b.similarity
    }
];
interface AppState
{
    page: string;
    distributed: boolean;
    nodes: NodeDataSource[];
    analyser: "string" | "token" | "syntax" | string;
    similarity: number;
    diffSource: string;
    diffSample: string;
    searchFolder: string;
    progress: number;
    diffData: DiffDataSource[];
    auditSource: string;
    vulns: Vulnerability[];
}
class App extends React.Component<{}, AppState>
{
    analyserMenu = (
        <Menu onClick={e => {
            this.setState({ analyser: e.key });
            this.diffChange(null, null);
        }}>
            <Menu.Item key="string">String based</Menu.Item>
            <Menu.Item key="token">Token based</Menu.Item>
            <Menu.Item key="syntax">Syntax based</Menu.Item>
        </Menu>);
    constructor(props: any)
    {
        super(props);
        this.state = {
            page: "",
            distributed: false,
            nodes: [{
                key: "1",
                name: "Name",
                port: 1234
            }, {
                    key: "2",
                    name: "Name",
                    port: 1234
                }, {
                    key: "3",
                    name: "Name",
                    port: 1234
                }],
            analyser: "string",
            similarity: 0,
            diffSample: "",
            diffSource: "",
            searchFolder: "",
            progress: 0,
            diffData: [],
            auditSource: "",
            vulns:[],
        };
    }
    toggleDist(enable: boolean)
    {
        this.setState({
            distributed: enable
        });
        if (enable)
        {    
        }
    }
    scan()
    {
        const nodes = CodeAudit.master.scan(500);
        this.setState({
            nodes: nodes.map((node, idx) => {
                return {
                    key: idx.toString(),
                    name: node.name,
                    port: node.port
                }
            })
        });
        CodeAudit.master.start();
    }
    async audit(source: string)
    {
        this.setState({
            auditSource: source
        });
        if (this.state.distributed)
        {
            const vulns = await CodeAudit.syntax.auditAsync(source);    
            this.setState({
                vulns: vulns
            });
        }
        else {
            const vulns = CodeAudit.syntax.audit(source);
            this.setState({
                vulns: vulns
            });
        }
    }
    async setSearchFolder(folder: string)
    {
        this.setState({
            searchFolder: folder
        });
        const fileMap = new Map<string, string>();
        let files = await promisify(fs.readdir)(Path.resolve(folder));
        files = files.map(p => Path.resolve(folder, p));
        await Promise.all(files.map(async (f) => {
            const data = await promisify(fs.readFile)(f);
            fileMap.set(f, data.toString());
        }));
        console.log(fileMap);
        message.success(`Loaded ${files.length} files.`);
        const samples: { sourcePath: string, samplePath: string, }[] = [];
        for (let i = 0; i < files.length; i++)
        {
            for (let j = i + 1; j < files.length; j++)
            {
                samples.push({
                    sourcePath: files[i],
                    samplePath: files[j]
                });
            }    
        }
        const analyser: Analyser = ({
            "string": CodeAudit.string,
            "token": CodeAudit.token,
            "syntax": CodeAudit.syntax
        } as any)[this.state.analyser];

        let completed: DiffDataSource[] = [];
        if (this.state.distributed)
        {
            await Promise.all(samples.map(async (test) => {
                const s = await analyser.similarityAsync(fileMap.get(test.sourcePath), fileMap.get(test.samplePath))
                completed.push({
                    key: completed.length.toString(),
                    source: Path.parse(test.sourcePath).base,
                    sample: Path.parse(test.samplePath).base,
                    similarity: s
                });
                this.setState({
                    diffData: completed,
                    progress: completed.length / samples.length
                });

            }));    
        }
        else
        {
            await Promise.all(samples.map(async (test) => {
                await setTimeoutAsync(() => {
                    console.log(`diff ${test.sourcePath} with ${test.samplePath}`);
                    const s = analyser.similarity(fileMap.get(test.sourcePath), fileMap.get(test.samplePath))
                    completed.push({
                        key: completed.length.toString(),
                        source: Path.parse(test.sourcePath).base,
                        sample: Path.parse(test.samplePath).base,
                        similarity: s
                    });
                    this.setState({
                        diffData: completed,
                        progress: completed.length / samples.length
                    });
                    
                }, 300)

            }));  
        }

    }
    async folderPicker()
    {
        await this.setSearchFolder((await dialog.showOpenDialog({
            defaultPath: "../",
            properties: ["openDirectory"]
        })).filePaths[0]);
    }
    async diffChange(source: string, sample: string)
    {
        this.setState({
            diffSource: source === null
                ? this.state.diffSource
                : source,
            diffSample: sample === null
                ? this.state.diffSample
                : sample
        });
        const analyser: Analyser = ({
            "string": CodeAudit.string,
            "token": CodeAudit.token,
            "syntax": CodeAudit.syntax
        } as any)[this.state.analyser];

        let result = 0;
        if (this.state.distributed) {
            result = await analyser.similarityAsync(this.state.diffSource, this.state.diffSample);
        }
        else
            result = analyser.similarity(this.state.diffSource, this.state.diffSample);
        this.setState({
            similarity: result
        });
    }
    render()
    {
        return (
            <Layout
                style={{
                    position: "absolute",
                    height: "100%",
                    width: "100%",

                }}
            >
                <Sider>
                    <Menu theme="dark" onSelect={(e) => this.setState({page:e.key})}>
                        <Menu.Item key="dist">
                            <Icon type="cloud-server" />
                            <span>Distributed Node</span>
                        </Menu.Item>
                        <Menu.Item key="diff">
                            <Icon type="diff" />
                            <span>Code Diff</span>
                        </Menu.Item>
                        <Menu.Item key="batch-diff">
                            <Icon type="database" />
                            <span>Batch Diff</span>
                        </Menu.Item>
                        <Menu.Item key="audit">
                            <Icon type="audit" />
                            <span>Code Audit</span>
                        </Menu.Item>
                    </Menu>
                </Sider>
                <Layout>
                    <Page visible={this.state.page=="dist"}>
                        <PageHeader title="Distributed Controller" >
                            <div className="block">
                                <Switch checked={this.state.distributed} onChange={(t) => this.toggleDist(t)} />
                                <span style={{marginLeft:"1em"}}>Enable distributed mode.</span>
                            </div>
                            {
                                this.state.distributed
                                    ? <div className="block">
                                        <div className="block">
                                            <Button type="primary" onClick={()=>this.scan()}>Scan</Button>
                                        </div>
                                        <div className="block">
                                            <Table columns={NodesTableColumns} dataSource={this.state.nodes}></Table>
                                        </div>
                                      </div>
                                    : null
                            }
                        </PageHeader>
                    </Page>
                    <Page visible={this.state.page==="diff"}>
                        <PageHeader title="Code Diff">
                            <div className="block">
                                <span>Use analyser of </span>
                                <Dropdown overlay={this.analyserMenu}>
                                    <a href="#">{analyserName[this.state.analyser]}<Icon type="down" /></a>
                                </Dropdown>
                            </div>
                            <div className="block">
                                <Statistic title="Similarity" value={this.state.similarity * 100} precision={2} suffix="%"/>
                            </div>
                            <div className="block diff-editors">
                                <AceEditor
                                    mode="c_cpp"
                                    theme="github"
                                    onChange={(str) => this.diffChange(str, null)}
                                    value={this.state.diffSource}
                                    fontSize={16}
                                />
                                <div className="spacer"></div>
                                <AceEditor
                                    mode="c_cpp"
                                    theme="github"
                                    onChange={(str) => this.diffChange(null, str)}
                                    value={this.state.diffSample}
                                    fontSize={16}
                                />
                            </div>
                        </PageHeader>
                    </Page>
                    <Page visible={this.state.page === "batch-diff"}>
                        <PageHeader title="Batch Diff" subTitle="Diff all files with each other in specific folder.">
                            <Title level={4}>Search in Folder</Title>
                            <Input placeholder="/path/to/codes" addonAfter={<Icon type="folder-open" onClick={() => this.folderPicker()} />} value={this.state.searchFolder} onChange={(e) => this.setSearchFolder(e.target.value)}></Input>
                            <div className="block">
                                <Progress percent={this.state.progress*100}/>
                            </div>
                            <div className="block">
                                <Table columns={DiffTableColumns} dataSource={this.state.diffData}></Table>
                            </div>
                        </PageHeader>
                    </Page>
                    <Page visible={this.state.page==="audit"}>
                        <PageHeader title="Code Audit">
                            <div className="audit">
                                <AceEditor
                                    mode="c_cpp"
                                    theme="github"
                                    onChange={(str) => this.audit(str)}
                                    value={this.state.auditSource}
                                    fontSize={16}
                                    width=""
                                    height="360px"
                                />
                                <div className="block vulns-wrapper">
                                    <Title level={4}>Vulnerabilities</Title>
                                    <div className="vulns scroll-view">
                                        <List
                                            size="small"
                                            dataSource={this.state.vulns}
                                            renderItem={item => (
                                                <List.Item>
                                                    {`At:${item.line},${item.column}: ${item.description}`}
                                                </List.Item>
                                            )}
                                        />
                                    </div>
                                </div>
                            </div>
                        </PageHeader>
                    </Page>
                </Layout>
            </Layout>
        );
    }
}

const mount = document.querySelector("#root");

ReactDOM.render(<App></App>, mount);