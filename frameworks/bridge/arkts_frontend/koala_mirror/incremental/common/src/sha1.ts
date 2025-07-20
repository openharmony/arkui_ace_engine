/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { CustomTextDecoder } from "@koalaui/compat"
import { int32 } from "@koalaui/compat"

const K = [
    (0x5a827999 | 0) as int32,
    (0x6ed9eba1 | 0) as int32,
    (0x8f1bbcdc | 0) as int32,
    (0xca62c1d6 | 0) as int32,
]

const inputBytes = 64
const inputWords = inputBytes / 4
const highIndex = inputWords - 2
const lowIndex = inputWords - 1
const workWords = 80
const allocBytes = 80
const allocWords = allocBytes / 4
const allocTotal = allocBytes * 100

export function createSha1(): SHA1Hash {
   return new SHA1Hash()
}

export class SHA1Hash {
    private A = (0x67452301 | 0) as int32
    private B = (0xefcdab89 | 0) as int32
    private C = (0x98badcfe | 0) as int32
    private D = (0x10325476 | 0) as int32
    private E = (0xc3d2e1f0 | 0) as int32
    private readonly _byte: Uint8Array
    private readonly _word: Int32Array
    private _size = 0
    private _sp = 0 // surrogate pair

    constructor() {
        if (!sharedBuffer || sharedOffset >= allocTotal) {
            sharedBuffer = new ArrayBuffer(allocTotal)
            sharedOffset = 0
        }

        this._byte = new Uint8Array(sharedBuffer, sharedOffset, allocBytes)
        this._word = new Int32Array(sharedBuffer, sharedOffset, allocWords)
        sharedOffset += allocBytes
    }

    updateString(data: string, encoding?: string): SHA1Hash {
        return this._utf8(data)
    }
    updateInt32(data: int32): SHA1Hash {
        const buffer = new Int32Array(1)
        buffer[0] = data
        return this.update(buffer)
    }

    update(data: Int32Array | Float32Array | Uint32Array | Uint8Array): SHA1Hash {
        if (data == null) {
            throw new TypeError("SHA1Hash expected non-null data: ")
        }

        let byteOffset: int32 = 0
        let length: int32 = 0
        let buffer: ArrayBufferLike | undefined = undefined

        // Improve: an attempt to wrie this in a generic form causes
        // es2panda to segfault.
        let BYTES_PER_ELEMENT = 4
        if (data instanceof Int32Array) {
            byteOffset = data.byteOffset as int32
            length = data.byteLength as int32
            buffer = data.buffer
        } else if (data instanceof Uint32Array) {
            byteOffset = data.byteOffset as int32
            length = data.byteLength as int32
            buffer = data.buffer
        } else if (data instanceof Float32Array) {
            byteOffset = data.byteOffset as int32
            length = data.byteLength as int32
            buffer = data.buffer
        } else if (data instanceof Uint8Array) {
            byteOffset = data.byteOffset as int32
            length = data.byteLength as int32
            buffer = data.buffer
            BYTES_PER_ELEMENT = 1
        }

        let blocks: int32 = ((length / inputBytes) | 0) as int32
        let offset: int32 = 0

        // longer than 1 block
        if ((blocks != 0) && !(byteOffset & 3) && !(this._size % inputBytes)) {
            const block = new Int32Array(buffer!, byteOffset, blocks * inputWords)
            while (blocks--) {
                this._int32(block, offset >> 2)
                offset += inputBytes
            }
            this._size += offset
        }

        // data: TypedArray | DataView
        if ((BYTES_PER_ELEMENT != 1) && buffer != undefined) {
            const rest = new Uint8Array(buffer, byteOffset + offset, length - offset)
            return this._uint8(rest)
        }

        // no more bytes
        if (offset == length) return this

        return this._uint8(new Uint8Array(buffer!), offset)
    }

    private _uint8(data: Uint8Array, offset?: int32): SHA1Hash {
        const _byte = this._byte
        const _word = this._word
        const length = data.length
        offset = ((offset ?? 0) | 0) as int32

        while (offset < length) {
            const start = this._size % inputBytes
            let index = start

            while (offset < length && index < inputBytes) {
                _byte[index++] = data[offset++]
            }

            if (index >= inputBytes) {
                this._int32(_word)
            }

            this._size += index - start
        }

        return this
    }

    private _utf8(text: string): SHA1Hash {
        const _byte = this._byte
        const _word = this._word
        const length = text.length
        let surrogate = this._sp

        for (let offset = 0; offset < length; ) {
            const start = this._size % inputBytes
            let index = start

            while (offset < length && index < inputBytes) {
                let code = text.charCodeAt(offset++) | 0
                if (code < 0x80) {
                    // ASCII characters
                    _byte[index++] = code
                } else if (code < 0x800) {
                    // 2 bytes
                    _byte[index++] = 0xC0 | (code >>> 6)
                    _byte[index++] = 0x80 | (code & 0x3F)
                } else if (code < 0xD800 || code > 0xDFFF) {
                    // 3 bytes
                    _byte[index++] = 0xE0 | (code >>> 12)
                    _byte[index++] = 0x80 | ((code >>> 6) & 0x3F)
                    _byte[index++] = 0x80 | (code & 0x3F)
                } else if (surrogate) {
                    // 4 bytes - surrogate pair
                    code = ((surrogate & 0x3FF) << 10) + (code & 0x3FF) + 0x10000
                    _byte[index++] = 0xF0 | (code >>> 18)
                    _byte[index++] = 0x80 | ((code >>> 12) & 0x3F)
                    _byte[index++] = 0x80 | ((code >>> 6) & 0x3F)
                    _byte[index++] = 0x80 | (code & 0x3F)
                    surrogate = 0
                } else {
                    surrogate = code
                }
            }

            if (index >= inputBytes) {
                this._int32(_word)
                _word[0] = _word[inputWords]
            }

            this._size += index - start
        }

        this._sp = surrogate
        return this
    }

