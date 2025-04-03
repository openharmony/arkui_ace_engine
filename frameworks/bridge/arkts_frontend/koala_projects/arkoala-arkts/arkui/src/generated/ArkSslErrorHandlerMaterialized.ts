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
export class SslErrorHandlerInternal {
    public static fromPtr(ptr: KPointer): SslErrorHandler {
        const obj : SslErrorHandler = new SslErrorHandler()
        obj.peer = new Finalizable(ptr, SslErrorHandler.getFinalizer())
        return obj
    }
}
export class SslErrorHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_sslerrorhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SslErrorHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SslErrorHandler.ctor_sslerrorhandler()
        this.peer = new Finalizable(ctorPtr, SslErrorHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SslErrorHandler_getFinalizer()
    }
    public handleConfirm(): void {
        this.handleConfirm_serialize()
        return
    }
    public handleCancel(): void {
        this.handleCancel_serialize()
        return
    }
    private handleConfirm_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleConfirm(this.peer!.ptr)
    }
    private handleCancel_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleCancel(this.peer!.ptr)
    }
}
