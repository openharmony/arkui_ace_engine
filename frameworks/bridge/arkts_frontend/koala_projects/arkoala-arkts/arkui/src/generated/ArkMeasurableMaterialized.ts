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

import { ConstraintSizeOptions, DirectionalEdgesT } from "./ArkUnitsInterfaces"
import { MeasureResult } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface Measurable {
    measure(constraint: ConstraintSizeOptions): MeasureResult
    getMargin(): DirectionalEdgesT
    getPadding(): DirectionalEdgesT
    getBorderWidth(): DirectionalEdgesT
}
export class MeasurableInternal implements MaterializedBase,Measurable {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_measurable(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Measurable_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = MeasurableInternal.ctor_measurable()
        this.peer = new Finalizable(ctorPtr, MeasurableInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Measurable_getFinalizer()
    }
    public measure(constraint: ConstraintSizeOptions): MeasureResult {
        const constraint_casted = constraint as (ConstraintSizeOptions)
        return this.measure_serialize(constraint_casted)
    }
    public getMargin(): DirectionalEdgesT {
        return this.getMargin_serialize()
    }
    public getPadding(): DirectionalEdgesT {
        return this.getPadding_serialize()
    }
    public getBorderWidth(): DirectionalEdgesT {
        return this.getBorderWidth_serialize()
    }
    private measure_serialize(constraint: ConstraintSizeOptions): MeasureResult {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(constraint)
        const retval  = ArkUIGeneratedNativeModule._Measurable_measure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : MeasureResult = retvalDeserializer.readMeasureResult()
        return returnResult
    }
    private getMargin_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getMargin(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getPadding_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getPadding(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getBorderWidth_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getBorderWidth(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    public static fromPtr(ptr: KPointer): MeasurableInternal {
        const obj : MeasurableInternal = new MeasurableInternal()
        obj.peer = new Finalizable(ptr, MeasurableInternal.getFinalizer())
        return obj
    }
}
