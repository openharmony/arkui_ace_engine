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

// import { LengthUnit } from "./generated/ArkArkuiExternalInterfaces"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./generated/peers/Serializer"
import { CallbackKind } from "./generated/peers/CallbackKind"
import { Deserializer } from "./generated/peers/Deserializer"
import { CallbackTransformer } from "./generated/peers/CallbackTransformer"
export interface Size {
    width: number;
    height: number;
}
export type Position = Vector2;
export interface Vector2 {
    x: number;
    y: number;
}
export enum LengthMetricsUnit {
    DEFAULT = 0,
    PX = 1
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export class LengthMetricsInternal {
    public static fromPtr(ptr: KPointer): LengthMetrics {
        const obj : LengthMetrics = new LengthMetrics(0)
        obj.peer = new Finalizable(ptr, LengthMetrics.getFinalizer())
        return obj
    }
}
export class LengthMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public unit: LengthUnit;
    public value: number;
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_lengthmetrics(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_ctor()
        return retval
    }
    constructor(value: number, unit?: LengthUnit) {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = LengthMetrics.ctor_lengthmetrics()
        this.peer = new Finalizable(ctorPtr, LengthMetrics.getFinalizer())
        if (unit === undefined) {
            this.setUnit(LengthUnit.VP);
            this.setValue(value);
            this.unit = LengthUnit.VP;
            this.value = value;
        } else {
            if (unit >= LengthUnit.PX && unit <= LengthUnit.LPX) {
                this.setUnit(unit);
                this.setValue(value);
                this.unit = unit;
                this.value = value;
            } else {
                this.setUnit(LengthUnit.VP);
                this.setValue(0);
                this.unit = LengthUnit.VP;
                this.value = 0;
            }
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LengthMetrics_getFinalizer()
    }
    public static px(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj : LengthMetrics = LengthMetrics.px_serialize(value_casted)
        obj.unit = LengthUnit.PX
        obj.value = value
        return obj
    }
    public static vp(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj : LengthMetrics = LengthMetrics.vp_serialize(value_casted)
        obj.unit = LengthUnit.VP
        obj.value = value
        return obj
    }
    public static fp(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj : LengthMetrics = LengthMetrics.fp_serialize(value_casted)
        obj.unit = LengthUnit.FP
        obj.value = value
        return obj
    }
    public static percent(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj : LengthMetrics = LengthMetrics.percent_serialize(value_casted)
        obj.unit = LengthUnit.PERCENT
        obj.value = value
        return obj
    }
    public static lpx(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj : LengthMetrics = LengthMetrics.lpx_serialize(value_casted)
        obj.unit = LengthUnit.LPX
        obj.value = value
        return obj
    }
    public static resource(value: Resource): LengthMetrics {
        const value_casted = value as (Resource)
        const obj : LengthMetrics = LengthMetrics.resource_serialize(value_casted)
        obj.unit = obj.getUnit()
        obj.value = obj.getValue()
        return obj
    }
    private getUnit(): LengthUnit {
        return this.getUnit_serialize()
    }
    private setUnit(unit: LengthUnit): void {
        const unit_casted = unit as (LengthUnit)
        this.setUnit_serialize(unit_casted)
        return
    }
    private getValue(): number {
        return this.getValue_serialize()
    }
    private setValue(value: number): void {
        const value_casted = value as (number)
        this.setValue_serialize(value_casted)
        return
    }
    private static px_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_px(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static vp_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_vp(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static fp_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_fp(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static percent_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_percent(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static lpx_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_lpx(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resource_serialize(value: Resource): LengthMetrics {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_resource(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private getUnit_serialize(): LengthUnit {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_getUnit(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setUnit_serialize(unit: LengthUnit): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setUnit(this.peer!.ptr, unit.valueOf())
    }
    private getValue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_getValue(this.peer!.ptr)
        return retval
    }
    private setValue_serialize(value: number): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setValue(this.peer!.ptr, value)
    }
}
