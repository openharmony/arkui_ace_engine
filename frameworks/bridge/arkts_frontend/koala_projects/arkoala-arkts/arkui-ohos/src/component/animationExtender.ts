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

import { AnimateParam, TranslateOptions, ICurve } from "./common"
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
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
