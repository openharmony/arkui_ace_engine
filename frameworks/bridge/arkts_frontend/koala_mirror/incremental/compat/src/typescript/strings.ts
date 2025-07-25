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

import { int32 } from "./types"

interface SystemTextEncoder {
    encode(input?: string): Uint8Array;
    encodeInto(src: string, dest: Uint8Array): void;
}

interface WithStreamOption {
    stream?: boolean | undefined;
}

interface SystemTextDecoder {
    decode(
        input?: ArrayBuffer | null,
        options?: WithStreamOption
    ): string;
}

export class CustomTextEncoder {
    static readonly HeaderLen: int32 = Int32Array.BYTES_PER_ELEMENT

    constructor(encoder: SystemTextEncoder|undefined = ((typeof TextEncoder != "undefined") ? new TextEncoder() : undefined)) {
        this.encoder = encoder
    }

    private readonly encoder: SystemTextEncoder|undefined

    public static stringLength(input: string): int32 {
        let length = 0
        for (let i = 0; i < input.length; i++) {
            length++
            let cp = input.codePointAt(i)!
            if (cp >= 0x10000) {
                i++
            }
        }
        return length
    }

    encodedLength(input: string): int32 {
        let length = 0
        for (let i = 0; i < input.length; i++) {
            let cp = input.codePointAt(i)!
            if (cp < 0x80) {
                length += 1
            } else if (cp < 0x800) {
                length += 2
            } else if (cp < 0x10000) {
                length += 3
            } else {
                length += 4
                i++
            }
        }
        return length
    }

    private addLength(array: Uint8Array, offset: int32, len: int32): void {
        array[offset] = (len & 0xff)
        array[offset + 1] = ((len >> 8) & 0xff)
        array[offset + 2] = ((len >> 16) & 0xff)
        array[offset + 3] = ((len >> 24) & 0xff)
    }

    static getHeaderLength(array: Uint8Array, offset: int32 = 0): int32 {
        return (array[offset] | (array[offset + 1] << 8) | (array[offset + 2] << 16) | (array[offset + 3] << 24))
    }

    // Produces array of bytes with encoded string headed by 4 bytes (little endian) size information:
    // [s0][s1][s2][s3] [c_0] ... [c_size-1]
    encode(input: string | undefined, addLength: boolean = true): Uint8Array {
        let headerLen = addLength ? CustomTextEncoder.HeaderLen : 0
        let result: Uint8Array
        if (!input) {
            result = new Uint8Array(headerLen)
        } else if (this.encoder !== undefined) {
            result = this.encoder!.encode('s'.repeat(headerLen) + input)
        } else {
            let length = this.encodedLength(input)
            result = new Uint8Array(length + headerLen)
            this.encodeInto(input, result, headerLen)
        }
        if (addLength) {
            this.addLength(result, 0, result.length - headerLen)
        }
        return result
    }

    // Produces encoded array of strings with size information.
    encodeArray(strings: Array<string>): Uint8Array {
        let totalBytes = CustomTextEncoder.HeaderLen
        let lengths = new Int32Array(strings.length)
        for (let i = 0; i < lengths.length; i++) {
            let len = this.encodedLength(strings[i])
            lengths[i] = len
            totalBytes += len + CustomTextEncoder.HeaderLen
        }
        let array = new Uint8Array(totalBytes)
        let position = 0
        this.addLength(array, position, lengths.length)
        position += CustomTextEncoder.HeaderLen
        for (let i = 0; i < lengths.length; i++) {
            this.addLength(array, position, lengths[i])
            position += CustomTextEncoder.HeaderLen
            this.encodeInto(strings[i], array, position)
            position += lengths[i]
        }
        return array
    }

    encodeInto(input: string, result: Uint8Array, position: int32): Uint8Array {
        if (this.encoder !== undefined) {
            this.encoder!.encodeInto(input, result.subarray(position, result.length))
            return result
        }
        let index = position
        for (let stringPosition = 0; stringPosition < input.length; stringPosition++) {
            let cp = input.codePointAt(stringPosition)!
            if (cp < 0x80) {
                result[index++] = (cp | 0)
            } else if (cp < 0x800) {
                result[index++] = ((cp >> 6) | 0xc0)
                result[index++] = ((cp & 0x3f) | 0x80)
            } else if (cp < 0x10000) {
                result[index++] = ((cp >> 12) | 0xe0)
                result[index++] = (((cp >> 6) & 0x3f) | 0x80)
                result[index++] = ((cp & 0x3f) | 0x80)
            } else {
                result[index++] = ((cp >> 18) | 0xf0)
                result[index++] = (((cp >> 12) & 0x3f) | 0x80)
                result[index++] = (((cp >> 6) & 0x3f) | 0x80)
                result[index++] = ((cp & 0x3f) | 0x80)
                stringPosition++
            }
        }
        result[index] = 0
        return result
    }
}

export class CustomTextDecoder {
    static cpArrayMaxSize = 128
    constructor(decoder: SystemTextDecoder|undefined = ((typeof TextDecoder != "undefined") ? new TextDecoder() : undefined)) {
        this.decoder = decoder
    }

    private readonly decoder: SystemTextDecoder|undefined

    decode(input: Uint8Array): string {
        if (this.decoder !== undefined) {
            return this.decoder!.decode(input)
        }
        const cpSize = Math.min(CustomTextDecoder.cpArrayMaxSize, input.length)
        let codePoints = new Int32Array(cpSize)
        let cpIndex = 0;
        let index = 0
        let result = ""
        while (index < input.length) {
            let elem = input[index]
            let lead = elem & 0xff
            let count = 0
            let value = 0
            if (lead < 0x80) {
                count = 1
                value = elem
            } else if ((lead >> 5) == 0x6) {
                value = ((elem << 6) & 0x7ff) + (input[index + 1] & 0x3f)
                count = 2
            } else if ((lead >> 4) == 0xe) {
                value = ((elem << 12) & 0xffff) + ((input[index + 1] << 6) & 0xfff) +
                    (input[index + 2] & 0x3f)
                count = 3
            } else if ((lead >> 3) == 0x1e) {
                value = ((elem << 18) & 0x1fffff) + ((input[index + 1] << 12) & 0x3ffff) +
                    ((input[index + 2] << 6) & 0xfff) + (input[index + 3] & 0x3f)
                count = 4
            }
            codePoints[cpIndex++] = value
            if (cpIndex == cpSize) {
                cpIndex = 0
                result += String.fromCodePoint(...codePoints)
            }
            index += count
        }
        if (cpIndex > 0) {
            result += String.fromCodePoint(...codePoints.slice(0, cpIndex))
        }
        return result
    }
}
