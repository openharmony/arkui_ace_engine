// todo can be removed if passing ArrayBuffer type through interop is possible
export class KBuffer {
    private readonly _buffer: Uint8Array
    public get buffer(): ArrayBuffer {
        return this._buffer
    }
    public get length(): number {
        return this._buffer.length
    }

    constructor(length: number) {
        this._buffer = new Uint8Array(length)
    }

    set(index: number, value: number): void {
        this._buffer[index] = value
    }

    get(index: number): number {
        return this._buffer[index]
    }
}