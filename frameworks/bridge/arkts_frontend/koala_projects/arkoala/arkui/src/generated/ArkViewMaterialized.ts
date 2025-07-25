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
export class ViewInternal {
    public static fromPtr(ptr: KPointer): View {
        const obj: View = new View()
        obj.peer = new Finalizable(ptr, View.getFinalizer())
        return obj
    }
}
export class View implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_view(): KPointer {
        const retval = ArkUIGeneratedNativeModule._View_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = View.ctor_view()
        this.peer = new Finalizable(ctorPtr, View.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._View_getFinalizer()
    }
    public create(value: any): any {
        const value_casted = value as (any)
        return this.create_serialize(value_casted)
    }
    private create_serialize(value: any): any {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Any", value)
        const retval = ArkUIGeneratedNativeModule._View_create(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
