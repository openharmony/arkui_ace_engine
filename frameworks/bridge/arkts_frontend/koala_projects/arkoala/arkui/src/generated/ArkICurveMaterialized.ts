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
export interface ICurve {
    interpolate(fraction: number): number
}
export class ICurveInternal implements MaterializedBase,ICurve {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_icurve(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ICurve_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = ICurveInternal.ctor_icurve()
        this.peer = new Finalizable(ctorPtr, ICurveInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ICurve_getFinalizer()
    }
    public interpolate(fraction: number): number {
        const fraction_casted = fraction as (number)
        return this.interpolate_serialize(fraction_casted)
    }
    private interpolate_serialize(fraction: number): number {
        const retval = ArkUIGeneratedNativeModule._ICurve_interpolate(this.peer!.ptr, fraction)
        return retval
    }
    public static fromPtr(ptr: KPointer): ICurveInternal {
        const obj: ICurveInternal = new ICurveInternal()
        obj.peer = new Finalizable(ptr, ICurveInternal.getFinalizer())
        return obj
    }
}
