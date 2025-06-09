declare type int32 = number
declare type int8 = number
declare type float32 = number

// This is to allow symbols of arkts stdlib
// to be visible during ets-tsc preprocessing

declare class StringBuilder {
    constructor(value: string)
    append(value: string): StringBuilder
}


declare const console: {
    assert(value: any, message?: string, ...optionalParams: any[]): void;

    clear(): void;

    count(label?: string): void;

    countReset(label?: string): void;

    debug(message?: any, ...optionalParams: any[]): void;

    // dir(obj: any, options?: InspectOptions): void;

    dirxml(...data: any[]): void;

    error(message?: any, ...optionalParams: any[]): void;

    group(...label: any[]): void;

    groupCollapsed(...label: any[]): void;

    groupEnd(): void;

    info(message?: any, ...optionalParams: any[]): void;

    log(message?: any, ...optionalParams: any[]): void;

    table(tabularData: any, properties?: ReadonlyArray<string>): void;

    time(label?: string): void;

    timeEnd(label?: string): void;

    timeLog(label?: string, ...data: any[]): void;

    trace(message?: any, ...optionalParams: any[]): void;

    warn(message?: any, ...optionalParams: any[]): void;

    profile(label?: string): void;

    profileEnd(label?: string): void;

    timeStamp(label?: string): void;

}

declare function setTimeout(func: () => void, delayMs?: int32): int32

declare function setInterval(func: () => void, delayMs?: int32): int32

declare function clearInterval(timerId: int32): void

declare function clearTimeout(timerId: int32): void
    
