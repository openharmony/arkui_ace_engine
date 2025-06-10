/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class WebResourceErrorInternal {
    public static fromPtr(ptr: KPointer): WebResourceError {
        const obj : WebResourceError = new WebResourceError()
        obj.peer = new Finalizable(ptr, WebResourceError.getFinalizer())
        return obj
    }
}
export class WebResourceError implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourceerror(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebResourceError.ctor_webresourceerror()
        this.peer = new Finalizable(ctorPtr, WebResourceError.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceError_getFinalizer()
    }
    public getErrorInfo(): string {
        return this.getErrorInfo_serialize()
    }
    public getErrorCode(): number {
        return this.getErrorCode_serialize()
    }
    private getErrorInfo_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_getErrorInfo(this.peer!.ptr)
        return retval
    }
    private getErrorCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_getErrorCode(this.peer!.ptr)
        return retval
    }
}
