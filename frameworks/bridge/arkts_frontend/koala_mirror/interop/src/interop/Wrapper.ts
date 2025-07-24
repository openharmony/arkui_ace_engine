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

import { ptrToString, nullptr, isSamePtr } from "#common/wrappers/Wrapper"
import { className } from "@koalaui/common"
import { KPointer } from "./InteropTypes"

export { isNullPtr, nullptr, ptrToBits, bitsToPtr, isSamePtr, ptrToString } from "#common/wrappers/Wrapper"

/**
 * An object holding reference to the native pointer.
 */
export class Wrapper {
    ptr: KPointer
    constructor(ptr: KPointer) {
        if (ptr == null)
            throw new Error(`Init <${className(this)}> with null native peer`)
        this.ptr = ptr
    }
    toString(): string {
        return `[native object <${className(this)}> at ${ptrToString(this.ptr)}]`
    }
}

export function getPtr(value: Wrapper|undefined): KPointer {
    return value?.ptr ?? nullptr
}

export function ptrEqual(a: Wrapper|undefined, b: Wrapper|undefined): boolean {
    if (a === b) return true
    if (a == undefined || b == undefined) return false
    return isSamePtr(a.ptr, b.ptr)
}
