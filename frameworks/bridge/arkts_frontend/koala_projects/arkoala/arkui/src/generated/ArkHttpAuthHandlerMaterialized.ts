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

import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class HttpAuthHandlerInternal {
    public static fromPtr(ptr: KPointer): HttpAuthHandler {
        const obj: HttpAuthHandler = new HttpAuthHandler()
        obj.peer = new Finalizable(ptr, HttpAuthHandler.getFinalizer())
        return obj
    }
}
export class HttpAuthHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_httpauthhandler(): KPointer {
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = HttpAuthHandler.ctor_httpauthhandler()
        this.peer = new Finalizable(ctorPtr, HttpAuthHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HttpAuthHandler_getFinalizer()
    }
    public confirm(userName: string, password: string): boolean {
        const userName_casted = userName as (string)
        const password_casted = password as (string)
        return this.confirm_serialize(userName_casted, password_casted)
    }
    public cancel(): void {
        this?.cancel_serialize()
        return
    }
    public isHttpAuthInfoSaved(): boolean {
        return this.isHttpAuthInfoSaved_serialize()
    }
    private confirm_serialize(userName: string, password: string): boolean {
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_confirm(this.peer!.ptr, userName, password)
        return retval
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._HttpAuthHandler_cancel(this.peer!.ptr)
    }
    private isHttpAuthInfoSaved_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_isHttpAuthInfoSaved(this.peer!.ptr)
        return retval
    }
}
