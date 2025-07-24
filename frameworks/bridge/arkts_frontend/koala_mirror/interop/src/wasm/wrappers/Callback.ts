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

import { KPointer } from "../../interop/InteropTypes"
import { CallbackRegistry } from "../../interop/Platform"

class CallbackInfo {
    cb: any
    recv: any
    constructor(callback: any, obj: any = null) {
        this.cb = callback
        this.recv = obj
    }
}

const GLOBAL_SCOPE = new class CallbackScope {
    static readonly CB_NULL = new CallbackInfo(
        () => { throw new Error("attempted to call a callback at NULL") },
        null
    )
    static readonly CB_UNDEFINED = new CallbackInfo(
        () => { throw new Error("attempted to call an uninitialized callback") },
        null
    )
    static readonly CB_NULL_ID = 0
    nextId: number
    callbackMap: Map<number, CallbackInfo> | null

    constructor() {
        this.nextId = 1
        this.callbackMap = new Map()
        this.callbackMap.set(CallbackScope.CB_NULL_ID, CallbackScope.CB_NULL)
    }

    addCallback(cb: any, obj: any): number {
        let id = this.nextId++
        this.callbackMap?.set(id, new CallbackInfo(cb, obj))
        return id
    }

    getCallback(id: number): CallbackInfo {
        return this.callbackMap?.get(id) || CallbackScope.CB_UNDEFINED
    }

    deleteCallback(id: number): void {
        if (id > CallbackScope.CB_NULL_ID) {
            this.callbackMap?.delete(id)
        }
    }

    release(): void {
        this.callbackMap = null
    }
}

function callCallback(callbackId: number): any {
    let CallbackInfo = GLOBAL_SCOPE.getCallback(callbackId)
    try {
        let cb = CallbackInfo.cb
        if (CallbackInfo.recv !== null) {
            cb = cb.bind(CallbackInfo.recv)
        }
        return cb()
    } catch (e) {
        console.error(e)
    }
}

export function registerCallback(callback: any, obj: any = null): KPointer {
    return GLOBAL_SCOPE.addCallback(callback, obj)
}

function releaseCallback(callbackId: number): void {
    return GLOBAL_SCOPE.deleteCallback(callbackId)
}

declare namespace globalThis {
    function callCallback(callbackId: number): any
    function releaseCallback(callbackId: number): any
}

globalThis.callCallback = callCallback
globalThis.releaseCallback = releaseCallback

export function setCallbackRegistry(_ignoredRegistry: CallbackRegistry) {
    // On WASM we don't need registry in current implementation.
}
