import React from "react";

function IconWrapper(className: string, element: JSX.Element): (props: React.HTMLAttributes<HTMLDivElement>) => JSX.Element
function IconWrapper(element: JSX.Element): (props: React.HTMLAttributes<HTMLDivElement>) => JSX.Element
function IconWrapper(classNameSet: string | JSX.Element, element?: JSX.Element): (props: React.HTMLAttributes<HTMLDivElement>) => JSX.Element {
    if (typeof (classNameSet) === "string")
        classNameSet = ["icon", classNameSet].join(" ");
    else {
        element = classNameSet as JSX.Element;
        classNameSet = "icon"
    }
    return (props: React.HTMLAttributes<HTMLDivElement>) => {
        let { className, children, ...others } = props;
        className = [classNameSet, className].join(" ");
        return (
            <div className={className} {...others}>
                {element}
            </div>
        );
    };
}

export function IconKey() {
    return (
        <svg viewBox="0 0 24 24">
            <path d="M7,14A2,2 0 0,1 5,12A2,2 0 0,1 7,10A2,2 0 0,1 9,12A2,2 0 0,1 7,14M12.65,10C11.83,7.67 9.61,6 7,6A6,6 0 0,0 1,12A6,6 0 0,0 7,18C9.61,18 11.83,16.33 12.65,14H17V18H21V14H23V10H12.65Z" />
        </svg>
    );
}

export const IconVerify = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M10,17L6,13L7.41,11.59L10,14.17L16.59,7.58L18,9M12,1L3,5V11C3,16.55 6.84,21.74 12,23C17.16,21.74 21,16.55 21,11V5L12,1Z" />
    </svg>
))

export const IconWarn = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M12,2A10,10 0 0,0 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2Z" />
        <path fill="white" d="M13,13H11V7H13M13,17H11V15H13Z" />
    </svg>
));

export const IconSend = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M2,21L23,12L2,3V10L17,12L2,14V21Z" />
    </svg>
));

export const IconLoading = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M12,4V2A10,10 0 0,0 2,12H4A8,8 0 0,1 12,4Z" />
        <path d="M12,20V22A10,10 0 0,0 22,12H20A8,8 0 0,1 12,20Z" />
    </svg>
));

export const IconCheck = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M21,7L9,19L3.5,13.5L4.91,12.09L9,16.17L19.59,5.59L21,7Z" />
    </svg>
));

export const IconWarnNoBackground = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M13,13H11V7H13M13,17H11V15H13M12,2Z" />
    </svg>
))

export const IconCheckedBox = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M10,17L5,12L6.41,10.58L10,14.17L17.59,6.58L19,8M19,3H5C3.89,3 3,3.89 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V5C21,3.89 20.1,3 19,3Z" />
    </svg>
));

export const IconUncheckedBox = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M19,3H5C3.89,3 3,3.89 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V5C21,3.89 20.1,3 19,3M19,5V19H5V5H19Z" />
    </svg>
));

export const IconCopy = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M19,21H8V7H19M19,5H8A2,2 0 0,0 6,7V21A2,2 0 0,0 8,23H19A2,2 0 0,0 21,21V7A2,2 0 0,0 19,5M16,1H4A2,2 0 0,0 2,3V17H4V3H16V1Z" />
    </svg>
));

export const IconError = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M12,2C17.53,2 22,6.47 22,12C22,17.53 17.53,22 12,22C6.47,22 2,17.53 2,12C2,6.47 6.47,2 12,2Z" />
        <path fill="white" d="M15.59,7L12,10.59L8.41,7L7,8.41L10.59,12L7,15.59L8.41,17L12,13.41L15.59,17L17,15.59L13.41,12L17,8.41L15.59,7Z" />
    </svg>
));

export const IconCross = IconWrapper((
    <svg viewBox="0 0 24 24">
        <path d="M19,6.41L17.59,5L12,10.59L6.41,5L5,6.41L10.59,12L5,17.59L6.41,19L12,13.41L17.59,19L19,17.59L13.41,12L19,6.41Z" />
    </svg>
));

export const IconEdit = IconWrapper("icon-edit", (
    <svg viewBox="0 0 24 24">
        <path d="M20.71,7.04C21.1,6.65 21.1,6 20.71,5.63L18.37,3.29C18,2.9 17.35,2.9 16.96,3.29L15.12,5.12L18.87,8.87M3,17.25V21H6.75L17.81,9.93L14.06,6.18L3,17.25Z" />
    </svg>
));

export const IconMore = IconWrapper("icon-more", (
    <svg viewBox="0 0 24 24">
        <path d="M16,12A2,2 0 0,1 18,10A2,2 0 0,1 20,12A2,2 0 0,1 18,14A2,2 0 0,1 16,12M10,12A2,2 0 0,1 12,10A2,2 0 0,1 14,12A2,2 0 0,1 12,14A2,2 0 0,1 10,12M4,12A2,2 0 0,1 6,10A2,2 0 0,1 8,12A2,2 0 0,1 6,14A2,2 0 0,1 4,12Z" />
    </svg>
));

export const IconMenu = IconWrapper("icon-menu", (
    <svg viewBox="0 0 24 24">
        <path d="M3,6H21V8H3V6M3,11H21V13H3V11M3,16H21V18H3V16Z" />
    </svg>
));

export const IconLeft = IconWrapper("icon-left", (
    <svg viewBox="0 0 24 24">
        <path d="M15.41,16.58L10.83,12L15.41,7.41L14,6L8,12L14,18L15.41,16.58Z" />
    </svg>
));

export const IconRight = IconWrapper("icon-right", (
    <svg viewBox="0 0 24 24">
        <path d="M8.59,16.58L13.17,12L8.59,7.41L10,6L16,12L10,18L8.59,16.58Z" />
    </svg>
));

export const IconDesktop = IconWrapper("icon-desktop", (
    <svg viewBox="0 0 24 24">
        <path d="M21,16H3V4H21M21,2H3C1.89,2 1,2.89 1,4V16A2,2 0 0,0 3,18H10V20H8V22H16V20H14V18H21A2,2 0 0,0 23,16V4C23,2.89 22.1,2 21,2Z" />
    </svg>
));

export const IconMobile = IconWrapper("icon-mobile", (
    <svg viewBox="0 0 24 24">
        <path d="M17.25,18H6.75V4H17.25M14,21H10V20H14M16,1H8A3,3 0 0,0 5,4V20A3,3 0 0,0 8,23H16A3,3 0 0,0 19,20V4A3,3 0 0,0 16,1Z" />
    </svg>
));

export const IconDoubleRight = IconWrapper("icon-double-right", (
    <svg viewBox="0 0 24 24">
        <path d="M5.59,7.41L7,6L13,12L7,18L5.59,16.59L10.17,12L5.59,7.41M11.59,7.41L13,6L19,12L13,18L11.59,16.59L16.17,12L11.59,7.41Z" />
    </svg>
));

export const IconCompare = IconWrapper("icon-compare", (
    <svg viewBox="0 0 24 24">
        <path d="M10,18H6V16H10V18M10,14H6V12H10V14M10,1V2H6C4.89,2 4,2.89 4,4V20A2,2 0 0,0 6,22H10V23H12V1H10M20,8V20C20,21.11 19.11,22 18,22H14V20H18V11H14V9H18.5L14,4.5V2L20,8M16,14H14V12H16V14M16,18H14V16H16V18Z" />
    </svg>
));