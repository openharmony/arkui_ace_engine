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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { AnimateParam_serializer, TranslateOptions_serializer, AnimateParam, TranslateOptions, ICurve, ICurve_serializer } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Curve } from "./enums"
export class AnimationExtender {
    public static SetClipRect(node: KPointer, x: float32, y: float32, width: float32, height: float32): void {
        const node_casted = node as (KPointer)
        const x_casted = x as (float32)
        const y_casted = y as (float32)
        const width_casted = width as (float32)
        const height_casted = height as (float32)
        AnimationExtender.SetClipRect_serialize(node_casted, x_casted, y_casted, width_casted, height_casted)
        return
    }
    public static OpenImplicitAnimation(param: AnimateParam): void {
        const param_casted = param as (AnimateParam)
        AnimationExtender.OpenImplicitAnimation_serialize(param_casted)
        return
    }
    public static CloseImplicitAnimation(): void {
        AnimationExtender.CloseImplicitAnimation_serialize()
        return
    }
    public static StartDoubleAnimation(node: KPointer, param: DoubleAnimationParam): void {
        const node_casted = node as (KPointer)
        const param_casted = param as (DoubleAnimationParam)
        AnimationExtender.StartDoubleAnimation_serialize(node_casted, param_casted)
        return
    }
    public static AnimationTranslate(node: KPointer, options: TranslateOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (TranslateOptions)
        AnimationExtender.AnimationTranslate_serialize(node_casted, options_casted)
        return
    }
    private static SetClipRect_serialize(node: KPointer, x: float32, y: float32, width: float32, height: float32): void {
        ArkUIGeneratedNativeModule._AnimationExtender_SetClipRect(node, x, y, width, height)
    }
    private static OpenImplicitAnimation_serialize(param: AnimateParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static CloseImplicitAnimation_serialize(): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimation()
    }
    private static StartDoubleAnimation_serialize(node: KPointer, param: DoubleAnimationParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DoubleAnimationParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_StartDoubleAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static AnimationTranslate_serialize(node: KPointer, options: TranslateOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimationTranslate(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type Callback_Extender_OnProgress = (value: float32) => void;
export type Callback_Extender_OnFinish = () => void;
export interface DoubleAnimationParam {
    propertyName: string;
    startValue: float32;
    endValue: float32;
    duration: int32;
    delay: int32;
    curve: Curve | string | ICurve;
    onProgress?: Callback_Extender_OnProgress;
    onFinish?: Callback_Extender_OnFinish;
}
export class DoubleAnimationParam_serializer {
    public static write(buffer: SerializerBase, value: DoubleAnimationParam): void {
        let valueSerializer : SerializerBase = buffer
        const value_propertyName  = value.propertyName
        valueSerializer.writeString(value_propertyName)
        const value_startValue  = value.startValue
        valueSerializer.writeFloat32(value_startValue)
        const value_endValue  = value.endValue
        valueSerializer.writeFloat32(value_endValue)
        const value_duration  = value.duration
        valueSerializer.writeInt32(value_duration)
        const value_delay  = value.delay
        valueSerializer.writeInt32(value_delay)
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        if (TypeChecker.isCurve(value_curve)) {
            valueSerializer.writeInt8(0)
            const value_curve_0  = value_curve as Curve
            valueSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_curve_0))
        }
        else if (RuntimeType.STRING == value_curve_type) {
            valueSerializer.writeInt8(1)
            const value_curve_1  = value_curve as string
            valueSerializer.writeString(value_curve_1)
        }
        else if (RuntimeType.OBJECT == value_curve_type) {
            valueSerializer.writeInt8(2)
            const value_curve_2  = value_curve as ICurve
            ICurve_serializer.write(valueSerializer, value_curve_2)
        }
        const value_onProgress  = value.onProgress
        let value_onProgress_type : int32 = RuntimeType.UNDEFINED
        value_onProgress_type = runtimeType(value_onProgress)
        valueSerializer.writeInt8(value_onProgress_type)
        if ((RuntimeType.UNDEFINED) != (value_onProgress_type)) {
            const value_onProgress_value  = value_onProgress!
            valueSerializer.holdAndWriteCallback(value_onProgress_value)
        }
        const value_onFinish  = value.onFinish
        let value_onFinish_type : int32 = RuntimeType.UNDEFINED
        value_onFinish_type = runtimeType(value_onFinish)
        valueSerializer.writeInt8(value_onFinish_type)
        if ((RuntimeType.UNDEFINED) != (value_onFinish_type)) {
            const value_onFinish_value  = value_onFinish!
            valueSerializer.holdAndWriteCallback(value_onFinish_value)
        }
    }
    public static read(buffer: DeserializerBase): DoubleAnimationParam {
        let valueDeserializer : DeserializerBase = buffer
        const propertyName_result : string = (valueDeserializer.readString() as string)
        const startValue_result : float32 = valueDeserializer.readFloat32()
        const endValue_result : float32 = valueDeserializer.readFloat32()
        const duration_result : int32 = valueDeserializer.readInt32()
        const delay_result : int32 = valueDeserializer.readInt32()
        const curve_buf_selector : int32 = valueDeserializer.readInt8()
        let curve_buf : Curve | string | ICurve | undefined
        if (curve_buf_selector == 0) {
            curve_buf = TypeChecker.Curve_FromNumeric(valueDeserializer.readInt32())
        }
        else if (curve_buf_selector == 1) {
            curve_buf = (valueDeserializer.readString() as string)
        }
        else if (curve_buf_selector == 2) {
            curve_buf = (ICurve_serializer.read(valueDeserializer) as ICurve)
        }
        else {
            throw new Error("One of the branches for curve_buf has to be chosen through deserialisation.")
        }
        const curve_result : Curve | string | ICurve = (curve_buf as Curve | string | ICurve)
        const onProgress_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onProgress_buf : Callback_Extender_OnProgress | undefined
        if ((RuntimeType.UNDEFINED) != (onProgress_buf_runtimeType))
        {
            const onProgress_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onProgress_buf__call : KPointer = valueDeserializer.readPointer()
            const onProgress_buf__callSync : KPointer = valueDeserializer.readPointer()
            onProgress_buf = (value: float32):void => { 
    const onProgress_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onProgress_buf__argsSerializer.writeInt32(onProgress_buf__resource.resourceId);
    onProgress_buf__argsSerializer.writePointer(onProgress_buf__call);
    onProgress_buf__argsSerializer.writePointer(onProgress_buf__callSync);
    onProgress_buf__argsSerializer.writeFloat32(value);
    InteropNativeModule._CallCallback(1264236374, onProgress_buf__argsSerializer.asBuffer(), onProgress_buf__argsSerializer.length());
    onProgress_buf__argsSerializer.release();
    return; }
        }
        const onProgress_result : Callback_Extender_OnProgress | undefined = onProgress_buf
        const onFinish_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onFinish_buf : Callback_Extender_OnFinish | undefined
        if ((RuntimeType.UNDEFINED) != (onFinish_buf_runtimeType))
        {
            const onFinish_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinish_buf__call : KPointer = valueDeserializer.readPointer()
            const onFinish_buf__callSync : KPointer = valueDeserializer.readPointer()
            onFinish_buf = ():void => { 
    const onFinish_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onFinish_buf__argsSerializer.writeInt32(onFinish_buf__resource.resourceId);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__call);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__callSync);
    InteropNativeModule._CallCallback(-733525640, onFinish_buf__argsSerializer.asBuffer(), onFinish_buf__argsSerializer.length());
    onFinish_buf__argsSerializer.release();
    return; }
        }
        const onFinish_result : Callback_Extender_OnFinish | undefined = onFinish_buf
        let value : DoubleAnimationParam = ({propertyName: propertyName_result, startValue: startValue_result, endValue: endValue_result, duration: duration_result, delay: delay_result, curve: curve_result, onProgress: onProgress_result, onFinish: onFinish_result} as DoubleAnimationParam)
        return value
    }
}
