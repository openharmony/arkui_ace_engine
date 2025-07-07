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

import { AnimateParam, TranslateOptions, ICurve, KeyframeAnimateParam, KeyframeState } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    public static KeyframeAnimationImpl(param: KeyframeAnimateParam, keyframes: Array<KeyframeState>): void {
        const param_casted = param as (KeyframeAnimateParam)
        const keyframes_casted = keyframes as KeyframeState[];
        AnimationExtender.KeyFrameAnimation_serialize(param_casted, keyframes_casted)
        return
    }
    public static OpenImplicitAnimation(param: AnimateParam): void {
        const param_casted = param as (AnimateParam)
        AnimationExtender.OpenImplicitAnimation_serialize(param_casted)
        return
    }
    public static AnimateToImmediatelyImpl(param: AnimateParam, event: (() => void)): void {
        const param_casted = param as (AnimateParam)
        const event__casted = event as (() => void)
        AnimationExtender.OpenImplicitAnimation_serializeImmediately(param_casted, event__casted)
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
    private static KeyFrameAnimation_serialize(value: KeyframeAnimateParam, keyframes: Array<KeyframeState>): void {
        const valueSerializer: Serializer = Serializer.hold()
        const value_delay = value.delay
        let value_delay_type: int32 = RuntimeType.UNDEFINED
        value_delay_type = runtimeType(value_delay)
        valueSerializer.writeInt8(value_delay_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_delay_type)) {
            const value_delay_value = value_delay!
            valueSerializer.writeNumber(value_delay_value)
        }
        const value_iterations = value.iterations
        let value_iterations_type: int32 = RuntimeType.UNDEFINED
        value_iterations_type = runtimeType(value_iterations)
        valueSerializer.writeInt8(value_iterations_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_iterations_type)) {
            const value_iterations_value = value_iterations!
            valueSerializer.writeNumber(value_iterations_value)
        }
        const value_onFinish = value.onFinish
        let value_onFinish_type: int32 = RuntimeType.UNDEFINED
        value_onFinish_type = runtimeType(value_onFinish)
        valueSerializer.writeInt8(value_onFinish_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_onFinish_type)) {
            const value_onFinish_value = value_onFinish!
            valueSerializer.holdAndWriteCallback(value_onFinish_value)
        }
        valueSerializer.writeInt32(keyframes.length as int32)
        keyframes.forEach((value) => {
            const value_duration = value.duration
            let value_duration_type: int32 = RuntimeType.UNDEFINED
            value_duration_type = runtimeType(value_duration)
            valueSerializer.writeInt8(value_duration_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_duration_type)) {
                const value_duration_value = value_duration!
                valueSerializer.writeNumber(value_duration_value)
            }
            const value_curve = value.curve
            let value_curve_type: int32 = RuntimeType.UNDEFINED
            value_curve_type = runtimeType(value_curve)
            valueSerializer.writeInt8(value_curve_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_curve_type)) {
                const value_curve_value = value_curve!
                let value_curve_value_type: int32 = RuntimeType.UNDEFINED
                value_curve_value_type = runtimeType(value_curve_value)
                if (TypeChecker.isCurve(value_curve_value)) {
                    valueSerializer.writeInt8(0 as int32)
                    const value_curve_value_0 = value_curve_value as Curve
                    valueSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_curve_value_0))
                }
                else if (RuntimeType.STRING == value_curve_value_type) {
                    valueSerializer.writeInt8(1 as int32)
                    const value_curve_value_1 = value_curve_value as string
                    valueSerializer.writeString(value_curve_value_1)
                }
                else if (RuntimeType.OBJECT == value_curve_value_type) {
                    valueSerializer.writeInt8(2 as int32)
                    const value_curve_value_2 = value_curve_value as ICurve
                    valueSerializer.writeICurve(value_curve_value_2)
                }
            }
            const value_event = value.event
            let value_event_type: int32 = RuntimeType.UNDEFINED
            value_event_type = runtimeType(value_event)
            valueSerializer.writeInt8(value_event_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_event_type)) {
                const value_event_value = value_event!
                valueSerializer.holdAndWriteCallback(value_event_value)
            }
        });
        ArkUIGeneratedNativeModule._AnimationExtender_KeyFrameAnimation(valueSerializer.asBuffer(), valueSerializer.length())
        valueSerializer.release()
    }
    private static OpenImplicitAnimation_serialize(param: AnimateParam): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static OpenImplicitAnimation_serializeImmediately(param: AnimateParam, event: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(param)
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(event)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = event!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimationImmediately(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static CloseImplicitAnimation_serialize(): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimation()
    }
    private static StartDoubleAnimation_serialize(node: KPointer, param: DoubleAnimationParam): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDoubleAnimationParam(param)
        ArkUIGeneratedNativeModule._AnimationExtender_StartDoubleAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static AnimationTranslate_serialize(node: KPointer, options: TranslateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(options)
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
