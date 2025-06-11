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
export class UrlStyleInternal {
    public static fromPtr(ptr: KPointer): UrlStyle {
        const obj: UrlStyle = new UrlStyle(undefined)
        obj.peer = new Finalizable(ptr, UrlStyle.getFinalizer())
        return obj
    }
}
export class UrlStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get url(): string {
        return this.getUrl()
    }
    static ctor_urlstyle(url: string): KPointer {
        const retval = ArkUIGeneratedNativeModule._UrlStyle_ctor(url)
        return retval
    }
     constructor(url?: string) {
        if ((url) !== (undefined))
        {
            const ctorPtr: KPointer = UrlStyle.ctor_urlstyle((url)!)
            this.peer = new Finalizable(ctorPtr, UrlStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UrlStyle_getFinalizer()
    }
    private getUrl(): string {
        return this.getUrl_serialize()
    }
    private getUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._UrlStyle_getUrl(this.peer!.ptr)
        return retval
    }
}
