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

import { int32 } from "@koalaui/common"
import { isNullPtr, nullptr, Wrapper } from "./Wrapper"
import { decodeToString } from "#common/wrappers/arrays"
import { setCallbackRegistry } from "#common/wrappers/Callback"
import { KPointer } from "./InteropTypes"

export abstract class NativeStringBase extends Wrapper {
    constructor(ptr: KPointer) {
        super(ptr)
    }

    protected abstract bytesLength(): int32
    protected abstract getData(data: Uint8Array): void

    toString(): string {
        let length = this.bytesLength()
        let data = new Uint8Array(length)
        this.getData(data)
        return decodeToString(data)
    }

    abstract close(): void
}

export abstract class ArrayDecoder<T> {
    abstract getArraySize(blob: KPointer): int32
    abstract disposeArray(blob: KPointer): void
    abstract getArrayElement(blob: KPointer, index: int32): T

    decode(blob: KPointer): Array<T> {
        const size = this.getArraySize(blob)
        const result = new Array<T>(size)
        for (let index = 0; index < size; index++) {
            result[index] = this.getArrayElement(blob, index)
        }
        this.disposeArray(blob)
        return result
    }
}


// TODO: the semicolons after methods in these interfaces are to
// workaround ArkTS compiler parser bug
export interface CallbackRegistry {
    registerCallback(callback: any, obj: any): KPointer;
}

export interface PlatformDefinedData {
    nativeString(ptr: KPointer): NativeStringBase;
    nativeStringArrayDecoder(): ArrayDecoder<NativeStringBase>;
    callbackRegistry(): CallbackRegistry | undefined;
}

let platformData: PlatformDefinedData|undefined = undefined

export function providePlatformDefinedData(platformDataParam: PlatformDefinedData) {
    platformData = platformDataParam
    let registry = platformDataParam.callbackRegistry()
    if (registry) setCallbackRegistry(registry)
}

export function withStringResult(ptr: KPointer): string|undefined {
    if (isNullPtr(ptr)) return undefined
    let managedString = platformData!.nativeString(ptr)
    let result = managedString?.toString()
    managedString?.close()
    return result
}

export function withStringArrayResult(ptr: KPointer): Array<string> {
    if (ptr == nullptr) return new Array<string>()
    let managedStringArray = platformData!.nativeStringArrayDecoder().decode(ptr)
    return managedStringArray.map((nativeString:NativeStringBase) => nativeString.toString())
}
