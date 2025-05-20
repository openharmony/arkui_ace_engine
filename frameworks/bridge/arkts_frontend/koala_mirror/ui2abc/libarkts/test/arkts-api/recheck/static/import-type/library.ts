export class Scope<T> {
    static scope<T>(): Scope<T> {
        throw new Error("")
    }
    cached(): T {
        throw new Error("")
    }
}

export interface ExportedType {
    scope<V>( value: () => V )
}
