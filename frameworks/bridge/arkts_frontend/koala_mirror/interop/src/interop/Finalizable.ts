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

import { Wrapper, nullptr } from "./Wrapper"
import { finalizerRegister, finalizerUnregister, Thunk } from "@koalaui/common"
import { InteropNativeModule } from "./InteropNativeModule"
import { pointer } from "./InteropTypes"

export class NativeThunk implements Thunk {
    finalizer: pointer
    obj: pointer
    name: string|undefined

    constructor(obj: pointer, finalizer: pointer, name?: string) {
        this.finalizer = finalizer
        this.obj = obj
        this.name = name
    }

    clean() {
        if (this.obj != nullptr) {
            this.destroyNative(this.obj, this.finalizer)
        }
        this.obj = nullptr
    }

    destroyNative(ptr: pointer, finalizer: pointer): void {
        InteropNativeModule._InvokeFinalizer(ptr, finalizer)
    }
}

/**
 * Class with the custom finalizer, usually used to release a native peer.
 * Do not use directly, only via subclasses.
 */
export class Finalizable extends Wrapper {
    finalizer: pointer
    cleaner?: NativeThunk = undefined
    managed: boolean
    constructor(ptr: pointer, finalizer: pointer, managed: boolean = true) {
        super(ptr)
        this.finalizer = finalizer
        this.managed = managed
        const handle = this.createHandle()

        if (this.managed) {
            // Improve: reenable exception.
            if (this.ptr == nullptr) return // throw new Error("Can't have nullptr ptr ${}")
            if (this.finalizer == nullptr) throw new Error("Managed finalizer is 0")

            const thunk = this.makeNativeThunk(ptr, finalizer, handle)
            finalizerRegister(this, thunk)
            this.cleaner = thunk
        }
    }

    createHandle(): string | undefined {
        return undefined
    }

    makeNativeThunk(ptr: pointer, finalizer: pointer, handle: string | undefined): NativeThunk {
        return new NativeThunk(ptr, finalizer, handle)
    }

    close() {
        if (this.ptr == nullptr) {
            throw new Error(`Closing a closed object: ` + this.toString())
        } else if (this.cleaner == null) {
            throw new Error(`No thunk assigned to ` + this.toString())
        } else {
            finalizerUnregister(this)
            this.cleaner.clean()
            this.cleaner = undefined
            this.ptr = nullptr
        }
    }

    release(): pointer {
        finalizerUnregister(this)
        if (this.cleaner)
            this.cleaner.obj = nullptr
        let result = this.ptr
        this.ptr = nullptr
        return result
    }

    resetPeer(pointer: pointer) {
        if (this.managed) throw new Error("Can only reset peer for an unmanaged object")
        this.ptr = pointer
    }

    use<R>(body: (value: Finalizable) => R): R {
        let result = body(this)
        this.close()
        return result
    }
}
