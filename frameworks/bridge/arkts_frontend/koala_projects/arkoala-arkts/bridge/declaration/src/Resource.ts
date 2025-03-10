export interface Resource {
    bundleName: string;
    moduleName: string;
    id: number;
    params?: Array<string>;
    type?: number;
}