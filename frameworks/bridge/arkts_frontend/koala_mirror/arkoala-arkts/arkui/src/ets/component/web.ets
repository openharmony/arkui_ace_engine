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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
export class WebCookieInternal {
    public static fromPtr(ptr: KPointer): WebCookie {
        return new WebCookie(ptr)
    }
}
export class WebCookie implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebCookie.getFinalizer())
    }
    constructor() {
        this(WebCookie.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebCookie_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebCookie_getFinalizer()
    }
    public setCookie(): void {
        this.setCookie_serialize()
        return
    }
    public saveCookie(): void {
        this.saveCookie_serialize()
        return
    }
    private setCookie_serialize(): void {
        ArkUIGeneratedNativeModule._WebCookie_setCookie(this.peer!.ptr)
    }
    private saveCookie_serialize(): void {
        ArkUIGeneratedNativeModule._WebCookie_saveCookie(this.peer!.ptr)
    }
}
export class WebCookie_serializer {
    public static write(buffer: SerializerBase, value: WebCookie): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebCookie {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebCookieInternal.fromPtr(ptr)
    }
}
