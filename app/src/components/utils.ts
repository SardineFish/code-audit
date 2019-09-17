export function setTimeoutAsync(callback: ()=>void, time:number= 0)
{
    return new Promise<void>(resolve => {
        setTimeout(() => {
            callback();
            resolve();
        }, time);
    })
}