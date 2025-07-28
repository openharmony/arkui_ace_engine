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
export class ClientAuthenticationHandlerInternal {
    public static fromPtr(ptr: KPointer): ClientAuthenticationHandler {
        const obj: ClientAuthenticationHandler = new ClientAuthenticationHandler()
        obj.peer = new Finalizable(ptr, ClientAuthenticationHandler.getFinalizer())
        return obj
    }
}
export class ClientAuthenticationHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_clientauthenticationhandler(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ClientAuthenticationHandler_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = ClientAuthenticationHandler.ctor_clientauthenticationhandler()
        this.peer = new Finalizable(ctorPtr, ClientAuthenticationHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ClientAuthenticationHandler_getFinalizer()
    }
    public confirm(priKeyFile: string, certChainFile?: string): void {
        const priKeyFile_type = runtimeType(priKeyFile)
        const certChainFile_type = runtimeType(certChainFile)
        if (RuntimeType.UNDEFINED == certChainFile_type) {
            const authUri_casted = priKeyFile as (string)
            this?.confirm1_serialize(authUri_casted)
            return
        }
        if (RuntimeType.STRING == certChainFile_type) {
            const priKeyFile_casted = priKeyFile as (string)
            const certChainFile_casted = certChainFile as (string)
            this?.confirm0_serialize(priKeyFile_casted, certChainFile_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public cancel(): void {
        this?.cancel_serialize()
        return
    }
    public ignore(): void {
        this?.ignore_serialize()
        return
    }
    private confirm0_serialize(priKeyFile: string, certChainFile: string): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_confirm0(this.peer!.ptr, priKeyFile, certChainFile)
    }
    private confirm1_serialize(authUri: string): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_confirm1(this.peer!.ptr, authUri)
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_cancel(this.peer!.ptr)
    }
    private ignore_serialize(): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_ignore(this.peer!.ptr)
    }
}
