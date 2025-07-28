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

import { SpringProp, SpringPropInternal } from "./ArkSpringPropMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ScrollMotionInternal {
    public static fromPtr(ptr: KPointer): ScrollMotion {
        const obj: ScrollMotion = new ScrollMotion(undefined, undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ScrollMotion.getFinalizer())
        return obj
    }
}
export class ScrollMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scrollmotion(position: number, velocity: number, min: number, max: number, prop: SpringProp): KPointer {
        const retval = ArkUIGeneratedNativeModule._ScrollMotion_ctor(position, velocity, min, max, toPeerPtr(prop))
        return retval
    }
     constructor(position?: number, velocity?: number, min?: number, max?: number, prop?: SpringProp) {
        if (((position) !== (undefined)) || ((velocity) !== (undefined)) || ((min) !== (undefined)) || ((max) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr: KPointer = ScrollMotion.ctor_scrollmotion((position)!, (velocity)!, (min)!, (max)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, ScrollMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollMotion_getFinalizer()
    }
}
