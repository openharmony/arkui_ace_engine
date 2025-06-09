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
export class ColorFilterInternal {
    public static fromPtr(ptr: KPointer): ColorFilter {
        const obj: ColorFilter = new ColorFilter(undefined)
        obj.peer = new Finalizable(ptr, ColorFilter.getFinalizer())
        return obj
    }
}
export class ColorFilter implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_colorfilter(value: Array<number>): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: number = value[i]
            thisSerializer.writeNumber(value_element)
        }
        const retval = ArkUIGeneratedNativeModule._ColorFilter_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: Array<number>) {
        if ((value) !== (undefined))
        {
            const ctorPtr: KPointer = ColorFilter.ctor_colorfilter((value)!)
            this.peer = new Finalizable(ctorPtr, ColorFilter.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorFilter_getFinalizer()
    }
}
