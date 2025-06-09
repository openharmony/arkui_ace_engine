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
export class JsGeolocationInternal {
    public static fromPtr(ptr: KPointer): JsGeolocation {
        const obj: JsGeolocation = new JsGeolocation()
        obj.peer = new Finalizable(ptr, JsGeolocation.getFinalizer())
        return obj
    }
}
export class JsGeolocation implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_jsgeolocation(): KPointer {
        const retval = ArkUIGeneratedNativeModule._JsGeolocation_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = JsGeolocation.ctor_jsgeolocation()
        this.peer = new Finalizable(ctorPtr, JsGeolocation.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._JsGeolocation_getFinalizer()
    }
    public invoke(origin: string, allow: boolean, retain: boolean): void {
        const origin_casted = origin as (string)
        const allow_casted = allow as (boolean)
        const retain_casted = retain as (boolean)
        this?.invoke_serialize(origin_casted, allow_casted, retain_casted)
        return
    }
    private invoke_serialize(origin: string, allow: boolean, retain: boolean): void {
        ArkUIGeneratedNativeModule._JsGeolocation_invoke(this.peer!.ptr, origin, +allow, +retain)
    }
}
