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
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class SpringMotionInternal {
    public static fromPtr(ptr: KPointer): SpringMotion {
        const obj : SpringMotion = new SpringMotion(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, SpringMotion.getFinalizer())
        return obj
    }
}
export class SpringMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_springmotion(start: number, end: number, velocity: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringMotion_ctor(start, end, velocity, toPeerPtr(prop))
        return retval
    }
    constructor(start?: number, end?: number, velocity?: number, prop?: SpringProp) {
        if (((start) !== (undefined)) || ((end) !== (undefined)) || ((velocity) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr : KPointer = SpringMotion.ctor_springmotion((start)!, (end)!, (velocity)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, SpringMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringMotion_getFinalizer()
    }
}
