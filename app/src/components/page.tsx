import React from "react";
import { Layout, PageHeader } from "antd";

export function Page(props: {visible: boolean, children:React.ReactNode })
{
    return (
        <Layout.Content className="page" style={{ display: props.visible ? "unset" : "none" }}>
            {props.children}
        </Layout.Content>
    )
}