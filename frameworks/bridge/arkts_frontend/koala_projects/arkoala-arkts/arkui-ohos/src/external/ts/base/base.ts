export declare class BusinessError<T = void> extends Error {
    constructor();
    constructor(code: number, error: Error);
    constructor(code: number, data: T, error: Error);
    code: number;
    data?: T;
}