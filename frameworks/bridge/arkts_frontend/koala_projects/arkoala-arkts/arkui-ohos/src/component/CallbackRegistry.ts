/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { KUint8ArrayPtr } from "@koalaui/interop"

// todo: do we need an Uint8Array version?
export type CallbackType = (args: KUint8ArrayPtr, length: int32) => int32

class CallbackRecord {
    public callback: CallbackType
    public autoDisposable: boolean

    constructor(callback: CallbackType, autoDisposable: boolean) {
        this.callback = callback
        this.autoDisposable = autoDisposable
    }
}

class CallbackRegistry {

    static INSTANCE = new CallbackRegistry()

    private callbacks = new Map<int32, CallbackRecord>()
    private id = 1024

    constructor() {
        this.callbacks.set(0, new CallbackRecord(
            (args: KUint8ArrayPtr, length: int32): int32 => {
                // console.log(`Callback 0 called with args = ${args} and length = ${length}`)
                throw new Error(`Null callback called`)
            }, false)
        )
    }

    wrap(callback: CallbackType, autoDisposable: boolean): int32 {
        const id = this.id++
        this.callbacks.set(id, new CallbackRecord(callback, autoDisposable))
        return id
    }

    wrapSystem(id: int32, callback: CallbackType, autoDisposable: boolean): int32 {
        this.callbacks.set(id, new CallbackRecord(callback, autoDisposable))
        return id
    }

    call(id: int32, args: KUint8ArrayPtr, length: int32): int32 {
        if (!this.callbacks.has(id)) {
            // console.log(`Callback ${id} is not known`)
            throw new Error(`Disposed or unwrapped callback called (id = ${id})`)
        }
        const record = this.callbacks.get(id)!
        if (record.autoDisposable) {
            this.dispose(id)
        }
        return record.callback(args, length)
    }

    dispose(id: int32) {
        this.callbacks.delete(id)
    }
}

export function wrapCallback(callback: CallbackType, autoDisposable: boolean = true): int32 {
    return CallbackRegistry.INSTANCE.wrap(callback, autoDisposable)
}

export function disposeCallback(id: int32) {
    CallbackRegistry.INSTANCE.dispose(id)
}

export function wrapSystemCallback(id:int32, callback: CallbackType): int32 {
    return CallbackRegistry.INSTANCE.wrapSystem(id, callback, false)
}

export function callCallback(id: int32, args: KUint8ArrayPtr, length: int32): int32 {
    return CallbackRegistry.INSTANCE.call(id, args, length)
}
