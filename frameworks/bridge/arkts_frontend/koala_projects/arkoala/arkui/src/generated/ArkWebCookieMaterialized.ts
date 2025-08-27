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
export class WebCookieInternal {
    public static fromPtr(ptr: KPointer): WebCookie {
        const obj: WebCookie = new WebCookie()
        obj.peer = new Finalizable(ptr, WebCookie.getFinalizer())
        return obj
    }
}
export class WebCookie implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcookie(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebCookie_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebCookie.ctor_webcookie()
        this.peer = new Finalizable(ctorPtr, WebCookie.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebCookie_getFinalizer()
    }
    public setCookie(): undefined {
        return this.setCookie_serialize()
    }
    public saveCookie(): undefined {
        return this.saveCookie_serialize()
    }
    private setCookie_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebCookie_setCookie(this.peer!.ptr)
        return retval
    }
    private saveCookie_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebCookie_saveCookie(this.peer!.ptr)
        return retval
    }
}
