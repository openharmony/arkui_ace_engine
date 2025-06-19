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

import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class LengthMetricsInternal {
    public static fromPtr(ptr: KPointer): LengthMetrics {
        const obj: LengthMetrics = new LengthMetrics()
        obj.peer = new Finalizable(ptr, LengthMetrics.getFinalizer())
        return obj
    }
}
export class LengthMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get unit(): LengthUnit {
        return this.getUnit()
    }
    set unit(unit: LengthUnit) {
        this.setUnit(unit)
    }
    get value(): number {
        return this.getValue()
    }
    set value(value: number) {
        this.setValue(value)
    }
    static ctor_lengthmetrics(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = LengthMetrics.ctor_lengthmetrics()
        this.peer = new Finalizable(ctorPtr, LengthMetrics.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LengthMetrics_getFinalizer()
    }
    public static px(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.px_serialize(value_casted)
    }
    public static vp(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.vp_serialize(value_casted)
    }
    public static fp(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.fp_serialize(value_casted)
    }
    public static percent(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.percent_serialize(value_casted)
    }
    public static lpx(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.lpx_serialize(value_casted)
    }
    public static resource(value: Resource): LengthMetrics {
        const value_casted = value as (Resource)
        return LengthMetrics.resource_serialize(value_casted)
    }
    private getUnit(): LengthUnit {
        return this.getUnit_serialize()
    }
    private setUnit(unit: LengthUnit): void {
        const unit_casted = unit as (LengthUnit)
        this?.setUnit_serialize(unit_casted)
        return
    }
    private getValue(): number {
        return this.getValue_serialize()
    }
    private setValue(value: number): void {
        const value_casted = value as (number)
        this?.setValue_serialize(value_casted)
        return
    }
    private static px_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_px(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static vp_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_vp(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static fp_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_fp(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static percent_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_percent(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static lpx_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_lpx(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resource_serialize(value: Resource): LengthMetrics {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_resource(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private getUnit_serialize(): LengthUnit {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_getUnit(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setUnit_serialize(unit: LengthUnit): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setUnit(this.peer!.ptr, unit)
    }
    private getValue_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_getValue(this.peer!.ptr)
        return retval
    }
    private setValue_serialize(value: number): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setValue(this.peer!.ptr, value)
    }
}