    private _int32(data: Int32Array, offset?: int32): void {
        let A = this.A
        let B = this.B
        let C = this.C
        let D = this.D
        let E = this.E
        let i = 0
        offset = ((offset ??  0) | 0) as int32

        while (i < inputWords) {
            W[i++] = swap32(data[offset!++] as int32)
        }

        for (i = inputWords; i < workWords; i++) {
            W[i] = rotate1((W[i - 3] as int32) ^ (W[i - 8] as int32) ^ (W[i - 14] as int32) ^ (W[i - 16] as int32))
        }

        for (i = 0; i < workWords; i++) {
            const S = (i / 20) | 0
            const T = ((rotate5(A) + ft(S, B, C, D) + E + W[i] + K[S]) as int32) | 0
            E = D
            D = C
            C = rotate30(B)
            B = A
            A = T
        }

        this.A = (A + this.A) | 0
        this.B = (B + this.B) | 0
        this.C = (C + this.C) | 0
        this.D = (D + this.D) | 0
        this.E = (E + this.E) | 0
    }

    // digest(): Uint8Array
    // digest(encoding: string): string
    digest(encoding?: string): Uint8Array | string {
        const _byte = this._byte
        const _word = this._word
        let i = (this._size % inputBytes) | 0
        _byte[i++] = 0x80

        // pad 0 for current word
        while (i & 3) {
            _byte[i++] = 0
        }
        i >>= 2

        if (i > highIndex) {
            while (i < inputWords) {
                _word[i++] = 0
            }
            i = 0
            this._int32(_word)
        }

        // pad 0 for rest words
        while (i < inputWords) {
            _word[i++] = 0
        }

        // input size
        const bits64: int32 = this._size * 8
        const low32: int32 = ((bits64 & 0xffffffff) as int32 >>> 0) as int32
        const high32: int32 = ((bits64 - low32) as int32 / 0x100000000) as int32
        if (high32) _word[highIndex] = swap32(high32) as int32
        if (low32) _word[lowIndex] = swap32(low32) as int32

        this._int32(_word)

        return (encoding === "hex") ? this._hex() : this._bin()
    }

    private _hex(): string {
        let A = this.A
        let B = this.B
        let C = this.C
        let D = this.D
        let E = this.E

        return hex32Str(A, B, C, D, E)
    }

    private _bin(): Uint8Array {
        let A = this.A
        let B = this.B
        let C = this.C
        let D = this.D
        let E = this.E
        const _byte = this._byte
        const _word = this._word

        _word[0] = swap32(A)
        _word[1] = swap32(B)
        _word[2] = swap32(C)
        _word[3] = swap32(D)
        _word[4] = swap32(E)

        return _byte.slice(0, 20)
    }
}

type NS = (num: int32) => string
type NN = (num: int32) => int32

const W = new Int32Array(workWords)

let sharedBuffer: ArrayBuffer
let sharedOffset: int32 = 0

const swapLE: NN = ((c:int32):int32 => (((c << 24) & 0xff000000) | ((c << 8) & 0xff0000) | ((c >> 8) & 0xff00) | ((c >> 24) & 0xff)))
const swapBE: NN = ((c:int32):int32 => c)
const swap32: NN = isBE() ? swapBE : swapLE
const rotate1: NN = (num: int32): int32 => (num << 1) | (num >>> 31)
const rotate5: NN = (num: int32): int32 => (num << 5) | (num >>> 27)
const rotate30: NN = (num: int32): int32 => (num << 30) | (num >>> 2)

function isBE(): boolean {
    let a16 = new Uint16Array(1)
    a16[0] = 0xFEFF
    let a8 = new Uint8Array(a16.buffer)
    return a8[0] == 0xFE // BOM
}


function ft(s: int32, b: int32, c: int32, d: int32) {
    if (s == 0) return (b & c) | ((~b) & d)
    if (s == 2) return (b & c) | (b & d) | (c & d)
    return b ^ c ^ d
}

const hex32Decoder = new CustomTextDecoder()
const hex32DecodeBuffer = new Uint8Array(40)
function hex32Str(A: int32, B: int32, C: int32, D: int32, E: int32): string {
    writeIntAsHexUTF8(A, hex32DecodeBuffer, 0)
    writeIntAsHexUTF8(B, hex32DecodeBuffer, 8)
    writeIntAsHexUTF8(C, hex32DecodeBuffer, 16)
    writeIntAsHexUTF8(D, hex32DecodeBuffer, 24)
    writeIntAsHexUTF8(E, hex32DecodeBuffer, 32)
    return hex32Decoder.decode(hex32DecodeBuffer)
}

function writeIntAsHexUTF8(value: int32, buffer: Uint8Array, byteOffset: int32) {
    buffer[byteOffset++] = nibbleToHexCode((value >> 28) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 24) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 20) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 16) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 12) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 8 ) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 4 ) & 0xF)
    buffer[byteOffset++] = nibbleToHexCode((value >> 0 ) & 0xF)
}

function nibbleToHexCode(nibble: int32) {
    return nibble > 9 ? nibble + 87 : nibble + 48
}
